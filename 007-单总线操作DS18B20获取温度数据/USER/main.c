#include "oled.h"
#include "ds18b20.h"

/****************************主代码区******************************/

//主函数
int main(void)
{  
   Oled_Init();
   DS18B20_Init();
   
   float temp=0.0;
   int zheng=0;
   int xiao=0;
   
   while(1){
       temp=DS18B20_Get_Temp();
       zheng=(int)temp/100;
       xiao=(int)temp%100;
       Oled_Show_String(0,0,"temp:%d.%d     ",zheng,xiao);
   }
}
