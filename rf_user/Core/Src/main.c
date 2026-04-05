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
void RECEIVE_LOG();
void DEBUG_RF();
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
uint16_t log_rate = 100; // Default logging rate in ms

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

typedef struct {
	uint32_t time;
	uint32_t engine_rpm;
	uint32_t box_rpm;
} LogEntry;

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
  /* USER CODE BEGIN 2 */
  csn_high();
  nrf24_init();
  nrf24_tx_pwr(_0dbm);
  nrf24_data_rate(_2mbps);
  nrf24_set_channel(99);
  nrf24_set_crc(en_crc, _1byte);
  nrf24_pipe_pld_size(0, PLD_SIZE);

//  uint8_t addr[5] = {0x10, 0x21, 0x32, 0x43, 0x54};
//  nrf24_open_tx_pipe(addr);
//  nrf24_open_rx_pipe(0, addr);

  // --- In your initialization (User Code 2) ---

  nrf24_auto_ack_all(enable);     // Enable ACKs for all pipes
  nrf24_auto_retr_delay(5);       // Set delay (5 = 1500us). Critical for reliable ACKs.
  nrf24_auto_retr_limit(15);      // Try up to 15 times before giving up
  nrf24_mode_tx(addr_ecvt);
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
	  // USART Receive from GUI
	  if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_RXNE)){
		  HAL_UART_Receive(&huart3, &uart_char, 1, 0);

		  if (uart_char == '\n' || uart_char == '\r')
		  {

			  uart_buf[uart_index] = '\0';
			  uart_index = 0;
			  command_ready = 1;
		  }
		  else
		  {
			  if (uart_index < UART_BUF_SIZE - 1)
				  uart_buf[uart_index++] = uart_char;
		  }
	  }

	  // Process command
	  if (command_ready){
		  command_ready = 0;

		  // Transmit the command over RF
		  uint8_t result = nrf24_transmit_wait((uint8_t*)uart_buf, sizeof(uart_buf));

		  // Check for specific commands
		  if (strcmp((char*)uart_buf, "DOWNLOAD_LOG") == 0){
			  if(result == 0) {
				  BSP_LED_On(LED_GREEN);
				  RECEIVE_LOG();
				  HAL_UART_Transmit(&huart3, (uint8_t*)complete_msg, 10, HAL_MAX_DELAY);
				  BSP_LED_Off(LED_GREEN);
			  } else { // Error in RF Transmission
				  BSP_LED_On(LED_RED);
				  HAL_UART_Transmit(&huart3, (uint8_t*)rf_error_msg, 10, HAL_MAX_DELAY);
			  }
		  }

		  else if(strncmp((char*)uart_buf, "PID",3) == 0){
			  BSP_LED_Toggle(LED_GREEN);
		  }

		  else if(strncmp((char*)uart_buf, "TEST_RF", 7) == 0){
			  BSP_LED_Toggle(LED_GREEN);
			  if(result == 0){ // Success
				  HAL_UART_Transmit(&huart3, (uint8_t*)complete_msg, 10, HAL_MAX_DELAY);
			  } else{ 		   // Failed
				  HAL_UART_Transmit(&huart3, (uint8_t*)rf_error_msg, 10, HAL_MAX_DELAY);
			  }

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

void RECEIVE_LOG(){
  nrf24_flush_rx();
  HAL_Delay(2);
  nrf24_mode_rx(addr_gui);

  uint32_t rx_timeout = HAL_GetTick();

  int log_entry_index = 0;
  int log_index = 0;
  int log_lines = 0;

  // Wait to receive transmission (delayed switching)
  // Get the number of lines in the log file (For memory malloc)
  int timeout_flag = 1;
  while (HAL_GetTick() - rx_timeout < 10000) { // 10s window
	  if (nrf24_data_available()) {
		  nrf24_receive(data_Rx, PLD_SIZE);
		  timeout_flag = 0;
		  break;
	  }
  }
  if(timeout_flag){
	  nrf24_mode_tx(addr_ecvt);
	  DEBUG_RF();
	  BSP_LED_On(LED_RED);
	  while(1);
	  return;
  } else{
	  sscanf((char*)data_Rx, "%d", &log_lines);
	  nrf24_flush_rx(); // Clear buffer after reading
  }

  // Malloc memory to save log file in memory
  LogEntry *log_buffer = malloc(log_lines * sizeof(LogEntry));
  if (log_buffer == NULL) {
      // Allocation failed
      nrf24_mode_tx(addr_ecvt);
      while(1);
      return;
  }

  // Begin receiving log file
  //TODO: Ensure this doesn't get stuck
  while (1) {
	  DEBUG_RF();
	  if (nrf24_data_available()) {
		  nrf24_receive(data_Rx, PLD_SIZE);
		  BSP_LED_Toggle(LED_GREEN);

		  if(strncmp((char*)data_Rx, complete_msg, 8) == 0){
			  break;
		  }

		  switch(log_entry_index){
		  	case 0:
		  		log_buffer[log_index].time = atoi((char*)&data_Rx);
		  		break;

		  	case 1:
		  		log_buffer[log_index].engine_rpm = atoi((char*)&data_Rx);
		  		break;

		  	case 2:
		  		log_buffer[log_index].box_rpm = atoi((char*)&data_Rx);
		  		break;

		  }
		  log_entry_index++;
		  if(log_entry_index%3 == 0){
			  log_index++;
		  }
		  log_entry_index = log_entry_index%3;

	  }
  }

  nrf24_mode_tx(addr_ecvt);

  // Begin sending data over USART
  char logfile_buf[128];
  for(int i = 0; i < log_lines; i++){
	  sprintf(logfile_buf, "%u %u %u\r\n", (int)log_buffer[i].time, (int)log_buffer[log_index].engine_rpm, (int)log_buffer[log_index].box_rpm);
	  HAL_UART_Transmit(&huart3, (uint8_t*)logfile_buf, strlen(logfile_buf), HAL_MAX_DELAY);
  }
}

void DEBUG_RF(){
	//Status register
	uint8_t status = nrf24_r_status();
	uint8_t fifo_status = nrf24_r_reg(FIFO_STATUS, 1);
	//uint8_t observe = nrf24_r_reg(OBSERVE_TX, 1);
//	sprintf(msg, "%d %d %d\r\n", status, fifo_status, observe);
//	HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	if (status & (1 << MAX_RT)) {
		//BSP_LED_On(LED_RED);
	}

	if (status & (1 << TX_FULL)) {
		//BSP_LED_On(LED_RED);
	}

	if (fifo_status & (1 << RX_FULL)) {
		//BSP_LED_On(LED_RED);
	}

	// Check for "Carrier Detect" - helps identify interference
	if (nrf24_carrier_detect()) {
		BSP_LED_On(LED_RED);
	} else{
		BSP_LED_Off(LED_RED);
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
