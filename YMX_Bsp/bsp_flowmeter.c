#include "bsp_flowmeter.h"

TM1638_HandleTypeDef YMX_TM1638 = {0};
Flowmeter_HandleTypeDef YMX_Flowmeter = {0};

/**
 * @brief UI界面显示函数(调用一次刷新一次显示)
 * 
 */
void Flow_UI_Display(void)
{
    if(YMX_Flowmeter.Status == 0)  //设定中
    {
        TM1638_SEG(YMX_TM1638.SEG, Point_None);  //显示当前设定量
        TM1638_LED(YMX_TM1638.LED);
    }
    else if(YMX_Flowmeter.Status == 1)  //工作中
    {
        long temp = 0;
        temp += YMX_Flowmeter.Water_Target * 10000;      //添加高4位显示值
        temp += (YMX_Flowmeter.Counter * Water_Step)/10;      //添加低4位显示值
        TM1638_SEG(temp, Point_None);                    //高4位显示目标出水量，低4位显示当前出水量(mL)
        TM1638_LED(YMX_TM1638.LED);
    }
}

/**
 * @brief UI界面响应函数(逻辑：根据传入中断引脚与状态位标志综合判断)
 * 
 * @param GPIO_Pin GPIO中断引脚号(KEY_UP_Pin/KEY_01_Pin/KEY_02_Pin)
 */
void Flow_UI_Command(uint16_t GPIO_Pin)
{
    switch(GPIO_Pin)
    {
        case KEY_UP_Pin:
        {
            switch(YMX_Flowmeter.Status)
            {
                case 0:
                {
                    Flow_Water((uint16_t)YMX_TM1638.SEG);  //开始出水
                }break;
                case 1:
                {
                    ;
                }break;
                case 2:
                {
                    ;
                }break;
            }
        }break;
        case KEY_01_Pin:
        {
            switch(YMX_Flowmeter.Status)
            {
                case 0:
                {
                    if(YMX_TM1638.SEG >= 0)
                        YMX_TM1638.SEG -= 100;
                }break;
                case 1:
                {
                    ;
                }break;
                case 2:
                {
                    ;
                }break;
            }
        }break;
        case KEY_02_Pin:
        {
            switch(YMX_Flowmeter.Status)
            {
                case 0:
                {
                    if(YMX_TM1638.SEG <= 5000)
                        YMX_TM1638.SEG += 100;
                }break;
                case 1:
                {
                    ;
                }break;
                case 2:
                {
                    YMX_Flowmeter.Status = 0;
                    YMX_Flowmeter.Enable = false;
                    YMX_Flowmeter.Counter = 0;
                    YMX_Flowmeter.Counter_Target = 0;
                }break;
            }
        }break;
    }
}

/**
 * @brief 输出指定毫升的水(0-9900)
 * 
 * @param mL 水量(毫升)
 */
void Flow_Water(uint16_t mL)
{
    //对水流量计清零
    YMX_Flowmeter.Enable = false;           //使能标志位：不使能
    YMX_Flowmeter.Counter = 0;              //清零计数器
    //控制水流量计
    YMX_Flowmeter.Water_Target = mL;        //写入目标出水量
    uint16_t nCount = (mL*10)/Water_Step;   //计算需要的脉冲数
    YMX_Flowmeter.Counter_Target = nCount;  //写入目标脉冲数
    Flow_Valve(ON);                         //打开电磁阀
    Flow_Pump(ON);                          //打开水泵
    YMX_Flowmeter.Enable = true;            //使能标志位：使能
    YMX_Flowmeter.Status = 1;               //状态标志位：工作中
}

/**
 * @brief 控制水泵
 * 
 * @param Status 水泵状态(ON/OFF)
 */
void Flow_Pump(bool Status)
{
    if(Status == ON)
        HAL_GPIO_WritePin(Flow_Pump_PORT, Flow_Pump_PIN, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(Flow_Pump_PORT, Flow_Pump_PIN, GPIO_PIN_RESET);
}

/**
 * @brief 控制电磁阀
 * 
 * @param Status 电磁阀状态(ON/OFF)
 */
void Flow_Valve(bool Status)
{
    if(Status == ON)    
        HAL_GPIO_WritePin(Flow_Valve_PORT, Flow_Valve_PIN, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(Flow_Valve_PORT, Flow_Valve_PIN, GPIO_PIN_RESET);
}
