#ifndef __DELAY_H__
#define __DELAY_H__
#include "stm32f10x.h"

//�δ�ʱ����ʼ��
void Delay_Init(void);

//��ʱ΢��
void Delay_Us(u32 nus);

//��ʱ����
void Delay_Ms(u16 nms);

#endif
