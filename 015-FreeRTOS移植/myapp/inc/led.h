#ifndef __LED_H__
#define __LED_H__
#include "stm32f10x.h"

#define LED_RCC_CLOCK RCC_APB2Periph_GPIOC
#define LED_GPIO GPIOC
#define LED_GPIO_PIN GPIO_Pin_13

/**
  * 端口初始化
  * 步骤：1.使能时钟 2.设置GPIO_Init初始化 3.配置端口模式
*/
void led_init(void);

//4.设置高低电平
void open(void);//输出低电平
void close(void);//输出高电平

#endif
