#include "bsp_delay.h"

/**
  * @brief  利用SysTick定时器实现毫秒级延时
  * @param  nms 延时毫秒数
  * @return void
  */
void Delay_ms(uint16_t nms)
{
  uint32_t temp;
  SysTick->LOAD = 9000*nms;  //72MHz，8分频后 = 9MHz， 除以9000 = 1KHz
  SysTick->VAL=0X00;  //清空计数器
  SysTick->CTRL=0X01;  //使能，减到零是无动作，采用外部时钟源
  do
  {
    temp=SysTick->CTRL;  //读取当前倒计数值
  }while((temp&0x01)&&(!(temp&1<<16)));  //等待时间到达 (temp&0x01 = 计时器已开启)，(temp&1<<16 = 时间未到达)
  SysTick->CTRL=0x00; //关闭计数器
  SysTick->VAL=0X00; //清空计数器
}

/**
  * @brief  利用SysTick定时器实现微秒级延时
  * @param  num 延时微秒数
  * @return void
  */
void Delay_us(uint32_t nus)
{
  uint32_t temp;
  SysTick->LOAD = 9*nus;  //72MHz，8分频后 = 9MHz， 除以9000 = 1KHz
  SysTick->VAL=0X00;
  SysTick->CTRL=0X01;
  do
  {
    temp=SysTick->CTRL;
  }while((temp&0x01)&&(!(temp&1<<16)));
  SysTick->CTRL=0x00;
  SysTick->VAL=0X00;
}
