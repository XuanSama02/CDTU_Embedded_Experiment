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

/*
水流量计NPN脉冲
F(频率Hz) = 9.4 * Q(L/min)  ->  约156mL/一次脉冲
*/


#define ON  (bool)1
#define OFF (bool)0

//水泵
#define FLow_Pump_PORT FLow_Pump_GPIO_Port
#define FLow_Pump_PIN  Flow_Pump_Pin
//电磁阀
#define FLow_Valve_PORT FLow_Valve_GPIO_Port
#define FLow_Valve_PIN  Flow_Value_Pin
//继电器(CH1 -> 水泵，CH2 -> 电磁阀)
#define Flow_Relay_CH1_PORT Flow_Relay_CH1_GPIO_Port
#define Flow_Relay_CH1_PIN  Flow_Relay_CH1_Pin
#define Flow_Relay_CH2_PORT Flow_Relay_CH2_GPIO_Port
#define Flow_Relay_CH2_PIN  Flow_Relay_CH2_Pin
#define Relay_CH1 (bool)0
#define Relay_CH2 (bool)1

/**
 * @brief 霍尔水流量计句柄
 * 
 */
typedef struct
{
    bool Enable;              //使能标志位
    uint8_t Status;           //状态标志位(0:设定中，1:工作中，2:工作完成)
    uint32_t Counter;         //计数器
    uint32_t Counter_Target;  //目标计数器
    uint32_t Water_Target;    //目标出水量
}Flowmeter_HandleTypeDef;

extern Flowmeter_HandleTypeDef YMX_Flowmeter;

//UI函数

void FLow_UI(void);                             //UI界面函数
void Flow_UI_Setting(void);                     //设置出水量
void Flow_UI_Running(void);                     //水泵运行中
void Flow_UI_Finished(void);                    //完成任务

//功能函数

void Flow_Water(uint16_t mL);                  //输出指定毫升的水

//硬件控制

void FLow_Pump(bool Status);                   //控制水泵
void Flow_Valve(bool Status);                  //控制电磁阀
void FLow_Relay(bool Relay_CHx, bool Status);  //控制继电器

#endif
