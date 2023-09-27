#include "delay.h"
#include "oled.h"

/****************************主代码区******************************/

//主函数
int main(void)
{  
   int num=-12;
   Oled_Init();
   Oled_Show_String(0,6,"KINO");
   Oled_Show_String(2,3,"4119010231");
   Oled_Show_Chinese(3,3,"清风");
   while(1){
      Oled_Show_String(1,0,"NUM=%d %   @      ",num);
      Delay_Ms(1000);
      num++;
   }
}
