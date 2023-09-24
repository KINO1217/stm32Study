#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
#include "stm32f10x_it.h"

#define KEY_GPIO GPIOA
#define KEY_GPIO_PIN GPIO_Pin_1

//按键初始化
void Key_Init(void);

//获取按键值
int Get_Key_Value(void);

#endif
