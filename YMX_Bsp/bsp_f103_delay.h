#ifndef _BSP_F411_DELAY_H_
#define _BSP_F411_DELAY_H_

#include "main.h"
#include "tim.h"

/*
STM32_HAL RTOS Delay XuanLib
2022/06/22
changelog：
1.0：利用TIM7实现FreeRTOS微秒级延时
*/

void Delay_us(uint16_t num);

#endif
