#ifndef _BSP_TM1638_H_
#define _BSP_TM1638_H_

#include "main.h"
#include "stdio.h"
#include "stdbool.h"

/*
STM32_HAL TM1638 XuanLib V1.0
2022/06/06
changelog：
1.0：实现对TM1638芯片的输出控制
1.1：修改SEG->SEG，默认关闭RTC功能，重构引脚操作函数
*/

//使用RTC功能
#define RTC_DISABLE
//TM1638引脚配置
#define TM1638_STB_PORT TM1638_STB_GPIO_Port
#define TM1638_CLK_PORT TM1638_CLK_GPIO_Port
#define TM1638_DIO_PORT TM1638_DIO_GPIO_Port
#define TM1638_STB_PIN  TM1638_STB_Pin
#define TM1638_CLK_PIN  TM1638_CLK_Pin
#define TM1638_DIO_PIN  TM1638_DIO_Pin
//TM1638指令集
#define	COMMAND_DATA  0X40  //0100 0000
#define COMMAND_KEY   0x42  //0100 0010
#define COMMAND_TRANS 0x44  //0100 0100
#define	COMMAND_DISP  0x80  //1000 0000
#define	COMMAND_ADDR  0XC0  //1100 0000
//用于TM1638_SEG函数不使用小数点
#define Point_None 0xFF

extern uint8_t SEG_Num[];  //数字表
extern uint8_t SEG_NumP[];  //带小数点数字表
extern uint8_t SEG_Eng[];  //英文字母
extern uint8_t SEG_OFF;  //关闭数码管

//引脚操作函数
void TM1638_STB(GPIO_PinState Status);
void TM1638_CLK(GPIO_PinState Status);
void TM1638_DIO(GPIO_PinState Status);

void TM1638_Init(void);  //初始化函数
void TM1638_Write(uint8_t Data);  //写数据函数
void TM1638_Transmit(uint8_t Addr, uint8_t Data);  //指定地址写入数据
void TM1638_Command(uint8_t Cmd);  //发送命令字

void TM1638_Brightness(uint8_t Brightness);  //亮度调节函数
void TM1638_LED(uint8_t Status);  //控制全部LED灯
void TM1638_SEG(long Number, uint8_t Point);  //控制全部数码管
void TM1638_SEG_OFF(uint8_t SEG_Position);  //关闭单个数码管
void TM1638_SEG_Single(uint8_t SEG_Position, uint8_t SEG_Show, bool SEG_Point);  //控制单个数码管
void TM1638_SEG_English(uint8_t SEG_Position, int SEG_ASCII);  //控制单个数码管显示英文字母

#ifdef RTC_ENABLE
#include "bsp_rtc.h"
void TM1638_RTC(void);  //显示时间
#endif

#endif
