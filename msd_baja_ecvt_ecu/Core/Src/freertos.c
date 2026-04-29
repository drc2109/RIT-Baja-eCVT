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
#include <stdio.h>
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
#define MOTOR_CURR_BUF_LEN 1
#define PRIM_RPM_BUF_LEN 2
#define SEC_RPM_BUF_LEN 2

#define NEUTRAL 11999
#define MAX_FORWARD	15999
#define MAX_REVERSE 7999
#define PWM_RANGE 8000

#define MOTOR_CONTROL 2

#define PLD_SIZE 16

#define DEBUG 1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint16_t helix_angle_buf[HELIX_ANGLE_BUF_LEN];
uint16_t throttle_angle_buf[THROTTLE_ANGLE_BUF_LEN];

uint16_t motor_curr_buf[MOTOR_CURR_BUF_LEN] __attribute__((section(".sram4_section")));
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
extern int log_rate;
uint8_t data_Rx[PLD_SIZE*5];

// LOG Variables
extern uint8_t record_log_flag;
extern bool isLogging;
extern uint8_t logSwitchflg;
extern uint8_t uart_command_flag;
extern uint8_t rx_uart3_buffer[64];

extern UART_HandleTypeDef huart3;

uint32_t sensor_task_loop_time = 0;
uint32_t mc_task_loop_time = 0;
uint32_t log_task_loop_time = 0;
uint32_t rfrec_task_loop_time = 0;
uint32_t proc_rf_task_loop_time = 0;
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
  .priority = (osPriority_t) osPriorityAboveNormal6,
};
/* Definitions for Motor_Control */
osThreadId_t Motor_ControlHandle;
const osThreadAttr_t Motor_Control_attributes = {
  .name = "Motor_Control",
  .stack_size = 1028 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal7,
};
/* Definitions for Debug_Disp */
osThreadId_t Debug_DispHandle;
const osThreadAttr_t Debug_Disp_attributes = {
  .name = "Debug_Disp",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ReceiveRF */
osThreadId_t ReceiveRFHandle;
const osThreadAttr_t ReceiveRF_attributes = {
  .name = "ReceiveRF",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal5,
};
/* Definitions for processRF */
osThreadId_t processRFHandle;
const osThreadAttr_t processRF_attributes = {
  .name = "processRF",
  .stack_size = 1028 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal4,
};
/* Definitions for loggingTask */
osThreadId_t loggingTaskHandle;
const osThreadAttr_t loggingTask_attributes = {
  .name = "loggingTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal3,
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
/* Definitions for sensor_data_mc_q */
osMessageQueueId_t sensor_data_mc_qHandle;
const osMessageQueueAttr_t sensor_data_mc_q_attributes = {
  .name = "sensor_data_mc_q"
};
/* Definitions for sensor_data_debug_q */
osMessageQueueId_t sensor_data_debug_qHandle;
const osMessageQueueAttr_t sensor_data_debug_q_attributes = {
  .name = "sensor_data_debug_q"
};
/* Definitions for sensor_data_log_q */
osMessageQueueId_t sensor_data_log_qHandle;
const osMessageQueueAttr_t sensor_data_log_q_attributes = {
  .name = "sensor_data_log_q"
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
void logData(void *argument);

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

  /* creation of pidconfig_queue */
  pidconfig_queueHandle = osMessageQueueNew (4, sizeof(PIDConfig), &pidconfig_queue_attributes);

  /* creation of RFCommandQueue */
  RFCommandQueueHandle = osMessageQueueNew (16, 16, &RFCommandQueue_attributes);

  /* creation of sensor_data_mc_q */
  sensor_data_mc_qHandle = osMessageQueueNew (4, sizeof(sensor_data_t), &sensor_data_mc_q_attributes);

  /* creation of sensor_data_debug_q */
  sensor_data_debug_qHandle = osMessageQueueNew (4, sizeof(sensor_data_t), &sensor_data_debug_q_attributes);

  /* creation of sensor_data_log_q */
  sensor_data_log_qHandle = osMessageQueueNew (60, sizeof(sensor_data_t), &sensor_data_log_q_attributes);

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

  /* creation of loggingTask */
  loggingTaskHandle = osThreadNew(logData, NULL, &loggingTask_attributes);

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
    osDelay(1000);
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
	float helix_angle = 0;
	uint8_t helix_angle_prio = 0;
	float throttle_angle = 0;
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
	float motor_curr = 0.0f;
	float motor_curr_avg = 0.0f;
	uint8_t prim_rpm_sense_overflow = 0;
	uint8_t sec_rpm_sense_overflow = 0;

	sensor_data_t sensor_data = {0};
	int i = 0;
#if DEBUG == 1
	uint32_t prev_sensor_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	uint32_t curr_sensor_task_tick = prev_sensor_task_tick;
#endif
	dma_speed_fifo_init(&prim_speed_fifo);
	dma_speed_fifo_init(&sec_speed_fifo);

	//Start ADCs and DMAs
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)helix_angle_buf, HELIX_ANGLE_BUF_LEN);
	HAL_ADC_Start_DMA(&hadc2, (uint32_t*)throttle_angle_buf, THROTTLE_ANGLE_BUF_LEN);
	HAL_ADC_Start_DMA(&hadc3, (uint32_t*)motor_curr_buf, MOTOR_CURR_BUF_LEN);

	// Start prim and secondary timestep monitors
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, prim_speed_fifo.buf, DMA_FIFO_BUF_SIZE);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, sec_speed_fifo.buf, DMA_FIFO_BUF_SIZE);

	// Start sample trigger for ADCs
    HAL_TIM_OC_Start(&htim6, TIM_CHANNEL_1);


  for(;;)
  {
    osDelay(MC_OS_DELAY);

#if DEBUG == 1
    curr_sensor_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	sensor_task_loop_time = curr_sensor_task_tick - prev_sensor_task_tick;
    prev_sensor_task_tick = curr_sensor_task_tick;
#endif
    //Read and convert angles
    helix_angle = adc12b_to_rad(helix_angle_buf[0]);

    throttle_angle = adc12b_to_rad(throttle_angle_buf[0]);

    sensor_data.helix_angle = helix_angle;
    sensor_data.throttle_angle = throttle_angle;
    // Inside the for(;;) loop of Start_Sensor_Reading
    // Invalidate the 2 bytes (uint16_t) at the buffer address
    SCB_InvalidateDCache_by_Addr((uint32_t*)motor_curr_buf, 2);
    motor_curr = adc12b_to_motor_curr(motor_curr_buf[0]);
    motor_curr_avg = moving_average_filter_curr(motor_curr);

    //Read and empty prim rpm fifo so always most recent
    while(dma_speed_fifo_available(&prim_speed_fifo, &hdma_tim2_ch1)
    		||dma_speed_fifo_available(&sec_speed_fifo, &hdma_tim2_ch2)){
		if (dma_speed_fifo_available(&prim_speed_fifo, &hdma_tim2_ch1)){
			curr_prim_rpm_tic = dma_speed_fifo_read_single(&prim_speed_fifo);
			prim_rpm_sense_overflow = curr_prim_rpm_tic > prev_prim_rpm_tic ? 0 : 1;
			if (prim_rpm_sense_overflow){
				prev_prim_rpm_tic = curr_prim_rpm_tic;
				continue;
			}
			prim_rpm_uint32 = curr_prim_rpm_tic - prev_prim_rpm_tic;
			prev_prim_rpm_tic = curr_prim_rpm_tic;
			if (!prim_rpm_sense_overflow){
				prim_rpm = pickup_dt_to_rad_per_sec(prim_rpm_uint32);
			}
		}


		//Read and empty sec rpm fifo so always most recent
		if (dma_speed_fifo_available(&sec_speed_fifo, &hdma_tim2_ch2)){
			curr_sec_rpm_tic = dma_speed_fifo_read_single(&sec_speed_fifo);
			sec_rpm_sense_overflow = curr_sec_rpm_tic > prev_sec_rpm_tic ? 0 : 1;
			if (sec_rpm_sense_overflow){
				prev_sec_rpm_tic = curr_sec_rpm_tic;
				continue;
			}
			sec_rpm_uint32 = curr_sec_rpm_tic - prev_sec_rpm_tic;
			prev_sec_rpm_tic = curr_sec_rpm_tic;
			if (!prim_rpm_sense_overflow){
				sec_rpm = pickup_dt_to_rad_per_sec_gb(sec_rpm_uint32);
			}
		}

	    sensor_data.prim_rpm = prim_rpm;
	    sensor_data.sec_rpm = sec_rpm;

    }


    sensor_data.motor_curr = motor_curr_avg;


    osMessageQueuePut(sensor_data_mc_qHandle, &sensor_data, 0, 0);

#if DEBUG == 1

//    osMessageQueuePut(sensor_data_debug_qHandle, &sensor_data, 0, TIMEOUT);

#endif


  }
  /* USER CODE END Start_Sensor_Reading */
}

/* USER CODE BEGIN Header_Start_Motor_Control */
uint16_t ccr = NEUTRAL;
sensor_data_t sensor_data_mc = {0};
uint16_t motor_pwm_setpoint = NEUTRAL_SPEED;
float helix_angle_offset_removed = 0.0f;
uint8_t flag_min_pos_safety = 0;
uint8_t flag_max_pos_safety = 0;
uint8_t flag_no_safety = 0;

real_T controller_mode = 0;
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
  uint8_t current_percent = 50;
  char lr_dir = '\0';

  float prim_rpm = 0;
  uint8_t prim_rpm_prio = 0;
  float sec_rpm = 0;
  uint8_t sec_rpm_prio = 0;
  float throttle_pos = 0;
  uint8_t throttle_pos_prio = 0;
  float helix_pos = 0;
  float helix_offset = 2.2;
  sensor_data_t sensor_data_log = {0};

//  sensor_data_t sensor_data_mc = {0};
#if DEBUG == 1
	uint32_t prev_mc_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	uint32_t curr_mc_task_tick = prev_mc_task_tick;
#endif

  PIDConfig mode_pid_sp = {0};
  uint8_t mode_pid_sp_prio = 0;
	INIT_PID();
//	PRINT_PID();
	init_pidconfig(&mode_pid_sp);

//	helix_offset = init_helix_offset();

#if MOTOR_CONTROL == 2
  // Initialize controller variables
  Controller_P7_initialize();
#endif

  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, NEUTRAL_SPEED);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  for(;;)
  {
    osDelay(MC_OS_DELAY);

#if DEBUG == 1
    curr_mc_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
    mc_task_loop_time = curr_mc_task_tick - prev_mc_task_tick;
	prev_mc_task_tick = curr_mc_task_tick;
#endif
//    BSP_LED_Toggle(LED_BLUE);
#if MOTOR_CONTROL == 0

    while(osMessageQueueGetCount(helix_pos_mc_queueHandle)){
    	osMessageQueueGet(helix_pos_mc_queueHandle, &helix_pos, &helix_angle_prio, QUEUE_TIMEOUT);
    }
    pos_setpoint = update_setpoint(pos_setpoint, helix_pos);
    speed = pid_loop(pos_setpoint, helix_pos);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, speed);
#elif MOTOR_CONTROL == 1
//	  current_percent = (__HAL_TIM_GET_COMPARE(&htim1, TIM_CHANNEL_1) - MAX_REVERSE)*100/PWM_RANGE;
//	  printf("\r\nCurrent Percent: %lu", current_percent);
/*	  scanf("%lu", &speed_percent);
	  //HAL_Delay(10000);
	  if (speed_percent != 0xffff && speed_percent <= 100 && speed_percent >= 0){
		  ccr = PWM_RANGE * speed_percent / 100 + MAX_REVERSE;
		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ccr);
	  }*/
	  while(osMessageQueueGetCount(sensor_data_mc_qHandle)){
	    	osMessageQueueGet(sensor_data_mc_qHandle, &sensor_data_mc, &helix_angle_prio, QUEUE_TIMEOUT);
	  }
	  scanf("%c", &lr_dir);
	  	  //HAL_Delay(10000);
	  	  if (lr_dir == ','){
	  		  ccr-=20;
	  		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ccr);
	  	  }
	  	  else if (lr_dir == '.'){
	  		  ccr+= 20;
	  		  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ccr);

	  	  }
	  lr_dir = '\0';
	  speed_percent = 0xffff;
#elif MOTOR_CONTROL == 2

	    while(osMessageQueueGetCount(pidconfig_queueHandle)){
	    	osMessageQueueGet(pidconfig_queueHandle, &mode_pid_sp, &mode_pid_sp_prio, QUEUE_TIMEOUT);
		    update_pidconfig(&mode_pid_sp);
	    }


	    while(osMessageQueueGetCount(sensor_data_mc_qHandle)){
	    	osMessageQueueGet(sensor_data_mc_qHandle, &sensor_data_mc, &helix_angle_prio, QUEUE_TIMEOUT);
	    }
	    //Get all current sensor values

	    //Update sensor inputs

        Controller_P7_U.Omega_Primary = sensor_data_mc.prim_rpm; // ReadEngineSpeedSensor(); // e.g., 1500.0f

        Controller_P7_U.Omega_Secondary = sensor_data_mc.sec_rpm; // ReadSecondarySpeedSensor(); // e.g., 1500.0f

        helix_angle_offset_removed = sensor_data_mc.helix_angle - MIN_H_ANGLE;
        Controller_P7_U.Theta_Helix = helix_angle_offset_removed > 0 ? helix_angle_offset_removed : 0; //ReadGearRatioSensor(); // e.g., 1.5f


        // calculate speed command
        Controller_P7_step();

        motor_pwm_setpoint = scale_command(Controller_P7_Y.Command);

        if (sensor_data_mc.helix_angle >= MAX_H_ANGLE && motor_pwm_setpoint > NEUTRAL_SPEED){
        	motor_pwm_setpoint = NEUTRAL_SPEED;
        	flag_min_pos_safety = 0;
        	flag_max_pos_safety = 1;
        	flag_no_safety = 0;

        }
        else if (sensor_data_mc.helix_angle <= MIN_H_ANGLE && motor_pwm_setpoint < NEUTRAL_SPEED){
        	motor_pwm_setpoint = NEUTRAL_SPEED;
        	flag_min_pos_safety = 1;
        	flag_max_pos_safety = 0;
        	flag_no_safety = 0;
        }
        else{
        	flag_min_pos_safety = 0;
        	flag_max_pos_safety = 0;
        	flag_no_safety = 1;
        }


        if (HAL_GPIO_ReadPin(MC_Enable_GPIO_Port, MC_Enable_Pin) == GPIO_PIN_SET){
        	motor_pwm_setpoint = NEUTRAL_SPEED;
        }

        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, motor_pwm_setpoint);


        sensor_data_log.prim_rpm = Controller_P7_Y.Primary_Speed;
        sensor_data_log.sec_rpm = Controller_P7_Y.Secondary_Speed;
        osMessageQueuePut(sensor_data_log_qHandle, &sensor_data_log, 0, 0);

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
#if DEBUG == 1

	float prim_rpm = 0;
	uint8_t prim_rpm_prio = 0;
	float sec_rpm = 0;
	uint8_t sec_rpm_prio = 0;
	float throttle_angle = 0;
	uint8_t throttle_angle_prio = 0;
	float helix_angle = 0;
	uint8_t helix_angle_prio = 0;
	const uint32_t QUEUE_TIMEOUT= 10;
	sensor_data_t sensor_data_debug = {0};
#endif

  for(;;)
  {

#if DEBUG == 0
    osDelay(1000);

#else DEBUG == 1
    osDelay(10);

//    BSP_LED_Toggle(LED_RED);

//    while(osMessageQueueGetCount(helix_angle_queueHandle)){
//    	osMessageQueueGet(helix_angle_queueHandle, &helix_angle, &helix_angle_prio, QUEUE_TIMEOUT);
//    }
//
//    while(osMessageQueueGetCount(throttle_angle_queueHandle)){
//    	osMessageQueueGet(throttle_angle_queueHandle, &throttle_angle, &throttle_angle_prio, QUEUE_TIMEOUT);
//    }
//
//    while(osMessageQueueGetCount(pri_rpm_queueHandle)){
//    	osMessageQueueGet(pri_rpm_queueHandle, &prim_rpm, &prim_rpm_prio, QUEUE_TIMEOUT);
//    }
//
//    while(osMessageQueueGetCount(sec_rpm_queueHandle)){
//    	osMessageQueueGet(sec_rpm_queueHandle, &sec_rpm, &sec_rpm_prio, QUEUE_TIMEOUT);
//    }
//    while(osMessageQueueGetCount(sensor_data_debug_qHandle)){
 //   	osMessageQueueGet(sensor_data_debug_qHandle, &sensor_data_debug, &helix_angle_prio, QUEUE_TIMEOUT);
//    }
#if MOTOR_CONTROL != 1

//    print_debug_sensor_vals(sensor_data_debug.prim_rpm, sensor_data_debug.sec_rpm, sensor_data_debug.throttle_angle, sensor_data_debug.helix_angle);\

    #endif
#endif
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

#if DEBUG == 1
  uint32_t prev_rfrec_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
  uint32_t curr_rfrec_task_tick = prev_rfrec_task_tick;
#endif

  for(;;)
  {

#if DEBUG == 1
	curr_rfrec_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	rfrec_task_loop_time = curr_rfrec_task_tick - prev_rfrec_task_tick;
	prev_rfrec_task_tick = curr_rfrec_task_tick;
#endif

	if(nrf_irq_flag){
		if (nrf24_data_available()){
			// Receive in command
			nrf24_receive(data_Rx, PLD_SIZE);
			osMessageQueuePut(RFCommandQueueHandle, data_Rx, 0, QUEUE_TIMEOUT);
			nrf24_flush_rx();
		}
	}
	if(uart_command_flag){
		uart_command_flag = 0;
		osMessageQueuePut(RFCommandQueueHandle, rx_uart3_buffer, 0, QUEUE_TIMEOUT);
		memset(rx_uart3_buffer,0, sizeof(rx_uart3_buffer));
	}
    osDelay(10);
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
#if DEBUG == 1
	uint32_t prev_proc_rf_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	uint32_t curr_proc_rf_task_tick = prev_proc_rf_task_tick;
#endif

  for(;;)
  {

#if DEBUG == 1
	  curr_proc_rf_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	  proc_rf_task_loop_time = curr_proc_rf_task_tick - prev_proc_rf_task_tick;
	prev_proc_rf_task_tick = curr_proc_rf_task_tick;
#endif

	if(osMessageQueueGet(RFCommandQueueHandle, command, NULL, 10) == osOK){
		if (strncmp((char*)command, "PID", 3) == 0){ // Change PID Values
			BSP_LED_Toggle(LED_GREEN);
			// Read in value to be changed (P1,I2,D4, Etc.)
			char rx_command[20];
			char code[3];
			float value = 0;
			int parsed, value_int;
			if((strncmp((char*)command, "PID SP1", 7) || strncmp((char*)command, "PID SP3", 7) == 0) == 0){
				parsed = sscanf((char*)command, "%s %3s %d", rx_command, code, &value_int);
				if(parsed == 3){ // Successful parsing of command
				  // Change the value in memory
				  CHANGE_PID(code,value_int);
				}
			} else{
				parsed = sscanf((char*)command, "%s %3s %f", rx_command, code, &value);
				if(parsed == 3){ // Successful parsing of command
				  // Change the value in memory
				  CHANGE_PID(code,value);
				}

			}
//		    PRINT_PID();

		  } else if(strncmp((char*)command, "DOWNLOAD_LOG",12) == 0){ // Download log file from SD card
			  BSP_LED_Toggle(LED_GREEN);
			  HAL_Delay(100);
//			  TRANSMIT_LOG();
			  TRANSMIT_LOG_USB();
		  } else if(strncmp((char*)command, "CHANGE_RATE", 11) == 0){ // Change the logging rate
			  BSP_LED_Toggle(LED_GREEN);
			  sscanf((char*)data_Rx, "%*s %d", &log_rate);
			  CHANGE_PID("LOG",0);
			  PRINT_PID();
		  } else if(strncmp((char*)command, "TEST_RF",7) == 0){ // Send a message back if in range
			  // Do nothing since auto_ack is enabled the result variable will determine if a transmission is successful or not
			  BSP_LED_Toggle(LED_GREEN);
		  }
	}
    osDelay(10);
  }
  /* USER CODE END processRFCommand */
}

/* USER CODE BEGIN Header_logData */
/**
* @brief Function implementing the loggingTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_logData */
void logData(void *argument)
{
  /* USER CODE BEGIN logData */
	sensor_data_t sensor_data_log = {0};
	uint8_t prio = 0;
	const uint32_t QUEUE_TIMEOUT = 10;
	uint32_t log_number = 0; //incoming data is most recent value at 1ms timesteps
	uint16_t log_rate = 1; //log timestep in ms
  /* Infinite loop */
#if DEBUG == 1
	uint32_t prev_log_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	uint32_t curr_log_task_tick = prev_log_task_tick;
#endif

  for(;;)
  {

#if DEBUG == 1
	  curr_log_task_tick = __HAL_TIM_GET_COUNTER(&htim5);
	  log_task_loop_time = curr_log_task_tick - prev_log_task_tick;
	  prev_log_task_tick = curr_log_task_tick;
#endif
	BSP_LED_Toggle(LED_RED);
	if (logSwitchflg){
		logSwitchflg = 0;
		if(HAL_GPIO_ReadPin(LOG_SW_GPIO_Port,LOG_SW_Pin) == GPIO_PIN_SET){
			isLogging = false;
			STOP_LOG(); // Close log file
		} else{
			isLogging = true;
			START_LOG(); // Open log file
		}
	}
	if(isLogging){

		while(osMessageQueueGetCount(sensor_data_log_qHandle)){
			osMessageQueueGet(sensor_data_log_qHandle, &sensor_data_log, &prio, QUEUE_TIMEOUT);

			//skips any sensor data that isn't a multiple of log rate
			if (log_number++ % log_rate){
				continue;
			}

			LOG_DATA_POINT(log_number, sensor_data_log.prim_rpm, sensor_data_log.sec_rpm); //TODO: Connect to actual parameters
		}
	}

	else{
		log_number = 0;
	}
    osDelay(30);
  }
  /* USER CODE END logData */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
//float init_helix_offset(){
//	return 0
//}
/* USER CODE END Application */

