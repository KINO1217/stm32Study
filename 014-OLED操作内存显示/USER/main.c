#include "delay.h"
#include "oled.h"

/****************************��������******************************/

//������
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
