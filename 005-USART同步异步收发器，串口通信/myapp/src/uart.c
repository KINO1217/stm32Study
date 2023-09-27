#include "uart.h"

#if 1
#pragma import(__use_no_semihosting);//��ʹ�ð�����ģʽ

//����ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x=x;
}

//��׼����Ҫ֧�ֵĺ���
struct __FILE
{
    int handle;
};
FILE __stdout;

#endif

u8 recv_buf_temp[RECV_BUF_MAX_LEN];
void (*callback)(u8* , u16);

void UART_Init(void)
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
    
    USART_InitStruct.USART_BaudRate = 115200;//������
    USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//ģʽ���շ�ģʽ
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;//����λ���ȣ�8λ
    USART_InitStruct.USART_Parity = USART_Parity_No;//У��λ
    USART_InitStruct.USART_StopBits = USART_StopBits_1;//һλֹͣλ
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_Init(USART1,&USART_InitStruct);
    
    //3.ʹ�ܴ��������ж�
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//���ý����ж�
    USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
    
    //4.�����ж�NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
}

//�����жϺ���
void USART1_IRQHandler(void)
{
    static int recv_buf_offset=0;//��̬�������ᱣ���ϴκ�������ʱ�����ݣ���ʼ��һ�Ρ�
    uint16_t temp;
    
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){//���յ�����
        
        if(recv_buf_offset>=RECV_BUF_MAX_LEN){//�����С�жϣ���ֹ����Խ�����
            memset(recv_buf_temp,0,sizeof(recv_buf_temp));
            recv_buf_offset=0;
        }
        
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);//�������ж�״̬λ
        
        temp=USART_ReceiveData(USART1);
        recv_buf_temp[recv_buf_offset]=(u8)temp;
        recv_buf_offset++;
        
        //��������
        if(recv_buf_temp[recv_buf_offset-1]==0x0A&&recv_buf_temp[recv_buf_offset-2]==0x0D){
            //Send_Data(USART1,recv_buf_temp,recv_buf_offset-1);
            callback(recv_buf_temp,recv_buf_offset);
            memset(recv_buf_temp,0,sizeof(recv_buf_temp));
            recv_buf_offset=0;
        }
    }
}

//��дʵ��printf����
int fputc(int ch,FILE* f)
{
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//0��ʾ���ݻ�δת�Ƶ���λ�Ĵ�����1��ʾ�����Ѿ��ƶ�����λ�Ĵ������Է�������
    USART_SendData(USART1,(u8)ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//1��ʾ�������
    return ch;
}

//�����ַ�������
void Send_Data(USART_TypeDef* USARTx,u8* data,u16 data_len)
{
    for(int i=0;i<data_len;i++){
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);//0��ʾ���ݻ�δת�Ƶ���λ�Ĵ�����1��ʾ�����Ѿ��ƶ�����λ�Ĵ������Է�������
        USART_SendData(USARTx,data[i]);
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);//1��ʾ�������
    }
}
