#include "key.h"

int key_value=0;

void Key_Init(void)
{
    //1. ʹ�����ţ��������š�
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = KEY_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  //��������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_GPIO,&GPIO_InitStruct);
    
    //2. ����AFIO���ŵ��жϸ��ù���
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��ʱ��
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);//���ⲿ�ж���
    
    //3. �����ⲿ�ж�EXTI
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;//�жϿ�
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;//����EXTI�ж�
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//����Ϊ�ж�ģʽ
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
    EXTI_Init(&EXTI_InitStruct);
    
    //4.���÷����ж����ȼ�NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;//�ж�������
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//�����ж�
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ������ȼ�
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//��Ӧ���ȼ������ȼ�
    NVIC_Init(&NVIC_InitStruct);
}

//�����жϺ���
void EXTI1_IRQHandler(void)
{
    //��ȡ�ж���״̬
    if(EXTI_GetITStatus(EXTI_Line1)==SET){
        key_value=1;
        //�����λ
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

int Get_Key_Value(void)
{
    if(key_value==1){
        key_value=0;
        return 1;
    }
    return 0;
}
