#include "jq8400.h"

/****************************��������******************************/

//������
int main(void)
{   
    JQ8400_Init();
    JQ8400_SetVolume(10);
    JQ8400_Play(1,TRUE);
    while(1){
        
    }
}


