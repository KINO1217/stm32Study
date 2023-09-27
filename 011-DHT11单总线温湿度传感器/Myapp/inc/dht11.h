#ifndef __DHT11_H__
#define __DHT11_H__
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define DHT11_OUT PAout(11)
#define DHT11_IN PAin(11)

//初始化
void DHT11_Init(void);
//获取温湿度
u8 DHT11_Get(u8* temp,u8* humi);

#endif
