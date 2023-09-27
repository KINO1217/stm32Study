#include "pwm.h"

void Pwm_Init(void)
{
    //1.ʹ�ܶ�ʱ��x�����IO��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//PAO - Timer2CH1
    
    //4.��ʼ����ʱ�� 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseInitStruct.TIM_Period=20000-1;
    TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;//20ms
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    //TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;//�߼���ʱ��ʹ��
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
    
    //2.��ʼ��IO�ڵĸ��ù���
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�����������ģʽ
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //5.��ʼ������Ƚϲ���
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//PWMģʽ��ģʽ1 ���ϼ���ʱ��CNT < CCR1 �������Ч��ƽ�����������Ч��ƽ
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//�Ƚ�������ԣ�������Ч��ƽΪ�ߵ�ƽ���ǵ͵�ƽ
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
    TIM_OCInitStruct.TIM_Pulse = 500;//�Ƚ�ֵ��дCCRx
    TIM_OC1Init(TIM2,&TIM_OCInitStruct);//CH1ʹ��OC1
    
    //6.ʹ��Ԥװ�ؼĴ���
    TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
    
    //7.ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ��ʹ�ȽϼĴ���ARR������Ч�������¸��Ƚ�������Ч
    TIM_ARRPreloadConfig(TIM2,ENABLE);
    
    //8.ʹ�ܶ�ʱ��
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
