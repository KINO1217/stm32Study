#include "delay.h"

int fac_us=0;
int fac_ms=0;

void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//配置时钟源
    fac_us=SystemCoreClock/8/1000000;//计算1us的计数周期,9个周期
    fac_ms=fac_us*1000;//计算1ms的计数周期9000个周期
}

void Delay_Us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = fac_us*nus;     //自动重装载值寄存器，当计数到0时，将被重装载的值
    SysTick->VAL = 0x00;            //当前值寄存器，返回当前倒计数的值，写它则使之清零
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //使能,开始计数
    do{
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));   //使能位没有清零，并且COUNTFLAG=0（没有数完）
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;          //失能，停止计数
    SysTick->VAL = 0x00;
}

void Delay_Ms(u16 nms)
{
    if(nms>1864){//最大计数ms数24位
        return;
    }
    
    u32 temp;
    SysTick->LOAD = (u32)fac_ms*nms;     //自动重装载值寄存器，当计数到0时，将被重装载的值
    SysTick->VAL = 0x00;            //当前值寄存器，返回当前倒计数的值，写它则使之清零
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //使能,开始计数
    do{
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));   //使能位没有清零，并且COUNTFLAG=0（没有数完）
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;          //失能，停止计数
    SysTick->VAL = 0x00;
}
