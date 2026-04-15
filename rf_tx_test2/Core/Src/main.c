/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "NRF24.h"
#include "NRF24_reg_addresses.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PLD_SIZE 16
#define UART_BUF_SIZE 64
//#define USER

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin);
// PID Functions
void INIT_PID               (void);
void CHANGE_PID             (char* code, float value);
void PRINT_PID   		    (void);
// RF Functions
void TRANSMIT_LOG           (void);
void DEBUG_RF				(void);
void nrf24_scan_channels    (UART_HandleTypeDef *huart);
// Log file Functions
void LOG_DATA_POINT			(int time, int engine_rpm, int box_rpm);
void CLEAR_LOG_FILE			(void);
int  FIND_LOG_LINES			(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// USART3 Variables
char uart_buf[PLD_SIZE];
uint8_t uart_index = 0;
uint8_t uart_char;
uint8_t command_ready = 0;
// RF Variables
uint8_t data_Rx[PLD_SIZE*5];
uint8_t ack_R[PLD_SIZE] = { "Received" };
uint8_t ack_T[PLD_SIZE];
char complete_msg[10] = "COMPLETE";
char rf_error_msg[10] = "RF_ERROR\n";
char rf_timeout_msg[9] = "TIMEOUT\n";
volatile uint8_t nrf_irq_flag = 0;
uint32_t timeout;
// Logging variables
bool logging = false;
double log_rate = 0; // Default logging rate in ms

typedef struct __attribute__((packed)) {
    uint32_t time;
    uint16_t engine_rpm;
    uint16_t box_rpm;
} CompactLogEntry;

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
} PID_Param;
// 0 RPM Low
// 1 Low Gear
// 2 RPM High
// 3 High Gear
PID_Param PID_Values[4];

// some variables for FatFs
FATFS FatFs;
FIL fil;
FRESULT fres;
BYTE SDreadBuf[128];
char msg[128];
uint8_t addr_gui[5]  = {0x10,0x21,0x32,0x43,0x54};
uint8_t addr_ecvt[5] = {0x20,0x21,0x32,0x43,0x54};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM6_Init();
  MX_USART3_UART_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  csn_high();
  nrf24_init();
  nrf24_tx_pwr(_0dbm);
  nrf24_data_rate(_2mbps);
  nrf24_set_channel(7);
  nrf24_set_crc(en_crc, _1byte);
  nrf24_pipe_pld_size(0, PLD_SIZE);

//  uint8_t addr[5] = {0x10, 0x21, 0x32, 0x43, 0x54};
//  nrf24_open_tx_pipe(addr);
//  nrf24_open_rx_pipe(0, addr);

  // --- In your initialization (User Code 2) ---

  nrf24_auto_ack_all(enable);     // Enable ACKs for all pipes
  nrf24_auto_retr_delay(5);       // Set delay (5 = 1500us). Critical for reliable ACKs.
  nrf24_auto_retr_limit(15);      // Try up to 15 times before giving up
  nrf24_mode_rx(addr_ecvt);
  INIT_PID();
  //nrf24_scan_channels(&huart3);
  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_RED);

  /* Initialize User push-button without interrupt mode. */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1){

	  if (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET))
	  {
		 uint8_t result;
		 result = nrf24_transmit_wait((uint8_t*)complete_msg, strlen(complete_msg));
		 if(result == 0){
		 		sprintf(msg, "Success\r\n");
		 		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		 	} else if(result == 1){
		 		DEBUG_RF();
		 		sprintf(msg, "max_rt\r\n");
		 		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		 	} else{
		 		DEBUG_RF();
		 		sprintf(msg, "Error\r\n");
		 		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		 	}
		 HAL_Delay(100);
	  }

	  // Receive interrupt (data detected)
	  if(nrf_irq_flag){
		  // Clear IRQ flag
		  nrf_irq_flag = 0;
		  // Double check data is available
		  if (nrf24_data_available()){
			  	  // Receive in command
				  nrf24_receive(data_Rx, PLD_SIZE);

				  if (strncmp((char*)data_Rx, "PID", 3) == 0){ // Change PID Values
					BSP_LED_Toggle(LED_GREEN);
					// Read in value to be changed (P1,I2,D4, Etc.)
					char command[20];
					char code[3];
					float value = 0;
					int parsed = sscanf((char*)data_Rx, "%s %2s %f", command, code, &value);

					if(parsed == 3){ // Successful parsing of command
						// Change the value in memory
						CHANGE_PID(code,value);
						PRINT_PID();
					}

				  } else if(strcmp((char*)data_Rx, "DOWNLOAD_LOG") == 0){ // Download log file from SD card
					// Switch to transmitting
					// Confirm that logging is not active
					// Open the log file
					// Read one line until the end of the file
					// 	Transmit the line
					BSP_LED_On(LED_GREEN);
					HAL_Delay(100);
					TRANSMIT_LOG();
					BSP_LED_Off(LED_GREEN);


				  } else if(strncmp((char*)data_Rx, "CHANGE_RATE", 11) == 0){ // Change the logging rate
					  BSP_LED_Toggle(LED_GREEN);
					  sscanf((char*)data_Rx, "%*s %lf", &log_rate);
					  CHANGE_PID("NA",0);
					  PRINT_PID();

				  } else if(strncmp((char*)data_Rx, "TEST_RF",7) == 0){ // Send a message back if in range
					  // Do nothing since auto_ack is enabled the result variable will determine if a transmission is successful or not
					  BSP_LED_Toggle(LED_GREEN);
				  }
				  nrf24_flush_rx();
		  	  	  }
	  	  	  }
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 30;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == IRQ_Pin)
    {
        nrf_irq_flag = 1;
    }
}

void INIT_PID(){
	fres = f_mount(&FatFs, "", 1);
	  if (fres != FR_OK) {
	      sprintf(msg, "Init PID f_mount error (%i)\r\n", fres);
	      HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	      while(1);
	  }

	// Open file
	fres = f_open(&fil, "PID.txt", FA_READ);
    if (fres != FR_OK) {
	  sprintf(msg, "f_open error (%i)\r\n", fres);
	  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    }

	// 1. Read Log Rate (Line 1)
	if (f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil)) {
		// "Log Rate %lf" skips the text and reads the double
		sscanf((TCHAR*)SDreadBuf, "Log Rate %lf", &log_rate);
	}

	// 2. Read the 4 PID sets (3 lines each)
	for (int i = 0; i < 4; i++) {
	    // Read P line
	    if (f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil)) {
	        // " %*s" skips the "P1", "I1", etc. The leading space is critical!
	        sscanf((TCHAR*)SDreadBuf, " %*s %f", &PID_Values[i].Kp);
	    } else {
	        HAL_UART_Transmit(&huart3, (uint8_t*)"Read Error P\r\n", 14, 100);
	    }

	    // Read I line
	    if (f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil)) {
	        sscanf((TCHAR*)SDreadBuf, " %*s %f", &PID_Values[i].Ki);
	    }

	    // Read D line
	    if (f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil)) {
	        sscanf((TCHAR*)SDreadBuf, " %*s %f", &PID_Values[i].Kd);
	    }
	}

    // Close file
    f_close(&fil);

    // De-mount drive
    f_mount(NULL, "", 0);

}

void CHANGE_PID(char* code, float value){

	int index = (code[1] - '0') - 1;

	switch (code[0]) {
	        case 'P':
	            PID_Values[index].Kp = value;
	            break;
	        case 'I':
	            PID_Values[index].Ki = value;
	            break;
	        case 'D':
	            PID_Values[index].Kd = value;
	            break;
	        default:
	        	break;
	    }

	// Mount drive
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
	    sprintf(msg, "f_mount error (%i)\r\n", fres);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}

	// Open file
	fres = f_open(&fil, "PID.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if (fres != FR_OK) {
	    sprintf(msg, "f_open error (%i)\r\n", fres);
	    HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}

	char line_buffer[64];

	// Write logging rate
	sprintf(line_buffer, "Log Rate %0.2f\n", (double)log_rate);
	f_puts(line_buffer, &fil);

	// Save current PID values
	for (int i = 0; i < 4; i++) {
		sprintf(line_buffer, "P%d %0.3f\n", i + 1, (double)PID_Values[i].Kp);
		f_puts(line_buffer, &fil);

		sprintf(line_buffer, "I%d %0.3f\n", i + 1, (double)PID_Values[i].Ki);
		f_puts(line_buffer, &fil);

		sprintf(line_buffer, "D%d %0.3f\n", i + 1, (double)PID_Values[i].Kd);
		f_puts(line_buffer, &fil);
	}

	// Close file
	f_close(&fil);

	// De-mount drive
	f_mount(NULL, "", 0);
}

void PRINT_PID(){
	// 1. Verify Log Rate
	sprintf(msg, "Log Rate Parsed: %.2f\r\n", log_rate);
	HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	// 2. Verify PID Array Values
	for (int i = 0; i < 4; i++) {
		// Formatting the output for each PID set
		sprintf(msg, "Set %d: P%.2f I%.2f D%.2f\r\n",
				i, PID_Values[i].Kp, PID_Values[i].Ki, PID_Values[i].Kd);

		// Transmit via UART
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}
}

void TRANSMIT_LOG(){
	CompactLogEntry entry;

	// Switch to transmit
	nrf24_mode_tx(addr_gui);

	// Get the number of lines in the log file
	int log_lines = FIND_LOG_LINES();
	char log_lines_str[32] = "";
	snprintf(log_lines_str, sizeof(log_lines_str), "%d", log_lines);

	HAL_Delay(100);
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
	  sprintf(msg, "Download log f_mount error (%i)\r\n", fres);
	  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	  return;
	  }
	HAL_Delay(100);
	// Open file
	fres = f_open(&fil, "LOG.txt", FA_READ);
	if (fres != FR_OK) {
	  sprintf(msg, "f_open error (%i)\r\n", fres);
	  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	  return;
	}

	// Transmit complete message (Ensure that the NRF24 has switched modes)
	nrf_irq_flag = 0;
	uint8_t result;
	for(int i = 0; i< 50; i++){
	   result = nrf24_transmit_wait((uint8_t*)log_lines_str, strlen(log_lines_str));
	   HAL_Delay(10);
	   BSP_LED_On(LED_RED);
	   if(result == 0){
		   BSP_LED_Off(LED_RED);
		   break;
	   }
	}
	nrf_irq_flag = 0;
	int error_i = 0;
	char line[64];
	uint8_t status;
	// Begin log file transmission
	if (result == 0) {
		while (f_gets(line, sizeof(line), &fil)) {
			// Parse text file into our binary struct
			if(sscanf(line, "%lu %hu %hu", &entry.time, &entry.engine_rpm, &entry.box_rpm) >= 3) {

				// Send binary struct
				while(1){
					status = nrf24_transmit_wait((uint8_t*)&entry, sizeof(entry));
					DEBUG_RF();
					if (status == 0) {
						break;
					}
				}

				if (status != 0) {
					error_i++;
					nrf24_flush_tx(); // Clear the failed packet from buffer
				}
			}
		}

	} else {
		sprintf(msg, "Error in initial transmission\r\n");
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	}

	for(int i = 0; i< 50; i++){
		result = nrf24_transmit_wait((uint8_t*)complete_msg, strlen(complete_msg));
		if(result == 0){
			break;
		}
	}
	sprintf(msg, "Packets lost: %d\r\n", error_i);
	HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	if(result == 0){
		sprintf(msg, "Success\r\n");
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	} else if(result == 1){
		sprintf(msg, "max_rt\r\n");
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	} else{
		sprintf(msg, "Error\r\n");
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}
	nrf24_flush_rx();
	// Switch back to receive
	nrf24_mode_rx(addr_ecvt);

	// Close file
	f_close(&fil);

	// De-mount drive
	f_mount(NULL, "", 0);
}

void DEBUG_RF(){
	//Status register
	uint8_t status = nrf24_r_status();
//	uint8_t fifo_status = nrf24_r_reg(FIFO_STATUS, 1);
//	uint8_t observe = nrf24_r_reg(OBSERVE_TX, 1);
//	sprintf(msg, "%d %d %d\r\n", status, fifo_status, observe);
//	HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	if (status & (1 << MAX_RT)) {
		//BSP_LED_On(LED_RED);
	}

	if (status & (1 << TX_FULL)) {
		//BSP_LED_On(LED_RED);
	}

	// Check for "Carrier Detect" - helps identify interference
	if (nrf24_carrier_detect()) {
		BSP_LED_On(LED_RED);
	} else{
		BSP_LED_Off(LED_RED);
	}
}

void CLEAR_LOG_FILE(){
	// Mount drive
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		sprintf(msg, "f_mount error (%i)\r\n", fres);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		while(1);
	}
	// Clear file
	fres = f_open(&fil, "LOG.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if (fres != FR_OK) {
	  sprintf(msg, "f_open error (%i)\r\n", fres);
	  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}

	// Close file
	f_close(&fil);

	// De-mount drive
	f_mount(NULL, "", 0);
}

void LOG_DATA_POINT(int time, int engine_rpm, int box_rpm){
	// Mount drive
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		sprintf(msg, "f_mount error (%i)\r\n", fres);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		while(1);
	}
	// Open file to append
	fres = f_open(&fil, "LOG.txt", FA_OPEN_ALWAYS | FA_WRITE);
	if (fres != FR_OK) {
	  sprintf(msg, "f_open error (%i)\r\n", fres);
	  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}

	f_lseek(&fil, f_size(&fil));

	char line_buffer[64];
	// Write logging rate
	sprintf(line_buffer, "%d %d %d\n", time, engine_rpm, box_rpm);
	if (f_puts(line_buffer, &fil) < 0) {
		sprintf(msg, "f_puts error\r\n");
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}

	// Close file
	f_close(&fil);
	// De-mount drive
	f_mount(NULL, "", 0);
}

int FIND_LOG_LINES(){
	int lines_count = 0;

	// Mount drive
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		sprintf(msg, "f_mount error (%i)\r\n", fres);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}

	// Open file
	fres = f_open(&fil, "LOG.txt", FA_READ);
	if (fres != FR_OK) {
		sprintf(msg, "f_open error (%i)\r\n", fres);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}


	while(f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil)){
		lines_count++;
	}
	if (lines_count > 0) {
	    lines_count++; // account for last line without newline
	}
	// Close file
	f_close(&fil);
	// De-mount drive
	f_mount(NULL, "", 0);

	return lines_count;
}

void nrf24_scan_channels(UART_HandleTypeDef *huart) {
	uint8_t best_channel = 0;
	uint32_t min_noise = 0xFFFFFFFF;
	uint8_t noise_map[126];

	sprintf(msg, "Scanning for cleanest channel...\r\n");
	HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), 100);

	for (uint8_t i = 0; i < 126; i++) {
		uint32_t channel_noise = 0;
		nrf24_set_channel(i);
		nrf24_mode_rx(addr_gui); // Must be in RX mode to detect carrier

		// Sample the channel 100 times to catch "bursty" noise
		for (int samples = 0; samples < 100; samples++) {
			if (nrf24_carrier_detect()) {
				channel_noise++;
			}
			delay_us(50); // Quick samples
		}

		noise_map[i] = channel_noise;

		// Keep track of the winner
		if (channel_noise < min_noise) {
			min_noise = channel_noise;
			best_channel = i;
		}
	}

	sprintf(msg, "Best Channel: %d (Noise: %d%%)\r\n", best_channel, (int)min_noise);
	HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), 100);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
