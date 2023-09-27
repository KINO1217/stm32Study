#include "jq8400.h"

void JQ8400_Init(void)
{
    //1.ʹ��ʱ�ӣ���ʼ���˿�
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//�������ݶ˿ڣ������������
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//�������ݶ˿ڣ���������
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //2.ʹ��ʱ�ӣ����ô��ڲ���
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    USART_InitTypeDef USART_InitStruct;
    
    USART_InitStruct.USART_BaudRate = 9600;//������
    USART_InitStruct.USART_Mode = USART_Mode_Tx;//ģʽ����ģʽ
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;//����λ���ȣ�8λ
    USART_InitStruct.USART_Parity = USART_Parity_No;//У��λ
    USART_InitStruct.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_Init(USART1,&USART_InitStruct);
    
    //3.ʹ�ܴ���
    USART_Cmd(USART1,ENABLE);
}

//�����ַ�������
static void Send_Data(u8* data,u16 data_len)
{
    for(int i=0;i<data_len;i++){
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//0��ʾ���ݻ�δת�Ƶ���λ�Ĵ�����1��ʾ�����Ѿ��ƶ�����λ�Ĵ������Է�������
        USART_SendData(USART1,data[i]);
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//1��ʾ�������
    }
}

void JQ8400_SetVolume(int volume)
{
    SETVOLUME[3]=volume;
    SETVOLUME[4]=SETVOLUME[0]+SETVOLUME[1]+SETVOLUME[2]+SETVOLUME[3];
    Send_Data((u8*)SETVOLUME,5);
}

void JQ8400_Play(int index,bool loop)
{
    if(loop == TRUE){
        LOOP[3]=0x01;
        LOOP[4]=0xC4;
        Send_Data((u8*)LOOP,5);
    }else{
        LOOP[3]=0x02;
        LOOP[4]=0xC5;
        Send_Data((u8*)LOOP,5);
    }
    
    PLAY[3]=(index & 0xFF00) >> 8;
    PLAY[4]=(index & 0x00FF);
    PLAY[5]=PLAY[0]+PLAY[1]+PLAY[2]+PLAY[3]+PLAY[4];
    Send_Data((u8*)PLAY,6);
}

void JQ8400_Stop(void)
{
    Send_Data((u8*)STOP,4);
}
