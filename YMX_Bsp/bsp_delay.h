#ifndef _BSP_DELAY_H_
#define _BSP_DELAY_H_

#include "main.h"

/*
STM32_HAL Delay XuanLib V1.0
2022/05/30
changelog：实现两种延时函数
*/

void Delay_ms(uint16_t nms);
void Delay_us(uint32_t nus);

#endif
