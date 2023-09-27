#include "timer.h"

static int timer_flag=0;

void Timer_Init(u16 arr)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能时钟
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数模式，向上计数
    TIM_TimeBaseInitStruct.TIM_Period=arr-1;//自动重装载值,计数时间(TIM_Period+1)/Tout=10000*0.1ms=1s
    TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;//TimerxClk=72MHz=APB1Clk*2     Tout=TimerxClk/TIM_Prescaler+1
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//初始化timer配置timer参数,配置时基参数
    
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//开启定时器中断
    
    //配置定时器中断NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//主优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//子优先级
    NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    
    TIM_Cmd(TIM2,ENABLE);//使能/开启定时器
}

//定时器中断函数
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){//发生中断
        timer_flag=1;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志
    }
}

int Get_Flag(void)
{
    if(timer_flag==1){
        timer_flag=0;
        return 1;
    }
    return 0;
}
