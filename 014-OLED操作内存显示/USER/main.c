#include "delay.h"
#include "oled.h"

/****************************主代码区******************************/

//主函数
int main(void)
{
   Oled_Init();
   while(1){
       for(int i=0;i<30;i++){    
           Oled_DrawCircle(30,60,i,DISPLAY);
           Delay_Ms(500);
       }
   }
}
