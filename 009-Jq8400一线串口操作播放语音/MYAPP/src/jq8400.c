#include "jq8400.h"

void jq8400Init(void)
{
    //��ʼ��ʱ�����ö˿�
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = JQ8400_GPIO_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(JQ8400_GPIO,&GPIO_InitStruct);
    
    NVIC_Config();
    
    Delay_Init();
}

void jq8400SendOneByteData(u8 dataOrCmd)
{
    SDA=1;
    Delay_Ms(10);//�����ֽڷ���֮�����ʱ���������10ms
    
    //���������룬����2ms������Ϊ4ms
    SDA=0;
    Delay_Ms(4);
    
    for(int i=0;i<8;i++){//��������
        SDA=1;
        if(dataOrCmd&0x01){//���λΪ1,����λ1���ߵ͵�ƽʱ��3:1��ʾ����1�������������2-5������ʶ��
            Delay_Us(1200);
            SDA=0;
            Delay_Us(400);
        }else{//����λ0
            Delay_Us(400);
            SDA=0;
            Delay_Us(1200);
        }
        dataOrCmd >>= 1;
    }
}
