#include "led.h"
#include "freertos.h"
#include "task.h"

TaskHandle_t myTaskHandler;

static void myTask(void *arg)
{
    while(1){
        close();
        vTaskDelay(500);
        open();
        vTaskDelay(500);
    }
}

//������
int main(void)
{
    led_init();
    
    //��������
    xTaskCreate(myTask,//������
                "taskTest",//������������ȡ
                512,//�����ջ��С
                NULL,//���񴫵ݲ���
                2,//�������ȼ�
                &myTaskHandler//������
                );
    //�������������
    vTaskStartScheduler();
    
    while(1){
        
    }
}
