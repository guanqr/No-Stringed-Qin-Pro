#ifndef _SYS_CFG_H_
#define _SYS_CFG_H_

#include <STC15F2K60S2.h>

#define uchar unsigned char 
#define uint  unsigned int 	  

//#define DATA  P2 //���������0~7 
#define BF 0x80 //���ڼ��LCDæ״̬�ı�־
//const uchar delay=250; //��ʱʱ�䳣��  

#define KeyIO 		P1//�������д���ΪP1
#define SW_CTRL 	P3//�л��������
#define OPT_CHECK 	P0	//�⿪�ؼ��
#define LCDIO 		P2 //LCD������ΪP2

/*
sbit RS=P4^0; //LCD12864 RS�� 
sbit RW=P4^1; //LCD12864 RW�� 
sbit E =P4^2; //LCD12864 E �� 
sbit PSB =P4^3;  
*/ 
sbit 	DI=P4^0; 		//LCD12864 DI�˿ڣ�1������;0������
sbit 	CS=P4^0;		//P1^0;//����ʱΪRS������ʱΪCS
sbit 	RW=P4^1;   		//LCD12864 RW�� 
sbit 	SID=P4^1;		//P1^1; //����ʱΪRW������ΪSID
sbit 	E=P4^2;	    	//LCD12864 E �� 
sbit 	SCLK=P4^2;		//LCDIO^5; //����ʱΪE������Ϊʱ��SCLK
sbit 	PSB=P4^3;		//����ʱΪE������Ϊʱ��SCLK
sbit 	REST=P4^4;		//LCD12864 RESET��
sbit 	bee_Speak =P4^5;  //��������������

/////////////////////////////////////////////////
//ע��: STC15W4K32S4ϵ�е�оƬ,�ϵ��������PWM��ص�IO�ھ�Ϊ
//      ����̬,�轫��Щ������Ϊ׼˫��ڻ�ǿ����ģʽ��������ʹ��
//���IO: P0.6/P0.7/P1.6/P1.7/P2.1/P2.2
//        P2.3/P2.7/P3.7/P4.2/P4.4/P4.5
/////////////////////////////////////////////////


#endif