#include "led.h"
#include "timer.h"
#include "sys.h"

int flags=0;
int led_flag=0;
int count=0;

//Ö÷º¯Êý
int main(void)
{
    NVIC_Configuration();
    led_init();
    Timer_Init(10000);
    
    while(1){
       flags=Get_Flag();
       if(flags){
           count++;
           if(count==3){
               led_flag=!led_flag;
               count=0;
           }
       }
       
       if(led_flag){
           open();
       }else{
           close();
       }
    }
}
