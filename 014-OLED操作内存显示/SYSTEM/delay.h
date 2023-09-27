#ifndef __DELAY_H__
#define __DELAY_H__
#include "stm32f10x.h"

//滴答定时器初始化
void Delay_Init(void);

//计时微妙
void Delay_Us(u32 nus);

//计时毫秒
void Delay_Ms(u16 nms);

#endif
