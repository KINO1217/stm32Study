#include "led.h"

//延时函数
void delay(int time)
{
    for(int i=0;i<time;i++)
        for(int j=0;j<10000;j++);
}

//主函数
int main(void)
{
    led_init();
    
    while(1){
        close();
        delay(500);
        open();
        delay(500);
    }
}
