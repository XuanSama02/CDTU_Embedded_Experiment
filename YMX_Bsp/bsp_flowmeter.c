#include "bsp_flowmeter.h"

Flowmeter_HandleTypeDef YMX_Flowmeter = {0};

/**
 * @brief UI界面函数
 * 
 */
void FLow_UI(void)
{
    switch(YMX_Flowmeter.Status)
    {
        case 0:FLow_UI_Setting();break;
        case 1:Flow_UI_Running();break;
        case 2:Flow_UI_Finished();break;
    }
}

/**
 * @brief 设置出水量
 * 
 */
void Flow_UI_Setting(void)
{
    TM1638_SEG((long)YMX_Flowmeter.Water_Target, Point_None);  //显示目标出水量
    TM1638_LED(0x00);
}

/**
 * @brief 水泵运行中
 * 
 */
void Flow_UI_Running(void)
{
    TM1638_SEG((long)YMX_Flowmeter.Counter*156, Point_None);  //显示当前出水量
    TM1638_LED(0xCC);
}

/**
 * @brief 完成任务
 * 
 */
void Flow_UI_Finished(void)
{
    TM1638_SEG((long)YMX_Flowmeter.Water_Target, Point_None);  //显示完成量
    TM1638_LED(0xFF);
}

/**
 * @brief 输出指定毫升的水
 * 
 * @param mL 水量(毫升)
 */
void Flow_Water(uint16_t mL)
{
    //对水流量计清零
    YMX_Flowmeter.Counter = 0;     //清零计数器
    YMX_Flowmeter.Enable = false;
    //控制水流量计
    uint16_t nCount = mL/156;      //计算需要的脉冲数
    Flow_Valve(ON);                //打开电磁阀
    FLow_Pump(ON);                 //打开水泵
    YMX_Flowmeter.Enable = true;   //使能水流量计
}

/**
 * @brief 控制水泵
 * 
 * @param Status 水泵状态(ON/OFF)
 */
void FLow_Pump(bool Status)
{
    if(Status == ON)
        FLow_Relay(Relay_CH1, ON);
    else
        FLow_Relay(Relay_CH1, OFF);
}

/**
 * @brief 控制电磁阀
 * 
 * @param Status 电磁阀状态(ON/OFF)
 */
void Flow_Valve(bool Status)
{
    if(Status == ON)    
        FLow_Relay(Relay_CH2, ON);
    else
        FLow_Relay(Relay_CH2, OFF);
}

/**
 * @brief 控制继电器状态
 * 
 * @param Relay_CHx 继电器通道(Relay_CH1/Relay_CH2)
 * @param Status 继电器通道状态(ON/OFF)
 */
void FLow_Relay(bool Relay_CHx, bool Status)
{
    if(Relay_CHx == Relay_CH1)
    {
        if(Status == ON);
            HAL_GPIO_WritePin(Flow_Relay_CH1_PORT, Flow_Relay_CH1_PIN, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(Flow_Relay_CH1_PORT, Flow_Relay_CH1_PIN, GPIO_PIN_SET);
    }
    else if(Relay_CHx == Relay_CH2)
    {
        if(Status == ON);
            HAL_GPIO_WritePin(Flow_Relay_CH2_PORT, Flow_Relay_CH1_PIN, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(Flow_Relay_CH2_PORT, Flow_Relay_CH1_PIN, GPIO_PIN_SET);
    }
}
