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

//主函数
int main(void)
{
    led_init();
    
    //创建任务
    xTaskCreate(myTask,//任务函数
                "taskTest",//任务名，随意取
                512,//任务堆栈大小
                NULL,//任务传递参数
                2,//任务优先级
                &myTaskHandler//任务句柄
                );
    //开启任务调度器
    vTaskStartScheduler();
    
    while(1){
        
    }
}
