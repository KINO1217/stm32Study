#include "my_adc.h"

void MADC_Init(void)
{
    //1.使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA,ENABLE);
    
    //2.配置初始化GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    //3.设置ADC分频因子
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC时钟72M/6=12M，不能超过14M
    
    //4.初始化ADC参数
    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;//数据对齐方式
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;//连续转换
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;//扫描模式
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发，硬件或软件触发
    ADC_InitStruct.ADC_NbrOfChannel = 1;//扫描模式下的转换通道数
    ADC_Init(ADC1,&ADC_InitStruct);
    
    //5.设置ADC规则组通道
    ADC_RegularChannelConfig(ADC1,ADC_Channel_5,1,ADC_SampleTime_55Cycles5);
    
    //6.使能ADC
    ADC_Cmd(ADC1,ENABLE);
    
    //7.ADC校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

float Get_ValueV(void)
{
    uint16_t temp=0;
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//使能软件触发转换
    while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
    temp=ADC_GetConversionValue(ADC1);//获取电压值
    return (float)3.3*temp/4095;
}
