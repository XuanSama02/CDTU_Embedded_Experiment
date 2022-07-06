#ifndef _BSP_USART_H_
#define _BSP_USART_H_

#include "usart.h"
#include "stdio.h"

/*
https://github.com/XuanSama02
STM32_HAL USART XuanLib V1.1
2022/05/31
changelog：重定义printf函数实现对UART1串口的输出
1.需要在MDK中勾选：Use MicroLib
2.注意中文编码
*/

#ifdef __GNUC__
  #define USART1_printf int __io_putchar(int ch)
#else
  #define USART1_printf int fputc(int ch, FILE *f)
#endif

#endif
