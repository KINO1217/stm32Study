#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
#include "stm32f10x_it.h"

#define KEY_GPIO GPIOA
#define KEY_GPIO_PIN GPIO_Pin_1

//������ʼ��
void Key_Init(void);

//��ȡ����ֵ
int Get_Key_Value(void);

#endif
