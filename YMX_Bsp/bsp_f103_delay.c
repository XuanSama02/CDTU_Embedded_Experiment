#include "bsp_f103_delay.h"

/**
 * @brief 微秒级延时函数(支持RTOS)
 * 
 * @param nus 微秒数
 */
void Delay_us(uint16_t nus)
{
    uint16_t Conter = 0xFFFF-nus-5;
    __HAL_TIM_SET_COUNTER(&htim7, Conter);  //设置重装寄存器
    HAL_TIM_Base_Start(&htim7);
    while(Conter < 0xFFFF-6)
        Conter = __HAL_TIM_GET_COUNTER(&htim7);
    HAL_TIM_Base_Stop(&htim7);
}
