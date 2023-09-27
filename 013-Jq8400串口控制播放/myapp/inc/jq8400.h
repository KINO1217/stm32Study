#ifndef __JQ8400_H__
#define __JQ8400_H__
#include "stm32f10x.h"

static char SETVOLUME[5]={0xAA,0x13,0x01,0x14,0xD2};//设置音量
static char PLAY[6]={0xAA,0x07,0x02,0x00,0x01,0xB4};//选择曲目并播放
static char STOP[4]={0xAA,0x04,0x00,0xAE};//停止播放
static char LOOP[5]={0xAA,0x18,0x01,0x02,0xC5};//设置循环模式

typedef enum{
    FALSE=0,
    TRUE,
}bool;

//初始化串口
void JQ8400_Init(void);
//设置音量
void JQ8400_SetVolume(int volume);
//播放指定音乐
void JQ8400_Play(int index,bool loop);
//停止播放
void JQ8400_Stop(void);

#endif
