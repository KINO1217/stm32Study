#include "uart.h"

#if 1
#pragma import(__use_no_semihosting);//不使用半主机模式

//避免使用半主机模式
void _sys_exit(int x)
{
    x=x;
}

//标准库需要支持的函数
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
    
    USART_InitStruct.USART_BaudRate = 115200;//波特率
    USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//模式，收发模式
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据位长度，8位
    USART_InitStruct.USART_Parity = USART_Parity_No;//校验位
    USART_InitStruct.USART_StopBits = USART_StopBits_1;//一位停止位
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_Init(USART1,&USART_InitStruct);
    
    //3.使能串口设置中断
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//设置接收中断
    USART_Cmd(USART1,ENABLE);//使能串口
    
    //4.设置中断NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
}

//串口中断函数
void USART1_IRQHandler(void)
{
    static int recv_buf_offset=0;//静态变量，会保留上次函数结束时的数据，初始化一次。
    uint16_t temp;
    
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){//接收到数据
        
        if(recv_buf_offset>=RECV_BUF_MAX_LEN){//数组大小判断，防止数组越界错误
            memset(recv_buf_temp,0,sizeof(recv_buf_temp));
            recv_buf_offset=0;
        }
        
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);//软件清除中断状态位
        
        temp=USART_ReceiveData(USART1);
        recv_buf_temp[recv_buf_offset]=(u8)temp;
        recv_buf_offset++;
        
        //接收数据
        if(recv_buf_temp[recv_buf_offset-1]==0x0A&&recv_buf_temp[recv_buf_offset-2]==0x0D){
            //Send_Data(USART1,recv_buf_temp,recv_buf_offset-1);
            callback(recv_buf_temp,recv_buf_offset);
            memset(recv_buf_temp,0,sizeof(recv_buf_temp));
            recv_buf_offset=0;
        }
    }
}

//重写实现printf函数
int fputc(int ch,FILE* f)
{
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//0表示数据还未转移到移位寄存器，1表示数据已经移动到移位寄存器可以发送数据
    USART_SendData(USART1,(u8)ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);//1表示发送完成
    return ch;
}

//发送字符串函数
void Send_Data(USART_TypeDef* USARTx,u8* data,u16 data_len)
{
    for(int i=0;i<data_len;i++){
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);//0表示数据还未转移到移位寄存器，1表示数据已经移动到移位寄存器可以发送数据
        USART_SendData(USARTx,data[i]);
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);//1表示发送完成
    }
}
