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
    DQ_OUT=0;//��������
    Delay_Us(500);//��������ʱ�����480usС��960us
    DQ_OUT=1;
    Delay_Us(20);
    Delay_Us(40);//��������ʱ��15~60us
    DQ_To_In();
    Delay_Us(40);//�ȴ�40us��������ݣ�60-240us��������
    if(DQ_IN){
        ack=1;
    }else{
        ack=0;
    }
    Delay_Us(140);//����ʱ��ﵽ240us���ȴ�DS18B20�ͷ�����
    Delay_Us(300);//���մ����ź�����480us
    return ack;
}

static void DS18B20_Write_Byte(u8 cmd)
{
    DQ_To_Out();
    for(u8 i=0;i<8;i++){
        DQ_OUT=0;
        Delay_Us(5);//������������1us��15us֮�����߷���"1"
        DQ_OUT=1;
        Delay_Us(10);//�ﵽ15us
        if(cmd&0x01){//���λΪ1������"1"
            DQ_OUT=1;
            Delay_Us(50);//15-60us��ΪDS18B20����ʱ��
        }else{
            DQ_OUT=0;
            Delay_Us(50);//15-60us��ΪDS18B20����ʱ��
        }
        DQ_OUT=1;//�ͷ�����
        Delay_Us(3);//����дʱ϶֮��ʱ��������1us
        cmd>>=1;
    }
}

static u8 DS18B20_Read_Byte(void)
{
    u8 data=0;
    for(int i=0;i<8;i++){
        DQ_To_Out();
        DQ_OUT=0;
        Delay_Us(2);//��������
        DQ_OUT=1;//�ͷ�����
        Delay_Us(3);//�������ߺ�15us����Ч
        data>>=1;
        DQ_To_In();
        if(DQ_IN){
            data|=0x80;
        }
        Delay_Us(60);//��ʱ϶����60us
        Delay_Us(2);
    }
    
    return data;
}

static void DS18B20_Start(void)
{
    DS18B20_Rest();//��λ��ʼ��DS18B20
    DS18B20_Write_Byte(0xCC);//����ROMָ��
    DS18B20_Write_Byte(0x44);//�¶�ת��ָ��
    Delay_Us(100);
}

float DS18B20_Get_Temp(void)
{
    u8 TL,TH;
    float temp;
    int tem;
    DS18B20_Start();
    DS18B20_Rest();//��λ��ʼ��DS18B20
    DS18B20_Write_Byte(0xCC);//����ROMָ��
    DS18B20_Write_Byte(0xBE);//��ȡ����ָ��
    
    TL=DS18B20_Read_Byte();
    TH=DS18B20_Read_Byte();
    
    //ת���¶�����
    tem=TH<<8;
    tem+=TL;
    temp=tem*6.25;
    return temp;
}
