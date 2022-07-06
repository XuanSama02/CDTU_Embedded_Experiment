#ifndef _BSP_F103_H_
#define _BSP_F103_H_

#include "main.h"
#include "stdbool.h"
#include "cmsis_os.h"

/*
https://github.com/XuanSama02
STM32_HAL F103 Elite XuanLib
2022/06/22
changelog：
1.0：正点原子F103 Elite开发板
*/

#define ON  (bool)1
#define OFF (bool)0

#define LED_COLOR_RED   (bool)1
#define LED_COLOR_GREEN (bool)0

void F103_LED(bool LED_COLOR, bool LED_Status);  //控制LED亮灭
void F103_BEEP(bool BEEP_Status);                //控制蜂鸣器

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);  //中断回调函数

#endif
