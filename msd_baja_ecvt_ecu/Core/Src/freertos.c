/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "print_debug.h"
#include <stddef.h>
#include "adc.h"
#include "tim.h"
#include "motor_control.h"
#include "sensor_filter.h"
#include "Controller_P7.h"
#include "sensor_conversion.h"
#include "main.h"
#include "NRF24.h"
#include "NRF24_reg_addresses.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define HELIX_ANGLE_BUF_LEN 1
#define THROTTLE_ANGLE_BUF_LEN 1
#define PRIM_RPM_BUF_LEN 2
#define SEC_RPM_BUF_LEN 2

#define NEUTRAL 11999
#define MAX_FORWARD	15999
#define MAX_REVERSE 7999
#define PWM_RANGE 8000

#define MOTOR_CONTROL 2

#define PLD_SIZE 16
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint16_t helix_angle_buf[HELIX_ANGLE_BUF_LEN];
uint16_t throttle_angle_buf[THROTTLE_ANGLE_BUF_LEN];
uint32_t prim_rpm_buf[PRIM_RPM_BUF_LEN];
uint32_t sec_rpm_buf[SEC_RPM_BUF_LEN];

//  uint16_t speed = NEUTRAL_SPEED;
//  uint16_t curr_position = 0;
//  uint16_t pos_setpoint = 0;
//  uint16_t helix_angle = 0;
extern DMA_HandleTypeDef hdma_tim2_ch1;
extern DMA_HandleTypeDef hdma_tim2_ch2;

// RF Variables
extern uint8_t nrf_irq_flag;
extern double log_rate;
uint8_t data_Rx[PLD_SIZE*5];


/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Sensor_Reading */
osThreadId_t Sensor_ReadingHandle;
const osThreadAttr_t Sensor_Reading_attributes = {
  .name = "Sensor_Reading",
  .stack_size = 1028 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Motor_Control */
osThreadId_t Motor_ControlHandle;
const osThreadAttr_t Motor_Control_attributes = {
  .name = "Motor_Control",
  .stack_size = 1028 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Debug_Disp */
osThreadId_t Debug_DispHandle;
const osThreadAttr_t Debug_Disp_attributes = {
  .name = "Debug_Disp",
  .stack_size = 1028 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ReceiveRF */
osThreadId_t ReceiveRFHandle;
const osThreadAttr_t ReceiveRF_attributes = {
  .name = "ReceiveRF",
  .stack_size = 1028 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for processRF */
osThreadId_t processRFHandle;
const osThreadAttr_t processRF_attributes = {
  .name = "processRF",
  .stack_size = 1028 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for helix_angle_queue */
osMessageQueueId_t helix_angle_queueHandle;
const osMessageQueueAttr_t helix_angle_queue_attributes = {
  .name = "helix_angle_queue"
};
/* Definitions for throttle_angle_queue */
osMessageQueueId_t throttle_angle_queueHandle;
const osMessageQueueAttr_t throttle_angle_queue_attributes = {
  .name = "throttle_angle_queue"
};
/* Definitions for pri_rpm_queue */
osMessageQueueId_t pri_rpm_queueHandle;
const osMessageQueueAttr_t pri_rpm_queue_attributes = {
  .name = "pri_rpm_queue"
};
/* Definitions for sec_rpm_queue */
osMessageQueueId_t sec_rpm_queueHandle;
const osMessageQueueAttr_t sec_rpm_queue_attributes = {
  .name = "sec_rpm_queue"
};
/* Definitions for helix_pos_mc_queue */
osMessageQueueId_t helix_pos_mc_queueHandle;
const osMessageQueueAttr_t helix_pos_mc_queue_attributes = {
  .name = "helix_pos_mc_queue"
};
/* Definitions for throttle_pos_mc_queue */
osMessageQueueId_t throttle_pos_mc_queueHandle;
const osMessageQueueAttr_t throttle_pos_mc_queue_attributes = {
  .name = "throttle_pos_mc_queue"
};
/* Definitions for prim_rpm_mc_queue */
osMessageQueueId_t prim_rpm_mc_queueHandle;
const osMessageQueueAttr_t prim_rpm_mc_queue_attributes = {
  .name = "prim_rpm_mc_queue"
};
/* Definitions for sec_rpm_mc_queue */
osMessageQueueId_t sec_rpm_mc_queueHandle;
const osMessageQueueAttr_t sec_rpm_mc_queue_attributes = {
  .name = "sec_rpm_mc_queue"
};
/* Definitions for pidconfig_queue */
osMessageQueueId_t pidconfig_queueHandle;
const osMessageQueueAttr_t pidconfig_queue_attributes = {
  .name = "pidconfig_queue"
};
/* Definitions for RFCommandQueue */
osMessageQueueId_t RFCommandQueueHandle;
const osMessageQueueAttr_t RFCommandQueue_attributes = {
  .name = "RFCommandQueue"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Start_Sensor_Reading(void *argument);
void Start_Motor_Control(void *argument);
void Start_Debug_Disp(void *argument);
void receiveRFCommand(void *argument);
void processRFCommand(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of helix_angle_queue */
  helix_angle_queueHandle = osMessageQueueNew (16, sizeof(float), &helix_angle_queue_attributes);

  /* creation of throttle_angle_queue */
  throttle_angle_queueHandle = osMessageQueueNew (16, sizeof(float), &throttle_angle_queue_attributes);

  /* creation of pri_rpm_queue */
  pri_rpm_queueHandle = osMessageQueueNew (16, sizeof(float), &pri_rpm_queue_attributes);

  /* creation of sec_rpm_queue */
  sec_rpm_queueHandle = osMessageQueueNew (16, sizeof(float), &sec_rpm_queue_attributes);

  /* creation of helix_pos_mc_queue */
  helix_pos_mc_queueHandle = osMessageQueueNew (16, sizeof(float), &helix_pos_mc_queue_attributes);

  /* creation of throttle_pos_mc_queue */
  throttle_pos_mc_queueHandle = osMessageQueueNew (16, sizeof(float), &throttle_pos_mc_queue_attributes);

  /* creation of prim_rpm_mc_queue */
  prim_rpm_mc_queueHandle = osMessageQueueNew (16, sizeof(float), &prim_rpm_mc_queue_attributes);

  /* creation of sec_rpm_mc_queue */
  sec_rpm_mc_queueHandle = osMessageQueueNew (16, sizeof(float), &sec_rpm_mc_queue_attributes);

  /* creation of pidconfig_queue */
  pidconfig_queueHandle = osMessageQueueNew (4, sizeof(PIDConfig), &pidconfig_queue_attributes);

  /* creation of RFCommandQueue */
  RFCommandQueueHandle = osMessageQueueNew (16, 16, &RFCommandQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Sensor_Reading */
  Sensor_ReadingHandle = osThreadNew(Start_Sensor_Reading, NULL, &Sensor_Reading_attributes);

  /* creation of Motor_Control */
  Motor_ControlHandle = osThreadNew(Start_Motor_Control, NULL, &Motor_Control_attributes);

  /* creation of Debug_Disp */
  Debug_DispHandle = osThreadNew(Start_Debug_Disp, NULL, &Debug_Disp_attributes);

  /* creation of ReceiveRF */
  ReceiveRFHandle = osThreadNew(receiveRFCommand, NULL, &ReceiveRF_attributes);

  /* creation of processRF */
  processRFHandle = osThreadNew(processRFCommand, NULL, &processRF_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Start_Sensor_Reading */
/**
* @brief Function implementing the Sensor_Reading thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Sensor_Reading */
void Start_Sensor_Reading(void *argument)
{
  /* USER CODE BEGIN Start_Sensor_Reading */
  /* Infinite loop */
	uint16_t helix_angle = 0;
	uint8_t helix_angle_prio = 0;
	uint16_t throttle_angle = 0;
	uint8_t throttle_angle_prio = 0;
	uint32_t prim_rpm_uint32 = 0;
//	uint32_t curr_prim_rpm_tic = 0;
//	uint32_t prev_prim_rpm_tic = 0;
	uint8_t prim_rpm_prio = 0;
	uint32_t sec_rpm_uint32 = 0;
	uint8_t sec_rpm_prio = 0;
	const uint32_t TIMEOUT = 10;
	SPEED_FIFO prim_speed_fifo = {0};
	uint32_t curr_prim_rpm_tic = 0;
	uint32_t prev_prim_rpm_tic = 0;
	SPEED_FIFO sec_speed_fifo = {0};
	uint32_t curr_sec_rpm_tic = 0;
	uint32_t prev_sec_rpm_tic = 0;
	float prim_rpm = 0.0f;
	float sec_rpm = 0.0f;

	dma_speed_fifo_init(&prim_speed_fifo);
	dma_speed_fifo_init(&sec_speed_fifo);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)helix_angle_buf, HELIX_ANGLE_BUF_LEN);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t*)throttle_angle_buf, THROTTLE_ANGLE_BUF_LEN);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, prim_speed_fifo.buf, DMA_FIFO_BUF_SIZE);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, sec_speed_fifo.buf, DMA_FIFO_BUF_SIZE);

    HAL_TIM_OC_Start(&htim6, TIM_CHANNEL_1);


  for(;;)
  {
    osDelay(MC_OS_DELAY);
    BSP_LED_Toggle(LED_GREEN);

    //Read and convert angles
    helix_angle = adc12b_to_rad(helix_angle_buf[0]);

    throttle_angle = adc12b_to_rad(throttle_angle_buf[0]);

    //Read and empty prim rpm fifo so always most recent
    while (dma_speed_fifo_available(&prim_speed_fifo, &hdma_tim2_ch1)){
    	curr_prim_rpm_tic = dma_speed_fifo_read_single(&prim_speed_fifo);
    	prim_rpm_uint32 = curr_prim_rpm_tic - prev_prim_rpm_tic;
    	prev_prim_rpm_tic = curr_prim_rpm_tic;
    }

    prim_rpm = pickup_dt_to_rad_per_sec(prim_rpm_uint32);

    //Read and empty sec rpm fifo so always most recent
    while (dma_speed_fifo_available(&sec_speed_fifo, &hdma_tim2_ch2)){
    	curr_sec_rpm_tic = dma_speed_fifo_read_single(&sec_speed_fifo);
    	sec_rpm_uint32 = curr_sec_rpm_tic - prev_sec_rpm_tic;
    	prev_sec_rpm_tic = curr_sec_rpm_tic;
    }

    sec_rpm = pickup_dt_to_rad_per_sec(sec_rpm_uint32);


    osMessageQueuePut(helix_angle_queueHandle, &helix_angle, helix_angle_prio, TIMEOUT);
    osMessageQueuePut(helix_pos_mc_queueHandle, &helix_angle, helix_angle_prio, TIMEOUT);
    osMessageQueuePut(throttle_angle_queueHandle, &throttle_angle, throttle_angle_prio, TIMEOUT);
    osMessageQueuePut(throttle_pos_mc_queueHandle, &throttle_angle, throttle_angle_prio, TIMEOUT);
    osMessageQueuePut(pri_rpm_queueHandle, &prim_rpm, prim_rpm_prio, TIMEOUT);
    osMessageQueuePut(prim_rpm_mc_queueHandle, &prim_rpm, prim_rpm_prio, TIMEOUT);
    osMessageQueuePut(sec_rpm_queueHandle, &sec_rpm, sec_rpm_prio, TIMEOUT);
    osMessageQueuePut(sec_rpm_mc_queueHandle, &sec_rpm, sec_rpm_prio, TIMEOUT);

  }
  /* USER CODE END Start_Sensor_Reading */
}

/* USER CODE BEGIN Header_Start_Motor_Control */
/**
* @brief Function implementing the Motor_Control thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Motor_Control */
void Start_Motor_Control(void *argument)
{
  /* USER CODE BEGIN Start_Motor_Control */
  /* Infinite loop */
  uint16_t speed = NEUTRAL_SPEED;
//  uint16_t helix_pos = 0;
  uint16_t pos_setpoint = 0;
  uint16_t helix_angle = 0;
  uint8_t helix_angle_prio = 0;
  const uint32_t QUEUE_TIMEOUT= 10;
  uint8_t speed_percent = 0xff;
  uint16_t ccr = NEUTRAL;
  uint8_t current_percent = 50;
  char lr_dir = '\0';

  float prim_rpm = 0;
  uint8_t prim_rpm_prio = 0;
  float sec_rpm = 0;
  uint8_t sec_rpm_prio = 0;
  float throttle_pos = 0;
  uint8_t throttle_pos_prio = 0;
  float helix_pos = 0;

  uint16_t motor_pwm_setpoint = NEUTRAL_SPEED;

  PIDConfig mode_pid_sp = {0};
  uint8_t mode_pid_sp_prio = 0;
  init_pidconfig(&mode_pid_sp);

#if MOTOR_CONTROL == 2
  // Initialize controller variables
  Controller_P7_initialize();
#endif

  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, NEUTRAL_SPEED);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

  for(;;)
  {
    osDelay(MC_OS_DELAY);

    BSP_LED_Toggle(LED_BLUE);
#if MOTOR_CONTROL == 0

    while(osMessageQueueGetCount(helix_pos_mc_queueHandle)){
    	osMessageQueueGet(helix_pos_mc_queueHandle, &helix_pos, &helix_angle_prio, QUEUE_TIMEOUT);
    }
    pos_setpoint = update_setpoint(pos_setpoint, helix_pos);
    speed = pid_loop(pos_setpoint, helix_pos);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed);
#elif MOTOR_CONTROL == 1
	  current_percent = (__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1) - MAX_REVERSE)*100/PWM_RANGE;
//	  printf("\r\nCurrent Percent: %lu", current_percent);
/*	  scanf("%lu", &speed_percent);
	  //HAL_Delay(10000);
	  if (speed_percent != 0xffff && speed_percent <= 100 && speed_percent >= 0){
		  ccr = PWM_RANGE * speed_percent / 100 + MAX_REVERSE;
		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ccr);
	  }*/
	  scanf("%c", &lr_dir);
	  	  //HAL_Delay(10000);
	  	  if (lr_dir == ','){
	  		  ccr = PWM_RANGE * (current_percent - 1)/ 100 + MAX_REVERSE;
	  		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccr);
	  	  }
	  	  else if (lr_dir == '.'){
	  		  ccr = PWM_RANGE * (current_percent + 1)/ 100 + MAX_REVERSE;
	  		  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccr);

	  	  }
	  lr_dir = '\0';
	  speed_percent = 0xffff;
#elif MOTOR_CONTROL == 2

	    while(osMessageQueueGetCount(pidconfig_queueHandle)){
	    	osMessageQueueGet(pidconfig_queueHandle, &mode_pid_sp, &mode_pid_sp_prio, QUEUE_TIMEOUT);
	    }

	    update_pidconfig(&mode_pid_sp);

	    //Get all current sensor values
	    while(osMessageQueueGetCount(helix_pos_mc_queueHandle)){
	    	osMessageQueueGet(helix_pos_mc_queueHandle, &helix_pos, &helix_angle_prio, QUEUE_TIMEOUT);
	    }
	    while(osMessageQueueGetCount(throttle_pos_mc_queueHandle)){
	    	osMessageQueueGet(throttle_pos_mc_queueHandle, &throttle_pos, &throttle_pos_prio, QUEUE_TIMEOUT);
	    }
	    while(osMessageQueueGetCount(prim_rpm_mc_queueHandle)){
	    	osMessageQueueGet(prim_rpm_mc_queueHandle, &prim_rpm, &prim_rpm_prio, QUEUE_TIMEOUT);
	    }
	    while(osMessageQueueGetCount(sec_rpm_mc_queueHandle)){
	    	osMessageQueueGet(sec_rpm_mc_queueHandle, &sec_rpm, &sec_rpm_prio, QUEUE_TIMEOUT);
	    }

	    //Update sensor inputs
        Controller_P7_U.Omega_Primary = prim_rpm; // ReadEngineSpeedSensor(); // e.g., 1500.0f
        Controller_P7_U.Omega_Secondary = sec_rpm; // ReadSecondarySpeedSensor(); // e.g., 1500.0f
        Controller_P7_U.Theta_Helix = helix_pos; //ReadGearRatioSensor(); // e.g., 1.5f

        // calculate speed command
        Controller_P7_step();

        motor_pwm_setpoint = scale_command(Controller_P7_Y.Command);

        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, motor_pwm_setpoint);


#else
	#error "invalid MOTOR_CONTROL value"
#endif
  }
  /* USER CODE END Start_Motor_Control */
}

/* USER CODE BEGIN Header_Start_Debug_Disp */
/**
* @brief Function implementing the Debug_Disp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Debug_Disp */
void Start_Debug_Disp(void *argument)
{
  /* USER CODE BEGIN Start_Debug_Disp */
  /* Infinite loop */
	uint32_t prim_rpm = 0;
	uint8_t prim_rpm_prio = 0;
	uint32_t sec_rpm = 0;
	uint8_t sec_rpm_prio = 0;
	uint16_t throttle_angle = 0;
	uint8_t throttle_angle_prio = 0;
	uint16_t helix_angle = 0;
	uint8_t helix_angle_prio = 0;
	const uint32_t QUEUE_TIMEOUT= 10;

  for(;;)
  {
    osDelay(1);
    BSP_LED_Toggle(LED_RED);

    while(osMessageQueueGetCount(helix_angle_queueHandle)){
    	osMessageQueueGet(helix_angle_queueHandle, &helix_angle, &helix_angle_prio, QUEUE_TIMEOUT);
    }

    while(osMessageQueueGetCount(throttle_angle_queueHandle)){
    	osMessageQueueGet(throttle_angle_queueHandle, &throttle_angle, &throttle_angle_prio, QUEUE_TIMEOUT);
    }

    while(osMessageQueueGetCount(pri_rpm_queueHandle)){
    	osMessageQueueGet(pri_rpm_queueHandle, &prim_rpm, &prim_rpm_prio, QUEUE_TIMEOUT);
    }

    while(osMessageQueueGetCount(sec_rpm_queueHandle)){
    	osMessageQueueGet(sec_rpm_queueHandle, &sec_rpm, &sec_rpm_prio, QUEUE_TIMEOUT);
    }

    print_debug_sensor_vals(prim_rpm, sec_rpm, throttle_angle, helix_angle);\

  }
  /* USER CODE END Start_Debug_Disp */
}

/* USER CODE BEGIN Header_receiveRFCommand */
/**
* @brief Function implementing the ReceiveRF thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_receiveRFCommand */
void receiveRFCommand(void *argument)
{
  /* USER CODE BEGIN receiveRFCommand */
  /* Infinite loop */
  const uint32_t QUEUE_TIMEOUT= 10;
  for(;;)
  {
	if(nrf_irq_flag){
		if (nrf24_data_available()){
			// Receive in command
			nrf24_receive(data_Rx, PLD_SIZE);
			osMessageQueuePut(RFCommandQueueHandle, data_Rx, 0, QUEUE_TIMEOUT);
			nrf24_flush_rx();
		}
	}
    osDelay(1);
  }
  /* USER CODE END receiveRFCommand */
}

/* USER CODE BEGIN Header_processRFCommand */
/**
* @brief Function implementing the processRF thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_processRFCommand */
void processRFCommand(void *argument)
{
  /* USER CODE BEGIN processRFCommand */
  /* Infinite loop */
  static char command[16];
  for(;;)
  {
	if(osMessageQueueGet(RFCommandQueueHandle, command, NULL, osWaitForever) == osOK){
		if (strncmp((char*)command, "PID", 3) == 0){ // Change PID Values
			BSP_LED_Toggle(LED_GREEN);
			// Read in value to be changed (P1,I2,D4, Etc.)
			char rx_command[20];
			char code[3];
			float value = 0;
			int parsed = sscanf((char*)command, "%s %2s %f", rx_command, code, &value);

			if(parsed == 3){ // Successful parsing of command
			  // Change the value in memory
			  CHANGE_PID(code,value);
			}

		  } else if(strcmp((char*)command, "DOWNLOAD_LOG") == 0){ // Download log file from SD card
			  BSP_LED_On(LED_GREEN);
			  HAL_Delay(100);
			  //TRANSMIT_LOG();
			  BSP_LED_Off(LED_GREEN);
		  } else if(strncmp((char*)command, "CHANGE_RATE", 11) == 0){ // Change the logging rate
			  BSP_LED_Toggle(LED_GREEN);
			  sscanf((char*)data_Rx, "%*s %lf", &log_rate);
			  CHANGE_PID("LOG",0);
		  } else if(strncmp((char*)command, "TEST_RF",7) == 0){ // Send a message back if in range
			  // Do nothing since auto_ack is enabled the result variable will determine if a transmission is successful or not
			  BSP_LED_Toggle(LED_GREEN);
		  }
	}
    osDelay(1);
  }
  /* USER CODE END processRFCommand */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

