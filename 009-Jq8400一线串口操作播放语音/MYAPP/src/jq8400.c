#include "jq8400.h"

void jq8400Init(void)
{
    //初始化时钟配置端口
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
    Delay_Ms(10);//两个字节发送之间的延时，建议大于10ms
    
    //发送引导码，大于2ms，建议为4ms
    SDA=0;
    Delay_Ms(4);
    
    for(int i=0;i<8;i++){//发送数据
        SDA=1;
        if(dataOrCmd&0x01){//最低位为1,发送位1，高低电平时间3:1表示发送1，脉冲比例基数2-5都可以识别
            Delay_Us(1200);
            SDA=0;
            Delay_Us(400);
        }else{//发送位0
            Delay_Us(400);
            SDA=0;
            Delay_Us(1200);
        }
        dataOrCmd >>= 1;
    }
}
