#ifndef _SYS_FUN_H_
#define _SYS_FUN_H_

#include <STC15F2K60S2.h>
#include "sys_cfg.h"
 

void Time0_Init();//��ʱ����ʼ��
void Play_Song(unsigned char i);//��������
uchar ctrl_port_check(void);//�����ƶ˿ڵ�״̬
uchar scankey(void);//������̷�תɨ��
void Delay_xMs(unsigned int x);//�ӳٺ�����

#endif