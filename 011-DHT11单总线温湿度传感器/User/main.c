#include "dht11.h"
#include "delay.h"

u8 temp,humi;
u8 flag=0;

int main()
{
    
    DHT11_Init();
    while(1)
    {
        flag=DHT11_Get(&temp,&humi);
        Delay_Ms(1000);
    }
}
