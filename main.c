#include "sys_fun.h"
#include "songs.h"
#include "display.h"
#define uchar unsigned char
void play_start(uchar (*music)[2]);
void delay(uchar p);
uchar m,n; 



uchar port_status;
uchar key,k=0;
unsigned char Count;

uchar key_1,key_tune;
void main()
{ 
	uchar i=0;
	P4M1=0x00;
	P4M0=0x00;
	Ini_Lcd();//液晶初始化子程序
	Disp(1,0,14,"欢迎使用无弦琴");//显示数据到LCD12864子程序			
	Disp(2,0,14,"欢迎使用无弦琴");//显示数据到LCD12864子程序
	Disp(3,0,14,"欢迎使用无弦琴");//显示数据到LCD12864子程序
	Disp(4,0,12,"浙大光电学院");//显示数据到LCD12864子程序
	play_start(music0);			 
		
	while(1)
	{
		key_1=00;
		KeyIO=0xf0;
		P4M1=0x00;
		P4M0=0x00;
		Ini_Lcd();//液晶初始化子程序			
		Disp(1,0,8,"选择功能");//显示数据到LCD12864子程序
		Disp(2,0,10,"1.音乐播放");//显示数据到LCD12864子程序
		Disp(3,0,10,"2.音乐演奏");//显示数据到LCD12864子程序
		Disp(4,0,10,"3.娱乐功能");//显示数据到LCD12864子程序
		while (1)
			{
				if ((KeyIO&0xf0)!=0xf0)
				Delay_xMs(100);
				if((KeyIO&0xf0)!=0xf0){
				key_1=scankey();
				break; }
			}

		switch (key_1)
		{

      case 11:
			{
				unsigned char page=1;
				while (1)
				{
					switch (page)
					{
						case 1:
							{
							key=00;
							KeyIO=0xf0;
							Ini_Lcd();//液晶初始化子程序
							Disp(1,0,14,"请选择播放歌曲");//显示数据到LCD12864子程序			
							Disp(2,0,8,"1.歌曲1");//显示数据到LCD12864子程序
							Disp(3,0,8,"2.歌曲2");//显示数据到LCD12864子程序
							Disp(4,0,8,"4.下一页");//显示数据到LCD12864子程序
							while (1)
							{
								if ((KeyIO&0xf0)!=0xf0)
							{
								Delay_xMs(100);
								if ((KeyIO&0xf0)!=0xf0)
								{
								key=scankey();
								break;	
								}
							}	
							}
							switch (key)
							{
							case 11:
								Ini_Lcd();
								Disp(2,0,12,"歌曲1:播放中");
								Disp(4,0,8,"16：退出");
								play_start(music1); 
								break;//显示数据到LCD12864子程序
							case 12:
								Ini_Lcd();
								Disp(2,0,12,"歌曲2:播放中");
								Disp(4,0,8,"16：退出");
								play_start(music2);	
								break;//显示数据到LCD12864子程
							case 14:
								page=2;
								break;
							default: break;
							}
							break;
							}
						case 2:
							{
							key=00;
							KeyIO=0xf0;
							Ini_Lcd();//液晶初始化子程序
							Disp(1,0,14,"请选择播放歌曲");//显示数据到LCD12864子程序			
							Disp(2,0,8,"1.歌曲3");//显示数据到LCD12864子程序
							Disp(3,0,10,"2.录音播放");//显示数据到LCD12864子程序
							Disp(4,0,8,"3.上一页");//显示数据到LCD12864子程序
							while (1)
							{
								if ((KeyIO&0xf0)!=0xf0)
								{
									Delay_xMs(100);
									if ((KeyIO&0xf0)!=0xf0)
									{
										key=scankey();	
										break;
									}
								}
							}
							switch (key)
							{
							case 11:
								Ini_Lcd();
								Disp(2,0,12,"歌曲3:播放中");
								Disp(4,0,8,"16：退出");
								play_start(music3); 
								break;//显示数据到LCD12864子程序
							case 12:
								Ini_Lcd();
								Disp(2,0,11,"录音:播放中");
								Disp(4,0,8,"16：退出");
								play_start(music6);	
								break;//显示数据到LCD12864子程
							case 13:
								page=1;
								break;
							default: break;
							} 
							break;
							}
							default: break;
					}
					if (key==43)
					break;
				}
				break;
			}
			
			case 12:
		  { 
			  char tune=0;
			  key=00;
			  KeyIO=0xF0; 
			  Ini_Lcd();
			  Disp(1,0,12,"进行弹奏模式");//显示数据到LCD12864子程序
			  Disp(4,0,12,"1.录2.停3.放");//显示数据到LCD12864子程序
			  while(key!=44)
			  {
			  if((P1&0xf0)!=0xf0) //如果有键按下
		    {
		      Delay_xMs(100);   //延时去抖动
		      if((KeyIO&0xf0)!=0xf0)   //再判断
		      {
						key=scankey();
						switch(key)
						{
							case 11:Disp(3,0,8,"录音开启");	k=1;i=0;break;//显示数据到LCD12864子程序
							case 12:Disp(3,0,8,"录音关闭");  k=0;music6[i+1][0]==0xFF;	music6[i+1][1]==0xFF;i=0;break;//显示数据到LCD12864子程序
							case 13:Disp(3,0,8,"播放录音");play_start(music6);Disp(3,0,8,"退出播放");	break;//显示数据到LCD12864子程序
						}
					}   
				}
				
			 OPT_CHECK = 0xFF;
			 key_tune=00;
			 KeyIO=0xf0;
			 if ((P1&0xf0)!=0xf0)
			 {
			 	Delay_xMs(50);
			 	if ((P1&0xf0)!=0xf0)
			 	key_tune=scankey();
			 }
			 if (OPT_CHECK!=0xff)
				 {
					 switch(key_tune)
					 {
					 	case 00:
					 	Disp(3,0,6,"middle");
					 	tune=0;
					 	break;
					 	case 41:
					 	Disp(3,0,6,"high  ");
					 	tune=1;
					 	break;
					 	case 42:
					 	Disp(3,0,6,"low   ");
					 	tune=-1;
					 	break;
					 }	
				 }
			 
  				if(!(OPT_CHECK&0x01))
				 {
				    Disp(2,0,8,"音调：1");
					 m=13+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x02))
				 {
				   Disp(2,0,8,"音调：2");
					 m=15+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x04))
				 {
				   Disp(2,0,8,"音调：3");
					 m=17+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x08))
				 {
				   Disp(2,0,8,"音调：4");
					 m=18+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x10))
				 {
				  Disp(2,0,8,"音调：5");
					 m=20+12*tune,n=2;
					
				 }
				 else if(!(OPT_CHECK&0x20))
				 {
				   Disp(2,0,8,"音调：6");
					 m=22+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x40))
				 {
				   Disp(2,0,8,"音调：7");
					 m=24+12*tune,n=2;
				 }
				 else{
				 	m=0,n=2;
					 TR0=0;
				 	Disp(2,0,8,"音调：0");
				 }
				 
				 if(k==1){
				 music6[i][0]=m;
					music6[i][1]=n*2;
					i++;
				 }
				 
				 if(i>=50){
				 music6[i][0]=0xFF;
					music6[i][1]=0xFF;
					i=0;k=0;
					 Disp(3,0,8,"录音关闭");
				 } 
				 if(m==0)
      	{TR0=0;delay(n);}
         else
{TR0=1;delay(n);}
				 
		}	
		}
		break;
		default: break;  	
		}
	}
}


	
	
/*****************检测控制端口的状态*****************/
uchar ctrl_port_check(void)
{
		SW_CTRL = 0xFF;
		return 	SW_CTRL&0xF0;
}


	 
/****************延迟毫秒数************************/
void Delay_xMs(unsigned int x)
{
    unsigned int i,j;
    for( i =0;i < x;i++ )
    {
        for( j =0;j<2;j++ );
    }
}


void delay(uchar p)
{
uchar i,j; 
for(;p>0;p--)
for(i=181;i>0;i--)
for(j=181;j>0;j--);
}
void pause()
{
uchar i,j;
for(i=150;i>0;i--)
for(j=150;j>0;j--);
}
void T0_int() interrupt 1
{
bee_Speak=!bee_Speak;

TH0=T[m][0]; TL0=T[m][1];
}
void play_start(uchar (*music)[2])
{
uchar i=0; 
TMOD=0x01; EA=1; ET0=1; 

while(1) 
{
if((P1&0xf0)!=0xf0) //如果有键按下
{
	Delay_xMs(100);   //延时去抖动
	if((KeyIO&0xf0)!=0xf0)   //再判断
	{
		key=scankey();
	  if(key==44){
		  TR0=0;
      return;
	  }
	}
}   
				
m=music[i][0];n=music[i][1];				
if(m==0x00)
{TR0=0;delay(n);i++;} 
else if(m==0xFF)
{TR0=0;
return;
} 
else
{TR0=1;delay(n);i++;}
}
}

uchar scankey(void)//矩阵键盘翻转扫描
{
	uint keyvalue=0;
	uchar temp1,temp2,keycode;

	KeyIO=0xf0;		//行置0列置1
	temp1=KeyIO&0xf0;
	if((temp1&0xf0)==0xf0) return(0);  //若无键按下返回0
	KeyIO=0x0f;
	temp2=KeyIO&0x0f;					   //若有键按下，行置1列置0
	keycode=~(temp1|temp2);			   //获得键盘码
	switch(keycode)					   //根据键盘码返回键值
	{
		case 0x11:return(11);break;
		case 0x21:return(12);break;
		case 0x41:return(13);break;
		case 0x81:return(14);break;
		case 0x12:return(21);break;
		case 0x22:return(22);break;
		case 0x42:return(23);break;
		case 0x82:return(24);break;
		case 0x14:return(31);break;
		case 0x24:return(32);break;
		case 0x44:return(33);break;
		case 0x84:return(34);break;
		case 0x18:return(41);break;
		case 0x28:return(42);break;
		case 0x48:return(43);break;
		case 0x88:return(44);break;
		default:  return(0);break;
	}
	return(0);
}

//按任意键退出

