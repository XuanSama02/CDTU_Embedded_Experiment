#ifndef _BSP_FLOWMETER_H_
#define _BSP_FLOWMETER_H_

#include "main.h"
#include "stdbool.h"

/*
STM32_HAL FLowmeter XuanLib
2022/06/25
changelog：
1.0：霍尔水流量传感器驱动
*/

/**
 * @brief 霍尔水流量计句柄
 * 
 */
typedef struct
{
    bool Enable;
    uint32_t Counter;
}Flowmeter_HandleTypeDef;

extern Flowmeter_HandleTypeDef YMX_Flowmeter;

#endif
