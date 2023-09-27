#include "jq8400.h"

/****************************主代码区******************************/

//主函数
int main(void)
{   
    JQ8400_Init();
    JQ8400_SetVolume(10);
    JQ8400_Play(1,TRUE);
    while(1){
        
    }
}


