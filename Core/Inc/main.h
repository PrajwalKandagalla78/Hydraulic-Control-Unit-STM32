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
#include "stm32f1xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DOWN_RLY_Pin GPIO_PIN_14
#define DOWN_RLY_GPIO_Port GPIOC
#define UP_RLY_Pin GPIO_PIN_15
#define UP_RLY_GPIO_Port GPIOC
#define V_SENSE_Pin GPIO_PIN_3
#define V_SENSE_GPIO_Port GPIOA
#define MOS_TEMP_Pin GPIO_PIN_4
#define MOS_TEMP_GPIO_Port GPIOA
#define CR_ADC_Pin GPIO_PIN_5
#define CR_ADC_GPIO_Port GPIOA
#define MOT_TEMP_Pin GPIO_PIN_6
#define MOT_TEMP_GPIO_Port GPIOA
#define PRESS_SENSE_Pin GPIO_PIN_7
#define PRESS_SENSE_GPIO_Port GPIOA
#define LEVEL_SENSE_Pin GPIO_PIN_0
#define LEVEL_SENSE_GPIO_Port GPIOB
#define PROXI_SENSE_Pin GPIO_PIN_1
#define PROXI_SENSE_GPIO_Port GPIOB
#define DATA_LED_Pin GPIO_PIN_12
#define DATA_LED_GPIO_Port GPIOB
#define UP_SW_Pin GPIO_PIN_13
#define UP_SW_GPIO_Port GPIOB
#define DOWN_SW_Pin GPIO_PIN_14
#define DOWN_SW_GPIO_Port GPIOB
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
