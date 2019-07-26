#ifndef _SYS_CFG_H_
#define _SYS_CFG_H_

#include <STC15F2K60S2.h>

#define uchar unsigned char 
#define uint  unsigned int 	  

//#define DATA  P2 //数据输出端0~7 
#define BF 0x80 //用于检测LCD忙状态的标志
//const uchar delay=250; //延时时间常数  

#define KeyIO 		P1//按键阵列串口为P1
#define SW_CTRL 	P3//切换程序控制
#define OPT_CHECK 	P0	//光开关检测
#define LCDIO 		P2 //LCD数据线为P2

/*
sbit RS=P4^0; //LCD12864 RS端 
sbit RW=P4^1; //LCD12864 RW端 
sbit E =P4^2; //LCD12864 E 端 
sbit PSB =P4^3;  
*/ 
sbit 	DI=P4^0; 		//LCD12864 DI端口：1：数据;0：命令
sbit 	CS=P4^0;		//P1^0;//并口时为RS，串口时为CS
sbit 	RW=P4^1;   		//LCD12864 RW端 
sbit 	SID=P4^1;		//P1^1; //并口时为RW，串口为SID
sbit 	E=P4^2;	    	//LCD12864 E 端 
sbit 	SCLK=P4^2;		//LCDIO^5; //并口时为E，串口为时钟SCLK
sbit 	PSB=P4^3;		//并口时为E，串口为时钟SCLK
sbit 	REST=P4^4;		//LCD12864 RESET端
sbit 	bee_Speak =P4^5;  //蜂鸣器控制引脚

/////////////////////////////////////////////////
//注意: STC15W4K32S4系列的芯片,上电后所有与PWM相关的IO口均为
//      高阻态,需将这些口设置为准双向口或强推挽模式方可正常使用
//相关IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
/////////////////////////////////////////////////


#endif