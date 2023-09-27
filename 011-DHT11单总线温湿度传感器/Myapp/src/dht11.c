#include "dht11.h"

static u8 Data[5];

//Program Size: Code=2028 RO-data=268 RW-data=40 ZI-data=1632  

void DHT11_Init(void)
{
    //1.ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //2.��ʼ��GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_SetBits(GPIOA,GPIO_Pin_11);
    
    Delay_Init();
    Delay_Ms(1000);
}

static void LineOut(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
}

static void LineIn(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
}

static void Start(void)
{
    LineOut();
    //��������
    DHT11_OUT=0;//��������18ms
    Delay_Ms(20);
    DHT11_OUT=1;//�ͷ����ߵȴ�20-40us�ȴ�DHT11��Ӧ
    Delay_Us(40);
    LineIn();
}

static u8 GetByte(void)
{
    u8 temp=0;
    for(int i=0;i<8;i++){
        while(!DHT11_IN);//�ȴ�50us������Ӧ����
        temp <<= 1;
        Delay_Us(40);//��ʱ40us���ݸߵ�ƽʱ���ж�0��1
        if(DHT11_IN){
            temp |= 0x01;
        }
        while(DHT11_IN);//�ȴ��ߵ�ƽ����
    }
    return temp;
}

u8 DHT11_Get(u8* temp,u8* humi)
{
    u8 temps=0;
    Start();
    if(!DHT11_IN){
        while(!DHT11_IN);//�ȴ�80us������Ӧ����
        while(DHT11_IN);//�ȴ�80us������Ӧ����
        
        //���ݽ���
        for(int i=0;i<5;i++){
            Data[i]=GetByte();
        }
        
        *temp=Data[2];
        *humi=Data[0];
        
        //�¶�ʪ����Ӽ���У���
        for(int i=0;i<4;i++){
            temps+=Data[i];
        }
    }
    if(temps == Data[4])
        return 0;
    else
        return 1;
}
