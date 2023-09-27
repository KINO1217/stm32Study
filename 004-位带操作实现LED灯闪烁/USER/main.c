#include "led.h"
/****************************主代码区******************************/

//延时函数
void delay(int time)
{
    for(int i=0;i<time;i++)
        for(int j=0;j<10000;j++);
}

//主函数
int main(void)
{   
    Led_Init();
    while(1){
        LED=0;
        delay(1000);
        LED=1;
        delay(1000);
    }
}
