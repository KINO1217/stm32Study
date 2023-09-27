#ifndef __OLED_H__
#define __OLED_H__
#include "my_iic.h"
#include "stdarg.h"
#include "string.h"

//дָ��
static void Write_Cmd(u8 cmd);
//д����
static void Write_Data(u8 data);
//����
void Oled_Clear(void);
//����ʾ
void Oled_On(void);
//�ر���ʾ
void Oled_Off(void);
//��ʼ��
void Oled_Init(void);
//ͨ����ʾ
static void Oled_Display(u8 x,u8 y,u8 g,u8 k,u8 *dat);
//��ʾ�����ַ�
static void Oled_Show_Char(u8 x,u8 y,u8 ch);
//����ת�ַ���
static void ITOA(int num,char *str);
//��ʾ�ַ���
void Oled_Show_String(u8 x,u8 y,char* chs,...);
//��ʾ��������
static void Oled_Show_One_Chinese(u8 x,u8 y,char chs[2]);
//��ʾ���ִ�
void Oled_Show_Chinese(u8 x,u8 y,char *chs);
#endif
