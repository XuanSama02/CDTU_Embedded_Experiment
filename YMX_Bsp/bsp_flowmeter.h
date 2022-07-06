#ifndef _BSP_FLOWMETER_H_
#define _BSP_FLOWMETER_H_

#include "main.h"
#include "stdbool.h"

/*
https://github.com/XuanSama02
STM32_HAL Flowmeter XuanLib
2022/07/06
changelog：
1.0：霍尔水流量传感器驱动
2.0：实现定量提供清水溶剂的功能
*/

/*
水流量计NPN脉冲
F(频率Hz) = 9.4 * Q(L/min)
引脚接线：
Flow_Relay_CH1 -> PE9
Flow_Relay_CH2 -> PE10
Flowmeter      -> PE11
TM1638_STB     -> PE12
TM1638_CLK     -> PE13
TM1638_DIO     -> PE14
*/

/*
按键逻辑：
设定状态：KEY_01 = 减少200mL出水量
         KEY_02 = 增加200mL出水量
         KEY_UP = 开始出水
工作状态：无功能
完成状态：KEY_UP = 复位
*/

#define ON  (bool)1
#define OFF (bool)0

#define Water_Step 25  //一次脉冲2.5mL

//水泵
#define Flow_Pump_PORT Flow_Pump_GPIO_Port
#define Flow_Pump_PIN  Flow_Pump_Pin
//电磁阀
#define Flow_Valve_PORT Flow_Valve_GPIO_Port
#define Flow_Valve_PIN  Flow_Valve_Pin
//继电器(CH1 -> 水泵，CH2 -> 电磁阀)

/**
 * @brief TM1638模块句柄
 * 
 */
typedef struct
{
    long SEG;      //数码管显示
    uint16_t LED;  //LED状态
}TM1638_HandleTypeDef;
extern TM1638_HandleTypeDef YMX_TM1638;

/**
 * @brief 霍尔水流量计句柄
 * 
 */
typedef struct
{
    bool Enable;              //使能标志位
    uint8_t Status;           //状态标志位(0:设定中，1:工作中，2:工作完成)
    uint32_t Counter;         //当前计数器
    uint32_t Counter_Target;  //目标计数器
    uint32_t Water_Target;    //目标出水量
}Flowmeter_HandleTypeDef;
extern Flowmeter_HandleTypeDef YMX_Flowmeter;

//UI函数

void Flow_UI_Display(void);                     //UI界面显示函数
void Flow_UI_Command(uint16_t GPIO_Pin);        //UI界面响应函数

//功能函数

void Flow_Water(uint16_t mL);                  //输出指定毫升的水

//底层硬件控制

void Flow_Pump(bool Status);                   //控制水泵
void Flow_Valve(bool Status);                  //控制电磁阀

#endif
