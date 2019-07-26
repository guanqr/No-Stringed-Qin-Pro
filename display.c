#include "sys_cfg.h"
#include "display.h"


/***********LCD12864Һ����æ�ӳ���(��״̬)************/ 
void Busy()   
{   
	uchar busy;
	do  
	{      
		E = 0;      //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�      
		DI = 0;      //1Ϊָ��,0Ϊ����      
		RW = 1;    //1Ϊ��,0Ϊд       
		Delay_1ms(20);  //��ʱ20����120ʱ��      
		E = 1;     //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�  
		P2M0=0x00;
		P2M1=0x00;	//��P2��Ϊ׼˫�򣨴�ͳ51IO�ڣ�  
		busy=P2;    //��ȡP2״̬      
		Delay_1ms(20);  //��ʱ20����120ʱ��      
		E = 0;    //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�     
	}while(busy&0x80);  //�ж�BUSYλ�Ƿ���:1Ϊ�ڲ��ڹ���,0Ϊ����״̬ 
}  
/*********************************************   LCD12864Һ������д���ӳ���  *********************************************/ 
void Write_Data(uchar k) 
{   
	Busy();   //��æ
	E =1;   //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�    
	DI=1;   //1Ϊָ��,0Ϊ����    
	RW=0;   //1Ϊ��,0Ϊд   
	P2M0=0xFF;
	P2M1=0x00;	//��P2��Ϊ����  	
	P2=k;   //��������K��DATA    
	Delay_1ms(20); //��ʱ20����120ʱ��    
	E =0;    //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�    
	Delay_1ms(20);   //��ʱ20����120ʱ�� 
}  

/*********************************************   LCD12864Һ������д���ӳ���  *********************************************/ 
void Write_Cmd(uchar cmd) 
{      
	Busy();    //��æ
	E=1;   //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�     
	DI=0;    //1Ϊָ��,0Ϊ����     
	RW=0;   //1Ϊ��,0Ϊд   
	P2M0=0xFF;
	P2M1=0x00;	//��P2��Ϊ���� 
	P2=cmd;    //��������cmd��DATA     
	Delay_1ms(20); //��ʱ20����120ʱ�� 
	E=0;   //0Ϊ�ر�ʹ�ܶ�,1Ϊ��ʹ�ܶ�     
	Delay_1ms(20); //��ʱ20����120ʱ�� 
}  


//��ʾ�����ַ���(��ʾ�������16*8����)
void ShowQQChar(uchar addr,uchar *english,uchar count)//DDRAM��ַ���������ֽ�ָ�룬���ݳ���
{
	uchar i;
	Write_Cmd(addr); //�趨DDRAM��ַ
	for(i=0;i<count;)
	{
		Write_Data(english[i*2]);
		Write_Data(english[i*2+1]);
		i++;
	}
}

//�ַ��ͺ�����ʾ
/*********************************************   LCD12864Һ��������ʾ�ӳ���  *********************************************/ 
void Disp(uchar y,uchar x,uchar i,uchar *z)   
{     
	uchar Address;    
	//Y�жϵڼ���,X�жϵڼ���,0x80ΪҺ���г�ʼ��ַ    
	if(y==1)  Address=0x80+x;
	if(y==2){Address=0x90+x;}        
	if(y==3){Address=0x88+x;}    
	if(y==4){Address=0x98+x;}  
	Write_Cmd(Address);//д���ַ���LCD12864  
	while(i)       //д����ʾ���ݵĴ�С  
	{    
		Write_Data(*(z++));    //д����ʾ���ݵ�LCD12864    
		i--;         
	}   
} 
	
//�Զ����ַ�1��16X16��д��CGRAM //
void WRCGRAM1(uchar addr)//���»���
{
	uchar i;
	for(i=0;i<2;)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	for(i=2;i<16;i++)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

//�Զ����ַ�2��16X16��д��CGRAM //
void WRCGRAM2(uchar addr)//˫�»���
{
	uchar i;
	for(i=0;i<4;)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	for(i=4;i<16;i++)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

//�Զ����ַ�3��16X16��д��CGRAM //
void WRCGRAM3(uchar addr)//���»��߼ӵ�
{
	uchar i;
	for(i=0;i<2;)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	for(i=2;i<6;)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	Write_Cmd(addr+6);Write_Data(0x18);Write_Data(0x00);
	Write_Cmd(addr+7);Write_Data(0x3c);Write_Data(0x00);
	Write_Cmd(addr+8);Write_Data(0x3c);Write_Data(0x00);
	Write_Cmd(addr+9);Write_Data(0x18);Write_Data(0x00);
	for(i=10;i<16;i++)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

//�Զ����ַ�4��16X16��д��CGRAM //
void WRCGRAM4(uchar addr)//˫�»��߼ӵ�
{
	uchar i;
	for(i=0;i<4;)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	Write_Cmd(addr+4);Write_Data(0x00);Write_Data(0x00);
    Write_Cmd(addr+5);Write_Data(0x00);Write_Data(0x00);
	Write_Cmd(addr+6);Write_Data(0x18);Write_Data(0x00);
	Write_Cmd(addr+7);Write_Data(0x3c);Write_Data(0x00);
	Write_Cmd(addr+8);Write_Data(0x3c);Write_Data(0x00);
	Write_Cmd(addr+9);Write_Data(0x18);Write_Data(0x00);
	for(i=10;i<16;i++)
	{
		Write_Cmd(addr+i); //�趨CGRAM��ַ
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

void CLEARGDRAM(void)//��ͼ����	 
{
	uchar j;
	uchar i;
	Write_Cmd(0x34);  //�л�����ָ�
	Write_Cmd(0x36);  //��ͼ��ʾ��
	for(j=0;j<32;j++)
	{
		Write_Cmd(0x80+j);//y���� ��32��
		Write_Cmd(0x80);//X����
		for(i=0;i<32;i++)//
		{
			Write_Data(0x00);//��ո�32*8����256�ո�
		}
	}
}

//д��GDRAM ��ͼ,Y��Y��ͼ����,2���ֽ�һ��,CLONG��ͼ�γ���,���ֽ�
//Ϊ��λ;HIGHT��ͼ�θ߶�,TAB��ͼ�����ݱ�.12864M��ͼ����ʾ���൱��256*32.
//������128*32����������ɣ�ͬһ�е�������ͷ��ַ����������δ��ַ��
//��ͼ�ڴ�������ʱ,����ڲ����µ�����Ҫ��һЩ
void WRGDRAM(uchar Y1,uchar clong,uchar hight,uchar *TAB1)
{
	uint k;
	uchar j;
	uchar i;
	Write_Cmd(0x34);
	Write_Cmd(0x36);
	for(j=0;j<hight;j++)//32
	{ //���ϰ���
		Write_Cmd(Y1+j); //Y������,���ڼ���
		Write_Cmd(0x80);//X����0����������0���ֽڿ�ʼд��		
		for(i=0;i<clong;i++)//
		{
			Write_Data(TAB1[clong*j+i]);
		}
	//���°���
		for(k=0;k<clong;k++)//
		{
			Write_Data(TAB1[clong*(j+hight)+k]);
		}
	}
	Write_Cmd(0x30);
}

void Cursor(uchar x,uchar y)
{
	Write_Cmd(0x34);
	Write_Cmd(y);
	Write_Cmd(x);
}

void DISPIcon(uchar x,uchar y,uchar clong,uchar hight,uchar *Icon)//����ͼ��
{
	uchar i,j;
	for(i=0;i<hight;i++)
	{
		if(y+i<32)
			Cursor(0x80+x/16,0x80+y+i);//�ϰ����趨��ʼλ��
		else
			Cursor(0x88+x/16,0x80-32+y+i);//�°����趨��ʼλ��
		for(j=0;j<clong;j++)
			Write_Data(Icon[clong*i+j]);
	}
	Write_Cmd(0x36);
	Write_Cmd(0x30);
} 


 /*********************************************   LCD12864Һ����ʼ���ӳ���  *********************************************/ 
 void Ini_Lcd(void)     
 {     

	 PSB=1;     
	 Delay_1ms(20);                  
	 Write_Cmd(0x30);   //����ָ�     
	 Delay_1ms(20);      
	 Write_Cmd(0x02);   // ��ַ��λ     
	 Delay_1ms(20);      
	 Write_Cmd(0x0c);   //������ʾ��,�α�ر�     
	 Delay_1ms(20);      
	 Write_Cmd(0x06);   //�α�����     
	 Delay_1ms(20);      
	 Write_Cmd(0x80);   //�趨��ʾ����ʼ��ַ     
	 Delay_1ms(20);      
	 Write_Cmd(0x01);   //�����ʾ 
 }


void antibackgroud(uint hang)//ĳһ���׷�����ʾ
{
	Write_Cmd(0x80+8*(hang/2)+16*(hang%2));
	Write_Cmd(0x0F);
}


/*******************��ʱ�ӳ���  ********************/ 
void Delay_1ms(uint x) 
{  
	uint j,i;   
	for(j=0;j<x;j++)   
	{    
		for(i=0;i<120;i++);   //��ʱX����120  
	}  
}


void delayNus(uchar x)	//LCD����ʱָ�������֮�����ʱ
{
uchar k;
for(k=0;k<x;k++);
}
