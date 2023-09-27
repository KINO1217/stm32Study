#ifndef __DS18B20_H__
#define __DS18B20_H__
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#define DQ_IN PAin(0)
#define DQ_OUT PAout(0)

#define DQ_To_Out() {GPIOA->CRL&=0xFFFFFFF0;GPIOA->CRL|=3<<0;}
#define DQ_To_In() {GPIOA->CRL&=0xFFFFFFF0;GPIOA->CRL|=8<<0;}

//初始化DS18B20
void DS18B20_Init(void);
//改变引脚输出输入状态
//void DQ_To_In(void);
//void DQ_To_Out(void);
//复位初始化DS18B20
static u8 DS18B20_Rest(void);
//写一字节数据
static void DS18B20_Write_Byte(u8 cmd);
//读一字节数据
static u8 DS18B20_Read_Byte(void);
//开启温度转换命令
static void DS18B20_Start(void);
//读取温度数据
float DS18B20_Get_Temp(void);

#endif
