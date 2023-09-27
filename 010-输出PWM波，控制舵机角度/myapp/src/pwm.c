#include "pwm.h"

void Pwm_Init(void)
{
    //1.使能定时器x和相关IO口时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//PAO - Timer2CH1
    
    //4.初始化定时器 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInitStruct.TIM_Period=20000-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;//20ms
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    //TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;//高级定时器使用
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
    
    //2.初始化IO口的复用功能
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //5.初始化输出比较参数
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//PWM模式，模式1 向上计数时：CNT < CCR1 则输出有效电平，否则输出无效电平
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//比较输出极性，设置有效电平为高电平还是低电平
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
    TIM_OCInitStruct.TIM_Pulse = 500;//比较值，写CCRx
    TIM_OC1Init(TIM2,&TIM_OCInitStruct);//CH1使用OC1
    
    //6.使能预装载寄存器
    TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
    
    //7.使能自动重装载的预装载寄存器允许位，使比较寄存器ARR立即生效，否则下个比较周期生效
    TIM_ARRPreloadConfig(TIM2,ENABLE);
    
    //8.使能定时器
    TIM_Cmd(TIM2,ENABLE);
}

void Set_Angle(float angle)
{
    int ccrCount;
    if(angle!=180.0)
        ccrCount = (int)ceil(11.11*(angle+5)+500);
    else
        ccrCount = (int)ceil(11.11*angle+500);
    TIM_SetCompare1(TIM2,ccrCount);
}
