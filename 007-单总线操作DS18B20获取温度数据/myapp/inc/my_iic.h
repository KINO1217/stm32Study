#ifndef __MY_IIC_H__
#define __MY_IIC_H__
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define SCL PBout(14)
#define SDA PBout(15)

#define SDA_STATE PBin(15)

#define ACK 0   //Ӧ���ź�
#define NACK 1  //��Ӧ���ź�

//IIC��ʼ���˿�
void IIC_Init(void);
//IIC��ʱ5us
void IIC_Delay_Us(void);

static void sda_out(void);
static void sda_in(void);

//IIC��ʼ�ź�
void IIC_Start(void);
//�����ź�
void IIC_Stop(void);
//����Ӧ��ӻ�
void IIC_ACK(u8 ack);
//�ӻ�Ӧ������
u8 IIC_Check_ACK(void);
//����һ���ֽ�����
void IIC_Send_Byte(u8 byte_data);
//����һ�ֽ�����
u8 IIC_Read_Byte(void);

#endif
