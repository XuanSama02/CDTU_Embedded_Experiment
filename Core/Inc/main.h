/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_f103.h"
#include "bsp_usart.h"
#include "bsp_f103_delay.h"
#include "bsp_tm1638.h"
#include "bsp_flowmeter.h"
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_02_Pin GPIO_PIN_3
#define KEY_02_GPIO_Port GPIOE
#define KEY_02_EXTI_IRQn EXTI3_IRQn
#define KEY_01_Pin GPIO_PIN_4
#define KEY_01_GPIO_Port GPIOE
#define KEY_01_EXTI_IRQn EXTI4_IRQn
#define LED_GREEN_Pin GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOE
#define KEY_UP_Pin GPIO_PIN_0
#define KEY_UP_GPIO_Port GPIOA
#define KEY_UP_EXTI_IRQn EXTI0_IRQn
#define Flowmeter_Pin GPIO_PIN_11
#define Flowmeter_GPIO_Port GPIOE
#define Flowmeter_EXTI_IRQn EXTI15_10_IRQn
#define TM1638_STB_Pin GPIO_PIN_12
#define TM1638_STB_GPIO_Port GPIOE
#define TM1638_CLK_Pin GPIO_PIN_13
#define TM1638_CLK_GPIO_Port GPIOE
#define TM1638_DIO_Pin GPIO_PIN_14
#define TM1638_DIO_GPIO_Port GPIOE
#define LED_RED_Pin GPIO_PIN_5
#define LED_RED_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_8
#define BEEP_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
