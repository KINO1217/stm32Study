#include "led.h"

void Led_Init(void)
{   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��ʱ��

    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP; //�����������������ߵ�ƽҲ��������͵�ƽ
    GPIO_InitStruct.GPIO_Pin=LED_GPIO_PIN;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    
    GPIO_Init(LED_GPIO,&GPIO_InitStruct);
}

void Led_On(void)
{
    GPIO_SetBits(LED_GPIO,LED_GPIO_PIN);
}

void Led_Off(void)
{
    GPIO_ResetBits(LED_GPIO,LED_GPIO_PIN);
}
