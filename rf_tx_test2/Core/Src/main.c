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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void INIT_PID(void);
void CHANGE_PID(char* code, float value);
void PRINT_PID(void);
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
char complete_msg[10] = "COMPLETE\n";
char rf_error_msg[10] = "RF_ERROR\n";
char rf_timeout_msg[9] = "TIMEOUT\n";
volatile uint8_t nrf_irq_flag = 0;
uint32_t timeout;
// Logging variables
bool logging = false;
double log_rate = 100; // Default logging rate in ms

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
BYTE SDreadBuf[64];
char msg[128];

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
  nrf24_set_channel(78);
  nrf24_set_crc(en_crc, _1byte);
  nrf24_pipe_pld_size(0, PLD_SIZE);
  uint8_t addr[5] = {0x10, 0x21, 0x32, 0x43, 0x54};
  nrf24_open_tx_pipe(addr);
  nrf24_open_rx_pipe(0, addr);

  // --- In your initialization (User Code 2) ---

  nrf24_auto_ack_all(enable);     // Enable ACKs for all pipes
  nrf24_auto_retr_delay(5);       // Set delay (5 = 1500us). Critical for reliable ACKs.
  nrf24_auto_retr_limit(15);      // Try up to 15 times before giving up
  nrf24_listen();
  INIT_PID();
  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_RED);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1){
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
					BSP_LED_Toggle(LED_GREEN);
					// Switch back to receiving
				  } else if(strncmp((char*)data_Rx, "CHANGE_RATE", 11) == 0){ // Change the logging rate
					  BSP_LED_Toggle(LED_GREEN);

					  CHANGE_PID("NO",0);
					  PRINT_PID();

				  } else if(strncmp((char*)data_Rx, "TEST_RF",7) == 0){ // Send a message back if in range
					  // Do nothing since auto_ack is enabled the result variable will determine if a transmission is successful or not
					  BSP_LED_Toggle(LED_GREEN);


//					  BSP_LED_Toggle(LED_GREEN);
//					  // Switch to transmit
//					  nrf24_mode_tx();
//
//					  // Transmit complete message (In range)
//					  nrf_irq_flag = 0;
//					  uint8_t result;
//					  for(int i = 0; i< 50; i++){
//						   result = nrf24_transmit_wait((uint8_t*)complete_msg, sizeof(complete_msg));
//						   if(result == 0){
//							   break;
//						   }
//					  }
//
//					  //HAL_Delay(10);
//					  //result = nrf24_transmit_wait((uint8_t*)complete_msg, sizeof(complete_msg));
//
//					  nrf_irq_flag = 0;
//					  // Set LEDs based on result
//					  if (result == 0) {
//						  // Complete message received
//						  HAL_UART_Transmit(&huart3, (uint8_t*)"Success\r\n", 11, HAL_MAX_DELAY);
//					  } else {
//						  // Complete message failed
//						  //BSP_LED_On(LED_RED);
//						  HAL_UART_Transmit(&huart3, (uint8_t*)"Failed\r\n", 11, HAL_MAX_DELAY);
//
//						  //Status register
//						  uint8_t status = nrf24_r_reg(STATUS, 1);
//						  char msg[40];
//						  sprintf(msg, "STATUS: 0x%02X\r\n", status);
//						  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
//
//						  // Observe_TX reg
//						  uint8_t obs = nrf24_r_reg(OBSERVE_TX, 1);
//						  uint8_t retry_count = obs & 0x0F;
//						  uint8_t packet_loss = (obs >> 4) & 0x0F;
//						  sprintf(msg, "Retries:%d Loss:%d\r\n", retry_count, packet_loss);
//						  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
//						  // FIFO Status reg
//						  uint8_t fifo = nrf24_r_reg(FIFO_STATUS, 1);
//						  sprintf(msg, "FIFO:0x%02X\r\n", fifo);
//						  HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
//
//					  }
//					  // Switch back to receive
//					  nrf24_mode_rx();
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
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
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
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
	      sprintf(msg, "f_mount error (%i)\r\n", fres);
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
		while(1);
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
