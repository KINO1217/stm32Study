#include "my_iic.h"

void IIC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
    
    Delay_Init();
}

void IIC_Delay_Us(void)
{
    Delay_Us(5);
}

static void sda_out(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
}

static void sda_in(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
}

void IIC_Start(void)
{
    sda_out();
    SCL=1;
    SDA=1;
    IIC_Delay_Us();//拉高SCL和SDA，维持5us
    SDA=0;
    IIC_Delay_Us();//拉低SDA，维持5us
    SCL=0;
    IIC_Delay_Us();//拉低SCL，维持5us，等待数据发送或接收
}

void IIC_Stop(void)
{
    sda_out();
    SCL=1;
    SDA=0;
    IIC_Delay_Us();//SCL高电平，SDA低电平,维持5us
    SDA=1;
    IIC_Delay_Us();//SDA电平拉高，维持5us
}

void IIC_ACK(u8 ack)
{
    sda_out();
    SCL=0;
    IIC_Delay_Us();//发送数据，SCL拉低，SDA信号变换
    if(ack==ACK){
        SDA=0;//变换SDA电平
        IIC_Delay_Us();
    }else{
        SDA=1;//变换SDA电平
        IIC_Delay_Us();
    }
    SCL=1;
    IIC_Delay_Us();//拉高SCL将SDA数据发送出去
    SCL=0;
}

u8 IIC_Check_ACK(void)
{
    u8 ack;
    sda_in();
    SCL=0;
    IIC_Delay_Us();
    SCL=1;
    Delay_Us(2);//拉高后延时2us等待信号稳定
    if(SDA_STATE){//无应答
        ack=NACK;
    }else{//有应答
        ack=ACK;
    }
    Delay_Us(2);
    SCL=0;
    return ack;
}

void IIC_Send_Byte(u8 byte_data)
{
    u8 i;
    sda_out();
    for(i=0;i<8;i++){
        SCL=0;
        IIC_Delay_Us();//拉低SCL等待SDA发送一位数据
        if(byte_data&0x80)//最高位为1,高位先发
            SDA=1;
        else
            SDA=0;
        IIC_Delay_Us();
        
        SCL=1;
        IIC_Delay_Us();//拉高SCL将SDA的一位数据发送出去
        
        byte_data<<=1;  
    }
    SCL=0;
    IIC_Delay_Us();//拉低SCL等待SDA发送一位数据
}

u8 IIC_Read_Byte(void)
{
    sda_in();
    u8 temp,i;
    for(i=0;i<8;i++){
        SCL=0;
        IIC_Delay_Us();//拉低SCL等待接收数据
        SCL=1;
        Delay_Us(2);
        temp<<=1;
        if(SDA_STATE)
            temp|=0x01;
        Delay_Us(2);
    }
    SCL=0;
    IIC_Delay_Us();//拉低SCL
    return temp;
}
