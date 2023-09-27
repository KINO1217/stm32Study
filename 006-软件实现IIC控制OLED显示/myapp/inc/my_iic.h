#ifndef __MY_IIC_H__
#define __MY_IIC_H__
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define SCL PBout(14)
#define SDA PBout(15)

#define SDA_STATE PBin(15)

#define ACK 0   //应答信号
#define NACK 1  //不应答信号

//IIC初始化端口
void IIC_Init(void);
//IIC延时5us
void IIC_Delay_Us(void);

static void sda_out(void);
static void sda_in(void);

//IIC开始信号
void IIC_Start(void);
//结束信号
void IIC_Stop(void);
//主机应答从机
void IIC_ACK(u8 ack);
//从机应答主机
u8 IIC_Check_ACK(void);
//发送一个字节数据
void IIC_Send_Byte(u8 byte_data);
//接收一字节数据
u8 IIC_Read_Byte(void);

#endif
