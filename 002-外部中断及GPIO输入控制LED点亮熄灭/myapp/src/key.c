#include "key.h"

int key_value=0;

void Key_Init(void)
{
    //1. 使能引脚，配置引脚。
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = KEY_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_GPIO,&GPIO_InitStruct);
    
    //2. 设置AFIO引脚的中断复用功能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能时钟
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);//绑定外部中断线
    
    //3. 设置外部中断EXTI
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;//中断口
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;//开启EXTI中断
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//设置为中断模式
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
    EXTI_Init(&EXTI_InitStruct);
    
    //4.配置分配中断优先级NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;//中断请求线
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//允许中断
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级的优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//响应优先级的优先级
    NVIC_Init(&NVIC_InitStruct);
}

//设置中断函数
void EXTI1_IRQHandler(void)
{
    //获取中断线状态
    if(EXTI_GetITStatus(EXTI_Line1)==SET){
        key_value=1;
        //软件复位
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
