#include "bsp_f103.h"

/**
 * @brief 控制LED亮灭
 * 
 * @param LED_COLOR LED颜色
 * @param LED_Status LED状态(ON/OFF)
 */
void F103_LED(bool LED_COLOR, bool LED_Status)
{
    if(LED_COLOR == LED_COLOR_GREEN)
    {
        if(LED_Status == ON)
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
        else  //LED_Status == OFF
            HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
    }
    else  //LED_COLOR == LED_COLOR_RED
    {
        if(LED_Status == ON)
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
        else  //LED_Status == OFF
            HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
    }
}

/**
 * @brief 控制蜂鸣器
 * 
 * @param BEEP_Status 蜂鸣器状态(ON/OFF)
 */
void F103_BEEP(bool BEEP_Status)
{
    if(BEEP_Status == ON)
        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
}

/**
 * @brief HAL库中断回调函数
 * 
 * @param GPIO_Pin 
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch(GPIO_Pin)
    {
        case KEY_UP_Pin:  //Flow_UI传入参数KEY_UP_Pin
        {
            HAL_NVIC_DisableIRQ(KEY_UP_EXTI_IRQn);
            for(uint16_t nCount=50; nCount!=0; nCount--)
                Delay_us(1000);
            if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == GPIO_PIN_SET)
                Flow_UI_Command(GPIO_Pin);
            HAL_NVIC_EnableIRQ(KEY_UP_EXTI_IRQn);
        }break;
        case KEY_01_Pin:  //Flow_UI传入参数KEY_01_Pin
        {
            HAL_NVIC_DisableIRQ(KEY_01_EXTI_IRQn);
            for(uint16_t nCount=50; nCount!=0; nCount--)
                Delay_us(1000);
            if(HAL_GPIO_ReadPin(KEY_01_GPIO_Port, KEY_01_Pin) == GPIO_PIN_RESET)
                Flow_UI_Command(GPIO_Pin);
            HAL_NVIC_EnableIRQ(KEY_01_EXTI_IRQn);
        }break;
        case KEY_02_Pin:  //Flow_UI传入参数KEY_02_Pin
        {
            
            HAL_NVIC_DisableIRQ(KEY_02_EXTI_IRQn);
            for(uint16_t nCount=50; nCount!=0; nCount--)
                Delay_us(1000);
            if(HAL_GPIO_ReadPin(KEY_02_GPIO_Port, KEY_02_Pin) == GPIO_PIN_RESET)
                Flow_UI_Command(GPIO_Pin);
            HAL_NVIC_EnableIRQ(KEY_02_EXTI_IRQn);
        }break;
        case Flowmeter_Pin:  //霍尔传感器产生下降沿
        {
            if(YMX_Flowmeter.Enable == true)
            {
                YMX_Flowmeter.Counter++;
                if(YMX_Flowmeter.Counter >= YMX_Flowmeter.Counter_Target)  //到达目标计数器
                {
                    Flow_Pump(OFF);
                    Flow_Valve(OFF);
                    YMX_Flowmeter.Enable = false;                          //使能标志位：不使能
                    YMX_Flowmeter.Status = 2;                              //状态标志位：工作完成
                }
            }
        }break;
    }
}
