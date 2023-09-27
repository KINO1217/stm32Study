#ifndef __JQ8400_H__
#define __JQ8400_H__
#include "stm32f10x.h"

static char SETVOLUME[5]={0xAA,0x13,0x01,0x14,0xD2};//��������
static char PLAY[6]={0xAA,0x07,0x02,0x00,0x01,0xB4};//ѡ����Ŀ������
static char STOP[4]={0xAA,0x04,0x00,0xAE};//ֹͣ����
static char LOOP[5]={0xAA,0x18,0x01,0x02,0xC5};//����ѭ��ģʽ

typedef enum{
    FALSE=0,
    TRUE,
}bool;

//��ʼ������
void JQ8400_Init(void);
//��������
void JQ8400_SetVolume(int volume);
//����ָ������
void JQ8400_Play(int index,bool loop);
//ֹͣ����
void JQ8400_Stop(void);

#endif
