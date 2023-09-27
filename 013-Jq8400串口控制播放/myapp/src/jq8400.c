#include "jq8400.h"

void JQ8400_Init(void)
{
    //1.使能时钟，初始化端口
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;//发送数据端口，复用推挽输出
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//接收数据端口，浮空输入
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //2.使能时钟，配置串口参数
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    USART_InitTypeDef USART_InitStruct;
    
    USART_InitStruct.USART_BaudRate = 9600;//波特率
    USART_InitStruct.USART_Mode = USART_Mode_Tx;//模式，发模式
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据位长度，8位
    USART_InitStruct.USART_Parity = USART_Parity_No;//校验位
    USART_InitStruct.USART_StopBits = USART_StopBits_1;//一位停止位
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_Init(USART1,&USART_InitStruct);
    
    //3.使能串口
    USART_Cmd(USART1,ENABLE);
}

//发送字符串函数
static void Send_Data(u8* data,u16 data_len)
{
    for(int i=0;i<data_len;i++){
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//0表示数据还未转移到移位寄存器，1表示数据已经移动到移位寄存器可以发送数据
        USART_SendData(USART1,data[i]);
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//1表示发送完成
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
