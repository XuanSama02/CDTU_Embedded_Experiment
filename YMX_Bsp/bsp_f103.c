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
