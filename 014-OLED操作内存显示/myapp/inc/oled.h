#ifndef __OLED_H__
#define __OLED_H__
#include "my_iic.h"
#include <math.h>

static u8 Oled_RAM[8][128]={0};
#define DISPLAY 1
#define UNDISPLAY 0
#define PI 3.1415926

//дָ��
static void Write_Cmd(u8 cmd);
//д����
static void Write_Data(u8 data);
//����
static void Oled_Clear(void);
//����ʾ
void Oled_On(void);
//�ر���ʾ
void Oled_Off(void);
//��ʼ��
void Oled_Init(void);
//ˢ���Դ�
void Oled_Refresh_Ram(void);
//����
void Oled_DrawLine(u8 x,u8 y,u8 x1,u8 y1,u8 dis);
//������
void Oled_DrawRect(u8 x1,u8 y1,u8 x2,u8 y2,u8 dis);
//������
void Oled_FillRect(u8 x1,u8 y1,u8 x2,u8 y2,u8 dis);
//����Ƭ
void Oled_DrawPic(u8 index);
//��Բ
void Oled_DrawCircle(u8 x,u8 y,u8 r,u8 dis);
#endif
