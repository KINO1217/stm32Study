#include "timer.h"

static int timer_flag=0;

void Timer_Init(u16 arr)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ��ʱ��
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//����ģʽ�����ϼ���
    TIM_TimeBaseInitStruct.TIM_Period=arr-1;//�Զ���װ��ֵ,����ʱ��(TIM_Period+1)/Tout=10000*0.1ms=1s
    TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;//TimerxClk=72MHz=APB1Clk*2     Tout=TimerxClk/TIM_Prescaler+1
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);//��ʼ��timer����timer����,����ʱ������
    
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//������ʱ���ж�
    
    //���ö�ʱ���ж�NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//�����ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//�����ȼ�
    NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStruct);
    
    TIM_Cmd(TIM2,ENABLE);//ʹ��/������ʱ��
}

//��ʱ���жϺ���
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){//�����ж�
        timer_flag=1;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//����жϱ�־
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
