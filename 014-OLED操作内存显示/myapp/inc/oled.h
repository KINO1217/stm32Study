#ifndef __OLED_H__
#define __OLED_H__
#include "my_iic.h"
#include <math.h>

static u8 Oled_RAM[8][128]={0};
#define DISPLAY 1
#define UNDISPLAY 0

//写指令
static void Write_Cmd(u8 cmd);
//写数据
static void Write_Data(u8 data);
//清屏
static void Oled_Clear(void);
//打开显示
void Oled_On(void);
//关闭显示
void Oled_Off(void);
//初始化
void Oled_Init(void);
//刷新显存
void Oled_Refresh_Ram(void);
//画线
void Oled_DrawLine(u8 x,u8 y,u8 x1,u8 y1,u8 dis);
//画矩形
void Oled_DrawRect(u8 x1,u8 y1,u8 x2,u8 y2,u8 dis);
//填充矩形
void Oled_FillRect(u8 x1,u8 y1,u8 x2,u8 y2,u8 dis);
void Oled_DrawPic(u8 index);
#endif
