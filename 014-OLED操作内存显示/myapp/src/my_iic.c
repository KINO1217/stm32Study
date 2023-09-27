#include "my_iic.h"

void IIC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;//��©���
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
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;//��©���
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
}

static void sda_in(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
}

void IIC_Start(void)
{
    sda_out();
    SCL=1;
    SDA=1;
    IIC_Delay_Us();//����SCL��SDA��ά��5us
    SDA=0;
    IIC_Delay_Us();//����SDA��ά��5us
    SCL=0;
    IIC_Delay_Us();//����SCL��ά��5us���ȴ����ݷ��ͻ����
}

void IIC_Stop(void)
{
    sda_out();
    SCL=1;
    SDA=0;
    IIC_Delay_Us();//SCL�ߵ�ƽ��SDA�͵�ƽ,ά��5us
    SDA=1;
    IIC_Delay_Us();//SDA��ƽ���ߣ�ά��5us
}

void IIC_ACK(u8 ack)
{
    sda_out();
    SCL=0;
    IIC_Delay_Us();//�������ݣ�SCL���ͣ�SDA�źű任
    if(ack==ACK){
        SDA=0;//�任SDA��ƽ
        IIC_Delay_Us();
    }else{
        SDA=1;//�任SDA��ƽ
        IIC_Delay_Us();
    }
    SCL=1;
    IIC_Delay_Us();//����SCL��SDA���ݷ��ͳ�ȥ
    SCL=0;
}

u8 IIC_Check_ACK(void)
{
    u8 ack;
    sda_in();
    SCL=0;
    IIC_Delay_Us();
    SCL=1;
    Delay_Us(2);//���ߺ���ʱ2us�ȴ��ź��ȶ�
    if(SDA_STATE){//��Ӧ��
        ack=NACK;
    }else{//��Ӧ��
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
        IIC_Delay_Us();//����SCL�ȴ�SDA����һλ����
        if(byte_data&0x80)//���λΪ1,��λ�ȷ�
            SDA=1;
        else
            SDA=0;
        IIC_Delay_Us();
        
        SCL=1;
        IIC_Delay_Us();//����SCL��SDA��һλ���ݷ��ͳ�ȥ
        
        byte_data<<=1;  
    }
    SCL=0;
    IIC_Delay_Us();//����SCL�ȴ�SDA����һλ����
}

u8 IIC_Read_Byte(void)
{
    sda_in();
    u8 temp,i;
    for(i=0;i<8;i++){
        SCL=0;
        IIC_Delay_Us();//����SCL�ȴ���������
        SCL=1;
        Delay_Us(2);
        temp<<=1;
        if(SDA_STATE)
            temp|=0x01;
        Delay_Us(2);
    }
    SCL=0;
    IIC_Delay_Us();//����SCL
    return temp;
}
