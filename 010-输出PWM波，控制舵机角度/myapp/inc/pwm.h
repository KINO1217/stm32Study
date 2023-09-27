#ifndef __PWM_H__
#define __PWM_H__
#include "stm32f10x.h"
#include <math.h>

void Pwm_Init(void);
void Set_Angle(float angle);

#endif
