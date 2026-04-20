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
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "fdcan.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Controller_P7.h"
#include "NRF24.h"
#include "NRF24_reg_addresses.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PLD_SIZE 16
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

COM_InitTypeDef BspCOMInit;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
int _read(int file, char *ptr, int len);
int __io_getchar(void);
// PID Functions
int  INIT_PID              (void);
int  CHANGE_PID            (char* code, uint16_t value);
void PRINT_PID   		   (void);
// SD Card Functions
int  START_LOG			   (void);
void STOP_LOG			   (void);
int  LOG_DATA_POINT		   (int time, int engine_rpm, int box_rpm);
int  FIND_LOG_LINES		   (void);
// RF Function
int  TRANSMIT_LOG		   (void);
// Timer Functions
void TIM6_SetPeriod_us     (uint32_t us);
//E1
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// some variables for FatFs
FATFS FatFs;
FIL fil_PID, fil_LOG; // TODO: Create two log files, one for log and one for PID so they don't interfere
FRESULT fres;
BYTE SDreadBuf[64];
char msg[128];
volatile int log_rate = 100; // Default logging rate in us
// RF Variables
volatile uint8_t nrf_irq_flag = 0;
uint8_t addr_ecvt[5] = {0x20,0x21,0x32,0x43,0x54};
uint8_t addr_gui[5]  = {0x10,0x21,0x32,0x43,0x54};
char complete_msg[10] = "COMPLETE";
typedef struct __attribute__((packed)) {
    uint32_t time;
    uint16_t engine_rpm;
    uint16_t box_rpm;
} CompactLogEntry;
// LOG variables
volatile bool isLogging = 0;
volatile uint8_t record_log_flag = 0;
char line_buffer[64];
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

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  MX_ADC2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_FDCAN1_Init();
  MX_FDCAN2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_FATFS_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  printf("\x1B[?25l\x1B[2J\x1B[H");
  if(!INIT_PID()){ // Attempts to open SD card PID.txt to init PID files
	  //TODO: Set safe PID Values instead
  }
  // NRF24 init
  csn_high();
  nrf24_init();
  nrf24_tx_pwr(_0dbm);
  nrf24_data_rate(_2mbps);
  nrf24_set_channel(7);
  nrf24_set_crc(en_crc, _1byte);
  nrf24_pipe_pld_size(0, PLD_SIZE);
  nrf24_auto_ack_all(enable);     // Enable ACKs for all pipes
  nrf24_auto_retr_delay(5);       // Set delay (5 = 1500us). Critical for reliable ACKs.
  nrf24_auto_retr_limit(15);      // Try up to 15 times before giving up
  nrf24_mode_rx(addr_ecvt);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_RED);

  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInitStruct.PLL2.PLL2M = 4;
  PeriphClkInitStruct.PLL2.PLL2N = 9;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 2;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int _read(int file, char *ptr, int len)
{
    HAL_UART_Receive(&hcom_uart[COM1], (uint8_t *)ptr, 1, HAL_MAX_DELAY);
    return 1;
}

int __io_getchar(void)
{
    uint8_t ch;
    HAL_UART_Receive(&hcom_uart[COM1], &ch, 1, HAL_MAX_DELAY);
    return ch;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == IRQ_RF_Pin)
    {
        nrf_irq_flag = 1;
    }

    if(GPIO_Pin == LOG_SW_Pin){
    	if(HAL_GPIO_ReadPin(LOG_SW_GPIO_Port,LOG_SW_Pin) == GPIO_PIN_RESET){
    		BSP_LED_Off(LED_GREEN);
    		isLogging = false;
    		//STOP_LOG(); // Close log file
    		HAL_TIM_Base_Stop(&htim6);
    	} else{
    		BSP_LED_On(LED_GREEN);
    		isLogging = true;
    		//START_LOG(); // Open log file
    		HAL_TIM_Base_Start(&htim6);
    	}
    }
}

// Reads the PID.txt saved PID values and assigns them to the PID data structure (Controller_P7_P)
// Returns 0 if the file was unable to be opened and 1 if the PID value assignments were successful
int INIT_PID(){
	int temp_int;
	float temp_float;
	fres = f_mount(&FatFs, "", 1);
	  if (fres != FR_OK) {
	      return 0;
	  }

	// Open file
	fres = f_open(&fil_PID, "PID.txt", FA_READ);
    if (fres != FR_OK) {
    	return 0;
    }

	// 1. Read Log Rate (Line 1)
	if (f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil_PID)) {
		// "Log Rate %lf" skips the text and reads the double
		sscanf((TCHAR*)SDreadBuf, "Log Rate %d", &log_rate);
	} else {
		return 0;
	}

	// 2. Read the 4 PID sets (4 lines each)
	for (int i = 0; i < 16; i++) {
	    // Read P line
	    if (f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil_PID)) {
	        if(i == 3 || i == 11){ // All values except RPM Low and High set points are floats
	        	sscanf((TCHAR*)SDreadBuf, " %*s %d", &temp_int);
	        } else{
	        	sscanf((TCHAR*)SDreadBuf, " %*s %f", &temp_float);
	        }
	        // Set correct variable in control scheme

	        switch(i){
				case 0: // P1
					Controller_P7_P.Prop_RPM_Low = temp_float;
					break;
				case 1: // I1
					Controller_P7_P.Int_RPM_Low = temp_float;
					break;
				case 2: // D1
					Controller_P7_P.Der_RPM_Low = temp_float;
					break;
				case 3: // Low RPM SP
					Controller_P7_P.Omega_Low = temp_int;
					break;
				case 4: // P2
					Controller_P7_P.Prop_GR_Low = temp_float;
					break;
				case 5: // I2
					Controller_P7_P.Int_GR_Low = temp_float;
					break;
				case 6: // D2
					Controller_P7_P.Der_GR_Low = temp_float;
					break;
				case 7: // Low Gear SP
					Controller_P7_P.Phi_max = temp_float;
					break;
				case 8: // P3
					Controller_P7_P.Prop_RPM_High = temp_float;
					break;
				case 9: // I3
					Controller_P7_P.Int_RPM_High = temp_float;
					break;
				case 10: // D3
					Controller_P7_P.Der_RPM_High = temp_float;
					break;
				case 11: // High RPM SP
					Controller_P7_P.Omega_High = temp_int;
					break;
				case 12: // P4
					Controller_P7_P.Prop_GR_High = temp_float;
					break;
				case 13: // I4
					Controller_P7_P.Int_GR_High = temp_float;
					break;
				case 14: // D4
					Controller_P7_P.Der_GR_High = temp_float;
					break;
				case 15: // High Gear SP
					Controller_P7_P.Phi_min = temp_float;
					break;
	        }
	    } else {
	       return 0;
	    }
	}

    // Close file
    f_close(&fil_PID);

    // De-mount drive
    f_mount(NULL, "", 0);

    return 1;

}

// Changes the PID values in the PID structure and overwrites the value in PID.txt
// Takes in the code in string (Ex. P1, I4, SP2) and the value to change it to
// Returns 0 if the file writing was unsuccessful and 1 if it was successfully written to PID.txt
int CHANGE_PID(char* code, uint16_t value){

	if (strncmp(code, "P1", 2) == 0) {
	    Controller_P7_P.Prop_RPM_Low = (real_T) value;
	} else if (strncmp(code, "I1", 2) == 0) {
	    Controller_P7_P.Int_RPM_Low = (real_T) value;
	} else if (strncmp(code, "D1", 2) == 0) {
	    Controller_P7_P.Der_RPM_Low = (real_T) value;
	} else if (strncmp(code, "SP1", 3) == 0) {
	    Controller_P7_P.Omega_Low = (real_T) value;
	} else if (strncmp(code, "P2", 2) == 0) {
	    Controller_P7_P.Prop_GR_Low = (real_T) value;
	} else if (strncmp(code, "I2", 2) == 0) {
	    Controller_P7_P.Int_GR_Low = (real_T) value;
	} else if (strncmp(code, "D2", 2) == 0) {
	    Controller_P7_P.Der_GR_Low = (real_T) value;
	} else if (strncmp(code, "SP2", 3) == 0) {
	    Controller_P7_P.Phi_max = (real_T) value;
	} else if (strncmp(code, "P3", 2) == 0) {
	    Controller_P7_P.Prop_RPM_High = (real_T) value;
	} else if (strncmp(code, "I3", 2) == 0) {
	    Controller_P7_P.Int_RPM_High = (real_T) value;
	} else if (strncmp(code, "D3", 2) == 0) {
	    Controller_P7_P.Der_RPM_High = (real_T) value;
	} else if (strncmp(code, "SP3", 3) == 0) {
	    Controller_P7_P.Omega_High = (real_T) value;
	} else if (strncmp(code, "P4", 2) == 0) {
	    Controller_P7_P.Prop_GR_High = (real_T) value;
	} else if (strncmp(code, "I4", 2) == 0) {
	    Controller_P7_P.Int_GR_High = (real_T) value;
	} else if (strncmp(code, "D4", 2) == 0) {
	    Controller_P7_P.Der_GR_High = (real_T) value;
	} else if (strncmp(code, "SP4", 3) == 0) {
	    Controller_P7_P.Phi_min = (real_T) value;
	} else if (strncmp(code, "LOG", 3) == 0){
		// Do nothing
	} else {
		 return 0;
	}

	// Mount drive
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
	    return 0;
	}

	// Open file
	fres = f_open(&fil_PID, "PID.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if (fres != FR_OK) {
	    return 0;
	}

	char line_buffer[64];

	// Write logging rate
	sprintf(line_buffer, "Log Rate %d\r\n", (int)log_rate);
	f_puts(line_buffer, &fil_PID);
	// P1
	sprintf(line_buffer, "P1 %0.3f\r\n", (double)Controller_P7_P.Prop_RPM_Low);
	f_puts(line_buffer, &fil_PID);
	// I1
	sprintf(line_buffer, "I1 %0.3f\r\n", (double)Controller_P7_P.Int_RPM_Low);
	f_puts(line_buffer, &fil_PID);
	// D1
	sprintf(line_buffer, "D1 %0.3f\r\n", (double)Controller_P7_P.Der_RPM_Low);
	f_puts(line_buffer, &fil_PID);
	// SP1
	sprintf(line_buffer, "SP1 %d\r\n", (int)Controller_P7_P.Omega_Low);
	f_puts(line_buffer, &fil_PID);
	// P2
	sprintf(line_buffer, "P2 %0.3f\r\n", (double)Controller_P7_P.Prop_GR_Low);
	f_puts(line_buffer, &fil_PID);
	// I2
	sprintf(line_buffer, "I2 %0.3f\r\n", (double)Controller_P7_P.Int_GR_Low);
	f_puts(line_buffer, &fil_PID);
	// D2
	sprintf(line_buffer, "D2 %0.3f\r\n", (double)Controller_P7_P.Der_GR_Low);
	f_puts(line_buffer, &fil_PID);
	// SP2
	sprintf(line_buffer, "SP2 %0.3f\r\n", (double)Controller_P7_P.Phi_max);
	f_puts(line_buffer, &fil_PID);
	// P3
	sprintf(line_buffer, "P3 %0.3f\r\n", (double)Controller_P7_P.Prop_RPM_High);
	f_puts(line_buffer, &fil_PID);
	// I3
	sprintf(line_buffer, "I3 %0.3f\r\n", (double)Controller_P7_P.Int_RPM_High);
	f_puts(line_buffer, &fil_PID);
	// D3
	sprintf(line_buffer, "D3 %0.3f\r\n", (double)Controller_P7_P.Der_RPM_High);
	f_puts(line_buffer, &fil_PID);
	// SP3
	sprintf(line_buffer, "SP3 %d\r\n", (int)Controller_P7_P.Omega_High);
	f_puts(line_buffer, &fil_PID);
	// P4
	sprintf(line_buffer, "P4 %0.3f\r\n", (double)Controller_P7_P.Prop_GR_High);
	f_puts(line_buffer, &fil_PID);
	// I4
	sprintf(line_buffer, "I4 %0.3f\r\n", (double)Controller_P7_P.Int_GR_High);
	f_puts(line_buffer, &fil_PID);
	// D4
	sprintf(line_buffer, "D4 %0.3f\r\n", (double)Controller_P7_P.Der_GR_High);
	f_puts(line_buffer, &fil_PID);
	// SP4
	sprintf(line_buffer, "SP4 %0.3f\r\n", (double)Controller_P7_P.Phi_min);
	f_puts(line_buffer, &fil_PID);

	// Close file
	f_close(&fil_PID);
	// De-mount drive
	f_mount(NULL, "", 0);
	return 1;
}

// Creates "LOG.txt" which overwrites (clears) the previously created log file
// Opens the global file variable
// Returns 1 if successful and 0 if unsuccessful
int START_LOG(){
	// Mount drive
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		return 0;
	}
	// Clear file
	fres = f_open(&fil_LOG, "LOG.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if (fres != FR_OK) {
		return 0;
	}

	return 1;
}

// Closes the global log file (LOG.txt)
void STOP_LOG(){
	// Close file
	f_close(&fil_LOG);
	// De-mount drive
	f_mount(NULL, "", 0);
}

// Finds the amount of logged data points in LOG.txt (# of lines)
// Returns a positive integer if successful and -1 if not
int FIND_LOG_LINES(){
	int lines_count = 0;

	// Mount drive
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
		return -1;
	}
	// Open file
	fres = f_open(&fil_LOG, "LOG.txt", FA_READ);
	if (fres != FR_OK) {
		return -1;
	}


	while(f_gets((TCHAR*)SDreadBuf, sizeof(SDreadBuf), &fil_LOG)){
		lines_count++;
	}
	if (lines_count > 0) {
	    lines_count++; // account for last line without newline
	}
	// Close file
	f_close(&fil_LOG);
	// De-mount drive
	f_mount(NULL, "", 0);

	return lines_count;
}

// Logs a data point (one line) into LOG.txt (Assumes LOG.txt is open)
// Takes in the data to be logged (time, engine_rpm, and box_rpm)
// Returns 1 if the data point was siccessfully logged and 0 if the f_puts fails
int LOG_DATA_POINT(int time, int engine_rpm, int box_rpm){

	f_lseek(&fil_LOG, f_size(&fil_LOG));

	// Write logging rate
	sprintf(line_buffer, "%d %d %d\n", time, engine_rpm, box_rpm);
	if (f_puts(line_buffer, &fil_LOG) < 0) {
		return 0;
	}

	return 1;
}

int TRANSMIT_LOG(){
	CompactLogEntry entry;
	if(isLogging){ // Only send when not currently logging
		return 0;
	}
	// Switch to transmit
	nrf24_mode_tx(addr_gui);

	// Get the number of lines in the log file
	int log_lines = FIND_LOG_LINES();
	char log_lines_str[32] = "";
	snprintf(log_lines_str, sizeof(log_lines_str), "%d", log_lines);

	HAL_Delay(100);
	fres = f_mount(&FatFs, "", 1);
	if (fres != FR_OK) {
	  return 0;
	  }
	HAL_Delay(100);
	// Open file
	fres = f_open(&fil_LOG, "LOG.txt", FA_READ);
	if (fres != FR_OK) {
	  return 0;
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
	char line[64];
	uint8_t status;
	// Begin log file transmission
	if (result == 0) {
		while (f_gets(line, sizeof(line), &fil_LOG)) {
			// Parse text file into our binary struct
			if(sscanf(line, "%lu %hu %hu", &entry.time, &entry.engine_rpm, &entry.box_rpm) >= 3) {
				BSP_LED_Toggle(LED_RED);
				// Send binary struct
//				while(1){
//					status = nrf24_transmit_wait((uint8_t*)&entry, sizeof(entry));
//					DEBUG_RF();
//					if (status == 0) {
//						break;
//					}
//				}
//
//				if (status != 0) {
//					nrf24_flush_tx(); // Clear the failed packet from buffer
//				}
			}
		}

	} else {
		nrf24_flush_rx();
		// Switch back to receive
		nrf24_mode_rx(addr_ecvt);
		// Close file
		f_close(&fil_LOG);
		// De-mount drive
		f_mount(NULL, "", 0);
		return 0; // Error in intial transmission (Timeout)

	}

	for(int i = 0; i< 50; i++){
		result = nrf24_transmit_wait((uint8_t*)complete_msg, strlen(complete_msg));
		if(result == 0){
			break;
		}
	}

	nrf24_flush_rx();
	// Switch back to receive
	nrf24_mode_rx(addr_ecvt);

	// Close file
	f_close(&fil_LOG);

	// De-mount drive
	f_mount(NULL, "", 0);

	if(result == 0){
		return 1;
	} else {
		return 0;
	}

}

/**
 * @brief  Sets TIM6 interrupt period in microseconds
 * @param  us: Target period in microseconds (e.g., 1000 for 1ms)
 * @retval None
 */
void TIM6_SetPeriod_us(uint32_t us) {
    // 1. Get the PCLK1 frequency
    uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();

    // 2. Determine the actual Timer Clock (H7 doubles it if APB1 divider != 1)
    uint32_t tim_clk;
    if ((RCC->D2CFGR & RCC_D2CFGR_D2PPRE1) == 0) {
        tim_clk = pclk1;
    } else {
        tim_clk = pclk1 * 2;
    }

    // 3. Get the current Prescaler from the register
    uint32_t current_psc = TIM6->PSC + 1;

    // 4. Calculate ARR for microseconds
    // Logic: ARR = (Clock * Seconds) / PSC
    // Since 'us' is microseconds, we divide the denominator by 1,000,000
    uint64_t arr_value = ((uint64_t)tim_clk * us) / (1000000ULL * current_psc);

    // 5. Apply limits for 16-bit Timer
    if (arr_value > 65536) {
        arr_value = 65536;
    } else if (arr_value < 1) {
        arr_value = 1;
    }

    // 6. Update the register
    __HAL_TIM_SET_AUTORELOAD(&htim6, (uint32_t)(arr_value - 1));
}

void PRINT_PID(){
	// 1. Verify Log Rate
	sprintf(msg, "Log Rate Parsed: %d\r\n", log_rate);
	printf(msg);

	// 2. Verify PID Array Values
	sprintf(msg, "P1:%.2f I1:%.2f D1:%.2f SP1:%d\r\n",
			(double)Controller_P7_P.Prop_RPM_Low, (double)Controller_P7_P.Int_RPM_Low, (double)Controller_P7_P.Der_RPM_Low, (int)Controller_P7_P.Omega_Low);
	printf(msg);
	sprintf(msg, "P2:%.2f I2:%.2f D2:%.2f SP2:%.2f\r\n",
			(double)Controller_P7_P.Prop_GR_Low, (double)Controller_P7_P.Int_GR_Low, (double)Controller_P7_P.Der_GR_Low, (double)Controller_P7_P.Phi_max);
	printf(msg);
	sprintf(msg, "P3:%.2f I3:%.2f D3:%.2f SP3:%d\r\n",
			(double)Controller_P7_P.Prop_RPM_High, (double)Controller_P7_P.Int_RPM_High, (double)Controller_P7_P.Der_RPM_High, (int)Controller_P7_P.Omega_High);
	printf(msg);
	sprintf(msg, "P4:%.2f I4:%.2f D4:%.2f SP4:%.2f\r\n",
			(double)Controller_P7_P.Prop_GR_High, (double)Controller_P7_P.Int_GR_High, (double)Controller_P7_P.Der_GR_High, (double)Controller_P7_P.Phi_min);
	printf(msg);
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM6)
  {
	  if (isLogging)
	  {
		record_log_flag = 1;
	  }
  }
  /* USER CODE END Callback 1 */
}

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
