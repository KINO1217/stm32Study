#include "delay.h"

int fac_us=0;
int fac_ms=0;

void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//����ʱ��Դ
    fac_us=SystemCoreClock/8/1000000;//����1us�ļ�������,9������
    fac_ms=fac_us*1000;//����1ms�ļ�������9000������
}

void Delay_Us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = fac_us*nus;     //�Զ���װ��ֵ�Ĵ�������������0ʱ��������װ�ص�ֵ
    SysTick->VAL = 0x00;            //��ǰֵ�Ĵ��������ص�ǰ��������ֵ��д����ʹ֮����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //ʹ��,��ʼ����
    do{
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));   //ʹ��λû�����㣬����COUNTFLAG=0��û�����꣩
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;          //ʧ�ܣ�ֹͣ����
    SysTick->VAL = 0x00;
}

void Delay_Ms(u16 nms)
{
    if(nms>1864){//������ms��24λ
        nms=1864;
    }
    
    u32 temp;
    SysTick->LOAD = (u32)fac_ms*nms;     //�Զ���װ��ֵ�Ĵ�������������0ʱ��������װ�ص�ֵ
    SysTick->VAL = 0x00;            //��ǰֵ�Ĵ��������ص�ǰ��������ֵ��д����ʹ֮����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;          //ʹ��,��ʼ����
    do{
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));   //ʹ��λû�����㣬����COUNTFLAG=0��û�����꣩
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;          //ʧ�ܣ�ֹͣ����
    SysTick->VAL = 0x00;
}
