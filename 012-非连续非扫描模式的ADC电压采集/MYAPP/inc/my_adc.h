#ifndef __MYADC_H__
#define __MYADC_H__
#include "stm32f10x.h"

//adc初始化
void MADC_Init(void);
//获取电压值
float Get_ValueV(void);

#endif
