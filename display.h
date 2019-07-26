#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <STC15F2K60S2.h>
#include "sys_cfg.h"

void Busy();
void Write_Data(uchar k) ;
void Write_Cmd(uchar cmd) ;
void ShowQQChar(uchar addr,uchar *english,uchar count);//DDRAM地址，数据首字节指针，数据长度
void Disp(uchar y,uchar x,uchar i,uchar *z);//字符和汉字显示
void WRCGRAM1(uchar addr);//单下划线
void WRCGRAM2(uchar addr);//双下划线
void WRCGRAM3(uchar addr);//单下划线加点
void WRCGRAM4(uchar addr);//双下划线加点
void CLEARGDRAM(void);//绘图清屏
void WRGDRAM(uchar Y1,uchar clong,uchar hight,uchar *TAB1);
void Cursor(uchar x,uchar y);
void DISPIcon(uchar x,uchar y,uchar clong,uchar hight,uchar *Icon);//插入图标
void Ini_Lcd(void);  	 
void antibackgroud(uint hang);//某一行首反白显示;
void Delay_1ms(uint x);
void delayNus(uchar x);	//LCD串口时指令和数据之间的延时

#endif