#ifndef _SYS_FUN_H_
#define _SYS_FUN_H_

#include <STC15F2K60S2.h>
#include "sys_cfg.h"
 

void Time0_Init();//定时器初始化
void Play_Song(unsigned char i);//播放音乐
uchar ctrl_port_check(void);//检测控制端口的状态
uchar scankey(void);//矩阵键盘翻转扫描
void Delay_xMs(unsigned int x);//延迟毫秒数

#endif