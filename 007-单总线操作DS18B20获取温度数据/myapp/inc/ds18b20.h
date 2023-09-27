#ifndef __DS18B20_H__
#define __DS18B20_H__
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"

#define DQ_IN PAin(0)
#define DQ_OUT PAout(0)

#define DQ_To_Out() {GPIOA->CRL&=0xFFFFFFF0;GPIOA->CRL|=3<<0;}
#define DQ_To_In() {GPIOA->CRL&=0xFFFFFFF0;GPIOA->CRL|=8<<0;}

//��ʼ��DS18B20
void DS18B20_Init(void);
//�ı������������״̬
//void DQ_To_In(void);
//void DQ_To_Out(void);
//��λ��ʼ��DS18B20
static u8 DS18B20_Rest(void);
//дһ�ֽ�����
static void DS18B20_Write_Byte(u8 cmd);
//��һ�ֽ�����
static u8 DS18B20_Read_Byte(void);
//�����¶�ת������
static void DS18B20_Start(void);
//��ȡ�¶�����
float DS18B20_Get_Temp(void);

#endif
