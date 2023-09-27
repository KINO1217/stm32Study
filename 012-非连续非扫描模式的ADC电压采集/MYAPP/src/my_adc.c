#include "my_adc.h"

void MADC_Init(void)
{
    //1.ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA,ENABLE);
    
    //2.���ó�ʼ��GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//ģ������
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //3.����ADC��Ƶ����
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCʱ��72M/6=12M�����ܳ���14M
    
    //4.��ʼ��ADC����
    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//���ݶ��뷽ʽ
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//����ת��
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//����ģʽ
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;//ɨ��ģʽ
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ⲿ������Ӳ�����������
    ADC_InitStruct.ADC_NbrOfChannel = 1;//ɨ��ģʽ�µ�ת��ͨ����
    ADC_Init(ADC1,&ADC_InitStruct);
    
    //5.����ADC������ͨ��
    ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);
    
    //6.ʹ��ADC
    ADC_Cmd(ADC1,ENABLE);
    
    //7.ADCУ׼
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

float Get_ValueV(void)
{
    uint16_t temp=0;
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//ʹ���������ת��
    while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�ת������
    temp=ADC_GetConversionValue(ADC1);//��ȡ��ѹֵ
    return (float)3.3*temp/4095;
}
