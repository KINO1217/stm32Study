#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"

#define LED_RCC_CLOCK RCC_APB2Periph_GPIOA
#define LED_GPIO GPIOA
#define LED_GPIO_PIN GPIO_Pin_4

/**
  * �˿ڳ�ʼ��
  * ���裺1.ʹ��ʱ�� 2.����GPIO_Init��ʼ�� 3.���ö˿�ģʽ
*/
void led_init(void);

//4.���øߵ͵�ƽ
void open(void);//����͵�ƽ
void close(void);//����ߵ�ƽ

#endif
