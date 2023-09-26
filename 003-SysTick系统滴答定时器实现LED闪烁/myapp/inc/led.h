#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"

#define LED_GPIO GPIOA
#define LED_GPIO_PIN GPIO_Pin_4

/**
  * �˿ڳ�ʼ��
  * ���裺1.ʹ��ʱ�� 2.����GPIO_Init��ʼ�� 3.���ö˿�ģʽ
*/
void Led_Init(void);

//4.���øߵ͵�ƽ
void Led_On(void);//����͵�ƽ
void Led_Off(void);//����ߵ�ƽ

#endif
