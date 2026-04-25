/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "stm32h7xx_nucleo.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
int  INIT_PID              (void);
int  CHANGE_PID            (char* code, float value);
int  START_LOG			   (void);
void STOP_LOG			   (void);
int  LOG_DATA_POINT		   (int time, int engine_rpm, int box_rpm);
int  FIND_LOG_LINES		   (void);
int  TRANSMIT_LOG		   (void);
void TIM6_SetPeriod_us     (uint32_t us);
void PRINT_PID   		   (void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI2_CS_Pin GPIO_PIN_0
#define SPI2_CS_GPIO_Port GPIOC
#define pri_speed_Pin GPIO_PIN_0
#define pri_speed_GPIO_Port GPIOA
#define RF_CSN_Pin GPIO_PIN_4
#define RF_CSN_GPIO_Port GPIOC
#define RF_CE_Pin GPIO_PIN_5
#define RF_CE_GPIO_Port GPIOC
#define test_Pin GPIO_PIN_0
#define test_GPIO_Port GPIOG
#define test_EXTI_IRQn EXTI0_IRQn
#define sec_speed_Pin GPIO_PIN_3
#define sec_speed_GPIO_Port GPIOB
#define IRQ_RF_Pin GPIO_PIN_6
#define IRQ_RF_GPIO_Port GPIOB
#define IRQ_RF_EXTI_IRQn EXTI9_5_IRQn
#define LOG_SW_Pin GPIO_PIN_1
#define LOG_SW_GPIO_Port GPIOE
#define LOG_SW_EXTI_IRQn EXTI1_IRQn

/* USER CODE BEGIN Private defines */
#define SD_SPI_HANDLE hspi2
#define P1 13
#define I1 5
#define D1 17
#define P2 11
#define I2 3
#define D2 1
#define P3 12
#define I3 4
#define D3 16
#define P4 10
#define I4 2
#define D4 0
#define SP1 7
#define SP2 8
#define SP3 6
#define SP4 9

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
