#include "led.h"
#include "sys.h"
#include "key.h"


/****************************��������******************************/

//��ʱ����
void delay(int time)
{
    for(int i=0;i<time;i++)
        for(int j=0;j<10000;j++);
}

int led_flag=0;

//������
int main(void)
{
    NVIC_Config();
    
    Led_Init();
    
    Key_Init();
    
    int kv=0;
    
    while(1){
        kv=Get_Key_Value();
        if(kv==1){
            led_flag=!led_flag;
        }
        
        if(led_flag){
            Led_On();
        }else{
            Led_Off();
        }
        delay(1000);
    }
}
