#include "led.h"
#include "delay.h"

/****************************��������******************************/

//������
int main(void)
{   
    Led_Init();
    Delay_Init();
    
    while(1){
        Led_On();
        Delay_Ms(500);
        Led_Off();
        Delay_Ms(500);
    }
}
