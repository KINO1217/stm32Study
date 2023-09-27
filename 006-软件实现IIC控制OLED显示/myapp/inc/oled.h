#ifndef __OLED_H__
#define __OLED_H__
#include "my_iic.h"
#include "stdarg.h"
#include "string.h"

//写指令
static void Write_Cmd(u8 cmd);
//写数据
static void Write_Data(u8 data);
//清屏
void Oled_Clear(void);
//打开显示
void Oled_On(void);
//关闭显示
void Oled_Off(void);
//初始化
void Oled_Init(void);
//通用显示
static void Oled_Display(u8 x,u8 y,u8 g,u8 k,u8 *dat);
//显示单个字符
static void Oled_Show_Char(u8 x,u8 y,u8 ch);
//数字转字符串
static void ITOA(int num,char *str);
//显示字符串
void Oled_Show_String(u8 x,u8 y,char* chs,...);
//显示单个汉字
static void Oled_Show_One_Chinese(u8 x,u8 y,char chs[2]);
//显示汉字串
void Oled_Show_Chinese(u8 x,u8 y,char *chs);
#endif
