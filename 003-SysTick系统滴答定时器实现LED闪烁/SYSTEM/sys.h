#ifndef __SYS_H__
#define __SYS_H__
#include "stm32f10x.h"

//设置NVIC中断优先级位数，抢占式优先级，响应式优先级
void NVIC_Config(void);

#endif
