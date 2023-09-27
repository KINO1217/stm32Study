#include "delay.h"
#include "oled.h"

/****************************主代码区******************************/

//主函数
int main(void)
{
   Oled_Init();
   while(1){
       Oled_DrawPic(1);
       Delay_Ms(1000);
       Delay_Ms(1000);
       Delay_Ms(1000);
       Delay_Ms(1000);
       Delay_Ms(1000);
       Oled_DrawPic(2);
       Delay_Ms(1000);
       Delay_Ms(1000);
       Delay_Ms(1000);
       Delay_Ms(1000);
       Delay_Ms(1000);
//       Oled_DrawLine(0,0,100,100,DISPLAY);
//       Oled_Refresh_Ram();
   }
}
