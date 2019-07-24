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
	Ini_Lcd();//Һ����ʼ���ӳ���
	Disp(1,0,14,"��ӭʹ��������");//��ʾ���ݵ�LCD12864�ӳ���			
	Disp(2,0,14,"��ӭʹ��������");//��ʾ���ݵ�LCD12864�ӳ���
	Disp(3,0,14,"��ӭʹ��������");//��ʾ���ݵ�LCD12864�ӳ���
	Disp(4,0,12,"�����ѧԺ");//��ʾ���ݵ�LCD12864�ӳ���
	play_start(music0);			 
		
	while(1)
	{
		key_1=00;
		KeyIO=0xf0;
		P4M1=0x00;
		P4M0=0x00;
		Ini_Lcd();//Һ����ʼ���ӳ���			
		Disp(1,0,8,"ѡ����");//��ʾ���ݵ�LCD12864�ӳ���
		Disp(2,0,10,"1.���ֲ���");//��ʾ���ݵ�LCD12864�ӳ���
		Disp(3,0,10,"2.��������");//��ʾ���ݵ�LCD12864�ӳ���
		Disp(4,0,10,"3.���ֹ���");//��ʾ���ݵ�LCD12864�ӳ���
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
							Ini_Lcd();//Һ����ʼ���ӳ���
							Disp(1,0,14,"��ѡ�񲥷Ÿ���");//��ʾ���ݵ�LCD12864�ӳ���			
							Disp(2,0,8,"1.����1");//��ʾ���ݵ�LCD12864�ӳ���
							Disp(3,0,8,"2.����2");//��ʾ���ݵ�LCD12864�ӳ���
							Disp(4,0,8,"4.��һҳ");//��ʾ���ݵ�LCD12864�ӳ���
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
								Disp(2,0,12,"����1:������");
								Disp(4,0,8,"16���˳�");
								play_start(music1); 
								break;//��ʾ���ݵ�LCD12864�ӳ���
							case 12:
								Ini_Lcd();
								Disp(2,0,12,"����2:������");
								Disp(4,0,8,"16���˳�");
								play_start(music2);	
								break;//��ʾ���ݵ�LCD12864�ӳ�
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
							Ini_Lcd();//Һ����ʼ���ӳ���
							Disp(1,0,14,"��ѡ�񲥷Ÿ���");//��ʾ���ݵ�LCD12864�ӳ���			
							Disp(2,0,8,"1.����3");//��ʾ���ݵ�LCD12864�ӳ���
							Disp(3,0,10,"2.¼������");//��ʾ���ݵ�LCD12864�ӳ���
							Disp(4,0,8,"3.��һҳ");//��ʾ���ݵ�LCD12864�ӳ���
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
								Disp(2,0,12,"����3:������");
								Disp(4,0,8,"16���˳�");
								play_start(music3); 
								break;//��ʾ���ݵ�LCD12864�ӳ���
							case 12:
								Ini_Lcd();
								Disp(2,0,11,"¼��:������");
								Disp(4,0,8,"16���˳�");
								play_start(music6);	
								break;//��ʾ���ݵ�LCD12864�ӳ�
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
			  Disp(1,0,12,"���е���ģʽ");//��ʾ���ݵ�LCD12864�ӳ���
			  Disp(4,0,12,"1.¼2.ͣ3.��");//��ʾ���ݵ�LCD12864�ӳ���
			  while(key!=44)
			  {
			  if((P1&0xf0)!=0xf0) //����м�����
		    {
		      Delay_xMs(100);   //��ʱȥ����
		      if((KeyIO&0xf0)!=0xf0)   //���ж�
		      {
						key=scankey();
						switch(key)
						{
							case 11:Disp(3,0,8,"¼������");	k=1;i=0;break;//��ʾ���ݵ�LCD12864�ӳ���
							case 12:Disp(3,0,8,"¼���ر�");  k=0;music6[i+1][0]==0xFF;	music6[i+1][1]==0xFF;i=0;break;//��ʾ���ݵ�LCD12864�ӳ���
							case 13:Disp(3,0,8,"����¼��");play_start(music6);Disp(3,0,8,"�˳�����");	break;//��ʾ���ݵ�LCD12864�ӳ���
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
				    Disp(2,0,8,"������1");
					 m=13+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x02))
				 {
				   Disp(2,0,8,"������2");
					 m=15+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x04))
				 {
				   Disp(2,0,8,"������3");
					 m=17+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x08))
				 {
				   Disp(2,0,8,"������4");
					 m=18+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x10))
				 {
				  Disp(2,0,8,"������5");
					 m=20+12*tune,n=2;
					
				 }
				 else if(!(OPT_CHECK&0x20))
				 {
				   Disp(2,0,8,"������6");
					 m=22+12*tune,n=2;
					 
				 }
				 else if(!(OPT_CHECK&0x40))
				 {
				   Disp(2,0,8,"������7");
					 m=24+12*tune,n=2;
				 }
				 else{
				 	m=0,n=2;
					 TR0=0;
				 	Disp(2,0,8,"������0");
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
					 Disp(3,0,8,"¼���ر�");
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


	
	
/*****************�����ƶ˿ڵ�״̬*****************/
uchar ctrl_port_check(void)
{
		SW_CTRL = 0xFF;
		return 	SW_CTRL&0xF0;
}


	 
/****************�ӳٺ�����************************/
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
if((P1&0xf0)!=0xf0) //����м�����
{
	Delay_xMs(100);   //��ʱȥ����
	if((KeyIO&0xf0)!=0xf0)   //���ж�
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

uchar scankey(void)//������̷�תɨ��
{
	uint keyvalue=0;
	uchar temp1,temp2,keycode;

	KeyIO=0xf0;		//����0����1
	temp1=KeyIO&0xf0;
	if((temp1&0xf0)==0xf0) return(0);  //���޼����·���0
	KeyIO=0x0f;
	temp2=KeyIO&0x0f;					   //���м����£�����1����0
	keycode=~(temp1|temp2);			   //��ü�����
	switch(keycode)					   //���ݼ����뷵�ؼ�ֵ
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

//��������˳�

