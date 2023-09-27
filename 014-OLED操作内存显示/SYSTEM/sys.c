#include "sys.h"

void NVIC_Config(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级组
}
