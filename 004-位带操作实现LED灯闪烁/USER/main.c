#include "led.h"
/****************************��������******************************/

//��ʱ����
void delay(int time)
{
    for(int i=0;i<time;i++)
        for(int j=0;j<10000;j++);
}

//������
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
