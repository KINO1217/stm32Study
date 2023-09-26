#include "led.h"
#include "delay.h"

/****************************主代码区******************************/

//主函数
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
