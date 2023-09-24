#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"

#define LED_GPIO GPIOA
#define LED_GPIO_PIN GPIO_Pin_4

/**
  * 端口初始化
  * 步骤：1.使能时钟 2.设置GPIO_Init初始化 3.配置端口模式
*/
void Led_Init(void);

//4.设置高低电平
void Led_On(void);//输出低电平
void Led_Off(void);//输出高电平

#endif
