#include "ds18b20.h"

void DS18B20_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    Delay_Init();
}

//void DQ_To_In(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA,&GPIO_InitStruct);
//}

//void DQ_To_Out(void)
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA,&GPIO_InitStruct);
//}

static u8 DS18B20_Rest(void)
{
    u8 ack=1;
    DQ_To_Out();
    DQ_OUT=0;//拉低总线
    Delay_Us(500);//拉低总线时间大于480us小于960us
    DQ_OUT=1;
    Delay_Us(20);
    Delay_Us(40);//拉高总线时间15~60us
    DQ_To_In();
    Delay_Us(40);//等待40us后接收数据，60-240us存在数据
    if(DQ_IN){
        ack=1;
    }else{
        ack=0;
    }
    Delay_Us(140);//接收时间达到240us，等待DS18B20释放总线
    Delay_Us(300);//接收存在信号至少480us
    return ack;
}

static void DS18B20_Write_Byte(u8 cmd)
{
    DQ_To_Out();
    for(u8 i=0;i<8;i++){
        DQ_OUT=0;
        Delay_Us(5);//拉低总线至少1us，15us之内拉高发送"1"
        DQ_OUT=1;
        Delay_Us(10);//达到15us
        if(cmd&0x01){//最低位为1，发送"1"
            DQ_OUT=1;
            Delay_Us(50);//15-60us内为DS18B20采样时间
        }else{
            DQ_OUT=0;
            Delay_Us(50);//15-60us内为DS18B20采样时间
        }
        DQ_OUT=1;//释放总线
        Delay_Us(3);//两个写时隙之间时间至少有1us
        cmd>>=1;
    }
}

static u8 DS18B20_Read_Byte(void)
{
    u8 data=0;
    for(int i=0;i<8;i++){
        DQ_To_Out();
        DQ_OUT=0;
        Delay_Us(2);//拉低总线
        DQ_OUT=1;//释放总线
        Delay_Us(3);//拉低总线后15us内有效
        data>>=1;
        DQ_To_In();
        if(DQ_IN){
            data|=0x80;
        }
        Delay_Us(60);//读时隙至少60us
        Delay_Us(2);
    }
    
    return data;
}

static void DS18B20_Start(void)
{
    DS18B20_Rest();//复位初始化DS18B20
    DS18B20_Write_Byte(0xCC);//跳过ROM指令
    DS18B20_Write_Byte(0x44);//温度转换指令
    Delay_Us(100);
}

float DS18B20_Get_Temp(void)
{
    u8 TL,TH;
    float temp;
    int tem;
    DS18B20_Start();
    DS18B20_Rest();//复位初始化DS18B20
    DS18B20_Write_Byte(0xCC);//跳过ROM指令
    DS18B20_Write_Byte(0xBE);//读取数据指令
    
    TL=DS18B20_Read_Byte();
    TH=DS18B20_Read_Byte();
    
    //转换温度数据
    tem=TH<<8;
    tem+=TL;
    temp=tem*6.25;
    return temp;
}
