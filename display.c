#include "sys_cfg.h"
#include "display.h"


/***********LCD12864液晶测忙子程序(读状态)************/ 
void Busy()   
{   
	uchar busy;
	do  
	{      
		E = 0;      //0为关闭使能端,1为打开使能端      
		DI = 0;      //1为指令,0为数据      
		RW = 1;    //1为读,0为写       
		Delay_1ms(20);  //延时20乘以120时间      
		E = 1;     //0为关闭使能端,1为打开使能端  
		P2M0=0x00;
		P2M1=0x00;	//将P2设为准双向（传统51IO口）  
		busy=P2;    //读取P2状态      
		Delay_1ms(20);  //延时20乘以120时间      
		E = 0;    //0为关闭使能端,1为打开使能端     
	}while(busy&0x80);  //判断BUSY位是否工作:1为内部在工作,0为正常状态 
}  
/*********************************************   LCD12864液晶数据写入子程序  *********************************************/ 
void Write_Data(uchar k) 
{   
	Busy();   //测忙
	E =1;   //0为关闭使能端,1为打开使能端    
	DI=1;   //1为指令,0为数据    
	RW=0;   //1为读,0为写   
	P2M0=0xFF;
	P2M1=0x00;	//将P2设为推挽  	
	P2=k;   //输入数据K到DATA    
	Delay_1ms(20); //延时20乘以120时间    
	E =0;    //0为关闭使能端,1为打开使能端    
	Delay_1ms(20);   //延时20乘以120时间 
}  

/*********************************************   LCD12864液晶命令写入子程序  *********************************************/ 
void Write_Cmd(uchar cmd) 
{      
	Busy();    //测忙
	E=1;   //0为关闭使能端,1为打开使能端     
	DI=0;    //1为指令,0为数据     
	RW=0;   //1为读,0为写   
	P2M0=0xFF;
	P2M1=0x00;	//将P2设为推挽 
	P2=cmd;    //输入命令cmd到DATA     
	Delay_1ms(20); //延时20乘以120时间 
	E=0;   //0为关闭使能端,1为打开使能端     
	Delay_1ms(20); //延时20乘以120时间 
}  


//显示数组字符串(显示半宽字型16*8点阵)
void ShowQQChar(uchar addr,uchar *english,uchar count)//DDRAM地址，数据首字节指针，数据长度
{
	uchar i;
	Write_Cmd(addr); //设定DDRAM地址
	for(i=0;i<count;)
	{
		Write_Data(english[i*2]);
		Write_Data(english[i*2+1]);
		i++;
	}
}

//字符和汉字显示
/*********************************************   LCD12864液晶数据显示子程序  *********************************************/ 
void Disp(uchar y,uchar x,uchar i,uchar *z)   
{     
	uchar Address;    
	//Y判断第几行,X判断第几列,0x80为液晶行初始地址    
	if(y==1)  Address=0x80+x;
	if(y==2){Address=0x90+x;}        
	if(y==3){Address=0x88+x;}    
	if(y==4){Address=0x98+x;}  
	Write_Cmd(Address);//写入地址命令到LCD12864  
	while(i)       //写入显示数据的大小  
	{    
		Write_Data(*(z++));    //写入显示数据到LCD12864    
		i--;         
	}   
} 
	
//自定义字符1（16X16）写入CGRAM //
void WRCGRAM1(uchar addr)//单下划线
{
	uchar i;
	for(i=0;i<2;)
	{
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	for(i=2;i<16;i++)
	{
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

//自定义字符2（16X16）写入CGRAM //
void WRCGRAM2(uchar addr)//双下划线
{
	uchar i;
	for(i=0;i<4;)
	{
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	for(i=4;i<16;i++)
	{
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

//自定义字符3（16X16）写入CGRAM //
void WRCGRAM3(uchar addr)//单下划线加点
{
	uchar i;
	for(i=0;i<2;)
	{
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0x00);
		Write_Data(0x00);
		i++;
	}
	for(i=2;i<6;)
	{
		Write_Cmd(addr+i); //设定CGRAM地址
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
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

//自定义字符4（16X16）写入CGRAM //
void WRCGRAM4(uchar addr)//双下划线加点
{
	uchar i;
	for(i=0;i<4;)
	{
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0xff);
		Write_Data(0x00);
		i++;
		Write_Cmd(addr+i); //设定CGRAM地址
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
		Write_Cmd(addr+i); //设定CGRAM地址
		Write_Data(0x00);
		Write_Data(0x00);
	}
}

void CLEARGDRAM(void)//绘图清屏	 
{
	uchar j;
	uchar i;
	Write_Cmd(0x34);  //切换扩充指令集
	Write_Cmd(0x36);  //绘图显示开
	for(j=0;j<32;j++)
	{
		Write_Cmd(0x80+j);//y坐标 共32行
		Write_Cmd(0x80);//X坐标
		for(i=0;i<32;i++)//
		{
			Write_Data(0x00);//绘空格32*8个即256空格
		}
	}
}

//写入GDRAM 绘图,Y是Y绘图坐标,2个字节一行,CLONG是图形长度,以字节
//为单位;HIGHT是图形高度,TAB是图形数据表.12864M的图形显示是相当于256*32.
//由两屏128*32上下两屏组成，同一行的下屏的头地址紧接上屏的未地址。
//绘图在串口输入时,会比在并口下的输入要慢一些
void WRGDRAM(uchar Y1,uchar clong,uchar hight,uchar *TAB1)
{
	uint k;
	uchar j;
	uchar i;
	Write_Cmd(0x34);
	Write_Cmd(0x36);
	for(j=0;j<hight;j++)//32
	{ //先上半屏
		Write_Cmd(Y1+j); //Y总坐标,即第几行
		Write_Cmd(0x80);//X坐标0，即横数第0个字节开始写起		
		for(i=0;i<clong;i++)//
		{
			Write_Data(TAB1[clong*j+i]);
		}
	//后下半屏
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

void DISPIcon(uchar x,uchar y,uchar clong,uchar hight,uchar *Icon)//插入图标
{
	uchar i,j;
	for(i=0;i<hight;i++)
	{
		if(y+i<32)
			Cursor(0x80+x/16,0x80+y+i);//上半屏设定起始位置
		else
			Cursor(0x88+x/16,0x80-32+y+i);//下半屏设定起始位置
		for(j=0;j<clong;j++)
			Write_Data(Icon[clong*i+j]);
	}
	Write_Cmd(0x36);
	Write_Cmd(0x30);
} 


 /*********************************************   LCD12864液晶初始化子程序  *********************************************/ 
 void Ini_Lcd(void)     
 {     

	 PSB=1;     
	 Delay_1ms(20);                  
	 Write_Cmd(0x30);   //基本指令集     
	 Delay_1ms(20);      
	 Write_Cmd(0x02);   // 地址归位     
	 Delay_1ms(20);      
	 Write_Cmd(0x0c);   //整体显示打开,游标关闭     
	 Delay_1ms(20);      
	 Write_Cmd(0x06);   //游标右移     
	 Delay_1ms(20);      
	 Write_Cmd(0x80);   //设定显示的起始地址     
	 Delay_1ms(20);      
	 Write_Cmd(0x01);   //清除显示 
 }


void antibackgroud(uint hang)//某一行首反白显示
{
	Write_Cmd(0x80+8*(hang/2)+16*(hang%2));
	Write_Cmd(0x0F);
}


/*******************延时子程序  ********************/ 
void Delay_1ms(uint x) 
{  
	uint j,i;   
	for(j=0;j<x;j++)   
	{    
		for(i=0;i<120;i++);   //延时X乘以120  
	}  
}


void delayNus(uchar x)	//LCD串口时指令和数据之间的延时
{
uchar k;
for(k=0;k<x;k++);
}
