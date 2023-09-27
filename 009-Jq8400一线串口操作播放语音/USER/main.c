#include "jq8400.h"

//主函数
int main(void)
{
    jq8400Init();
    jq8400SendOneByteData(0x0A);//先发送数字，再发送指令,清除数字指令
    jq8400SendOneByteData(0x01);//发送数字1
    //jq8400SendOneByteData(0x00);//发送数字0，结合组成数字10
    jq8400SendOneByteData(0x0B);//确定选曲指令
    
    jq8400SendOneByteData(0x11);//播放指令，单指令
}
