#ifndef __UART_H__
#define __UART_H__
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stdio.h"
#include "string.h"

#define RECV_BUF_MAX_LEN 128

//��ʼ������
void UART_Init(void);

//������Ϣ
void Send_Data(USART_TypeDef* USARTx,u8* data,u16 data_len);

//�ص�����
extern void (*callback)(u8* , u16);

#endif
