#include "delay.h"
#include "sys.h"
#include "uart.h"

/****************************主代码区******************************/

char send_data[32] = {0xAA, 0x55, 0x01, 0x55, 0xAA};
char send_data1[32];

void recv_callback(u8* data,u16 data_len)
{
    memcpy(send_data1,data,data_len);
    Send_Data(USART1,(u8*)send_data1,strlen(send_data1));
    return;
}

//主函数
int main(void)
{   
    Delay_Init();
    NVIC_Config();
    UART_Init();

    callback=recv_callback;
    
    
    
    while(1){
//        memset(send_data,0,sizeof(send_data));
//        sprintf(send_data,"KINO制作串口");
//        Send_Data(USART1,(u8*)send_data,strlen(send_data));
//        printf("清风制作串口");
//        Delay_Ms(1500);
        //Send_Data(USART1,(u8*)send_data,strlen(send_data));
        Delay_Ms(1500);
    }
}


