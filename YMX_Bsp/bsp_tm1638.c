#include "bsp_tm1638.h"

//共阴数码管显示代码
uint8_t SEG_Num[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
uint8_t SEG_NumP[] = {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF};
uint8_t SEG_Eng[] = {0x77,0x7C,0x39,0x5E,0x79,0x71};  //AbCdEF
uint8_t SEG_OFF = 0x00;

/**
 * @brief 初始化TM1638
 * 
 */
void TM1638_Init(void)
{
    TM1638_Brightness(2);  //亮度：2档
    TM1638_Command(COMMAND_DATA);  //采用地址自动+1
    TM1638_STB(GPIO_PIN_RESET);
    TM1638_Write(COMMAND_ADDR);  //设置起始地址
    //传送16个字节的数据
    for(uint8_t nCount=0; nCount<16; nCount++)
        TM1638_Write(0x00);
    TM1638_STB(GPIO_PIN_SET);
}

/**
 * @brief 向TM1638写入数据
 * 
 * @param Data 数据
 */
void TM1638_Write(uint8_t Data)
{
    for(uint8_t nCount=0; nCount<8; nCount++)
    {
        TM1638_CLK(GPIO_PIN_RESET);
        if(Data&0x01)
            TM1638_DIO(GPIO_PIN_SET);
        else
            TM1638_DIO(GPIO_PIN_RESET);
        Data>>=1;
        TM1638_CLK(GPIO_PIN_SET);
    }
}

/**
 * @brief 向指定地址发送数据
 * 
 * @param Add 地址
 * @param Data 数据
 */
void TM1638_Transmit(uint8_t Addr, uint8_t Data)
{
    TM1638_Command(COMMAND_TRANS);
    TM1638_STB(GPIO_PIN_RESET);
    TM1638_Write(COMMAND_ADDR|Addr);
    TM1638_Write(Data);
    TM1638_STB(GPIO_PIN_SET);
}

/**
 * @brief 向TM1638传输命令字
 * 
 * @param Cmd 命令字
 */
void TM1638_Command(uint8_t Cmd)
{
    TM1638_STB(GPIO_PIN_RESET);
    TM1638_Write(Cmd);
    TM1638_STB(GPIO_PIN_SET);
}

/**
 * @brief 读取TM1638数据
 * 
 * @return uint8_t 数据值
 */
uint8_t TM1638_Read(void)
{
    uint8_t temp = 0;
    TM1638_DIO(GPIO_PIN_SET);  //设置为输入
    for(uint8_t nCount=0; nCount<8; nCount++);
    {
        temp>>=1;
        TM1638_CLK(GPIO_PIN_RESET);
        if(HAL_GPIO_ReadPin(TM1638_DIO_PORT, TM1638_DIO_PIN) == SET)
            temp|=COMMAND_DATA;
        TM1638_CLK(GPIO_PIN_SET);
    }
    return temp;
}

/**
 * @brief 调节TM1638亮度，8档调节(1-8)
 * 
 * @param Brightness 亮度
 */
void TM1638_Brightness(uint8_t Brightness)
{
    switch(Brightness)
    {
        case 1:TM1638_Command(0x88);break;
        case 2:TM1638_Command(0x89);break;
        case 3:TM1638_Command(0x8a);break;
        case 4:TM1638_Command(0x8b);break;
        case 5:TM1638_Command(0x8c);break;
        case 6:TM1638_Command(0x8d);break;
        case 7:TM1638_Command(0x8e);break;
        case 8:TM1638_Command(0x8f);break;
    }
}

/**
 * @brief 控制全部LED灯
 * 
 */
void TM1638_LED(uint8_t Status)
{
    for(uint8_t nCount=0; nCount<8; nCount++)
    {
        if(Status&(1<<nCount))
            TM1638_Transmit(2*nCount+1, 1);
        else
            TM1638_Transmit(2*nCount+1, 0);
    }
}

/**
 * @brief 控制全部数码管显示数字
 * 
 * @param SEG_Show 要显示的数字表
 * @param SEG_Point 要显示的小数点表
 */
void TM1638_SEG(long Number, uint8_t Point)
{
    uint8_t Number_Form[8];
    Number_Form[0] = Number/10000000;
    Number_Form[1] = (Number/1000000)%10;
    Number_Form[2] = (Number/100000)%10;
    Number_Form[3] = (Number/10000)%10;
    Number_Form[4] = (Number/1000)%10;
    Number_Form[5] = (Number/100)%10;
    Number_Form[6] = (Number/10)%10;
    Number_Form[7] = Number%10;
    for(uint8_t nCount=1; nCount<=8; nCount++)
        TM1638_SEG_Single(nCount, Number_Form[nCount-1], 0);
    if(Point>=1 && Point<=8)
        TM1638_SEG_Single(Point, Number_Form[Point-1], 1);
}

/**
 * @brief 关闭单个数码管
 * 
 * @param SEG_Position 关闭的数码管
 */
void TM1638_SEG_OFF(uint8_t SEG_Position)
{
    TM1638_Transmit((SEG_Position-1)*2, SEG_OFF);
}

/**
 * @brief 控制单个数码管显示数字
 * 
 * @param SEG_Position 控制的数码管
 * @param SEG_Show 显示的数字
 * @param SEG_Point 是否带有小数点
 */
void TM1638_SEG_Single(uint8_t SEG_Position, uint8_t SEG_Show, bool SEG_Point)
{
    if(SEG_Point == 0)
        TM1638_Transmit((SEG_Position-1)*2, SEG_Num[SEG_Show]);
    else
        TM1638_Transmit((SEG_Position-1)*2, SEG_NumP[SEG_Show]);
}

/**
 * @brief 控制单个数码管显示英文字母
 * 
 * @param SEG_Position 控制的数码管
 * @param SEG_ASCII 显示的小写英文字母的ASCII码
 */
void TM1638_SEG_English(uint8_t SEG_Position ,int SEG_ASCII)
{
    switch(SEG_ASCII)
    {
        case 'a':TM1638_Transmit((SEG_Position-1)*2, SEG_Eng[0]);break;
        case 'b':TM1638_Transmit((SEG_Position-1)*2, SEG_Eng[1]);break;
        case 'c':TM1638_Transmit((SEG_Position-1)*2, SEG_Eng[2]);break;
        case 'd':TM1638_Transmit((SEG_Position-1)*2, SEG_Eng[3]);break;
        case 'e':TM1638_Transmit((SEG_Position-1)*2, SEG_Eng[4]);break;
        case 'f':TM1638_Transmit((SEG_Position-1)*2, SEG_Eng[5]);break;
    }
}

#ifdef RTC_ENABLE
/**
 * @brief 数码管显示时间
 * 
 * @note 需要FreeRTOS
 */
void TM1638_RTC(void)
{
    long Time = 0;
    Time += YMX_Time.Hours * 10000;
    Time += YMX_Time.Minutes * 100;
    Time += YMX_Time.Seconds;
    TM1638_SEG(Time, 6);
    osDelay(500);
    TM1638_SEG(Time, Point_None);
    osDelay(500);
}
#endif

/***************************************************/
/********************引脚操作函数********************/
/***************************************************/
void TM1638_STB(GPIO_PinState Status)
{
    if(Status == GPIO_PIN_SET)
        HAL_GPIO_WritePin(TM1638_STB_PORT, TM1638_STB_PIN, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(TM1638_STB_PORT, TM1638_STB_PIN, GPIO_PIN_RESET);
}

void TM1638_CLK(GPIO_PinState Status)
{
    if(Status == GPIO_PIN_SET)
        HAL_GPIO_WritePin(TM1638_CLK_PORT, TM1638_CLK_PIN, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(TM1638_CLK_PORT, TM1638_CLK_PIN, GPIO_PIN_RESET);
}

void TM1638_DIO(GPIO_PinState Status)
{
    if(Status == GPIO_PIN_SET)
        HAL_GPIO_WritePin(TM1638_DIO_PORT, TM1638_DIO_PIN, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(TM1638_DIO_PORT, TM1638_DIO_PIN, GPIO_PIN_RESET);
}
