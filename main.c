#include "sys_fun.h"
#include "image.h"
#include "songs.h"
#include "display.h"
#define uchar unsigned char
void play_start(uchar (*music)[2]);
void show_score(uchar (*music)[2]);
void delay(uchar p);
unsigned char win_xo(void);
unsigned char win_1(unsigned char x, unsigned char y);
unsigned char win_2(unsigned char x, unsigned char y);

uchar m,n; 

char dot_h=0x2e;
char dot_l=0x07;
uchar start=1;
uchar port_status;
uchar key,k=0;
unsigned char Count;

uchar key_1,key_tune;
void main()
{ 
	uchar i=0,j=0;
	uchar i_cide=0,key_cide;
	uchar clong,hight;
	hight=32;
	clong=16;
	Ini_Lcd();//液晶初始化子程序
	WRGDRAM(0x80,clong,hight,gImage_1);//开机图片	
	P4M1=0x00;
	P4M0=0x00;
	Ini_Lcd();//液晶初始化子程序
	WRCGRAM1(0x40);
	WRCGRAM2(0x50);
	WRCGRAM3(0x60);
	WRCGRAM4(0x70);
	Disp(1,0,16,"****************");//显示数据到LCD12864子程序			
	Disp(2,0,14,"欢迎使用无弦琴");//显示数据到LCD12864子程序
	Disp(3,0,12,"浙大光电学院");//显示数据到LCD12864子程序
	Disp(4,0,16,"****************");//显示数据到LCD12864子程序
	play_start(music0);		
	start=0;	
	Ini_Lcd();
    Disp(1,0,14,"请输入开机密码");
    for (i=0;i<5;i++)
    {
    Write_Cmd(0x88+i);
    Write_Data(0x00);
    Write_Data(0x00);
    }
    Write_Cmd(0x88+i_cide);
    Write_Data(0x00);
    Write_Data(0x02);
    while (1)
    {
        bit flag_cide;
        flag_cide=0;
        key_cide=00;
        while (1)
        {
            KeyIO=0xf0;
            if((KeyIO&0xf0)!=0xf0)
            {
                Delay_xMs(100);
                if ((KeyIO&0xf0)!=0xf0)
                {
                key_cide=scankey();
                KeyIO=0xf0;
                while (KeyIO!=0xf0);
                break;
                }
            }
        }
        switch (key_cide)
        {
            case 11:
            cide[i_cide]=1+0x30;
            break;
            case 12:
            cide[i_cide]=2+0x30;
            break;
            case 13:
            cide[i_cide]=3+0x30;
            break;
            case 14:
            cide[i_cide]=4+0x30;
            break;
            case 21:
            cide[i_cide]=5+0x30;
            break;
            case 22:
            cide[i_cide]=6+0x30;
            break;
            case 23:
            cide[i_cide]=7+0x30;
            break;
            case 24:
            cide[i_cide]=8+0x30;
            break;
            case 31:
            cide[i_cide]=9+0x30;
            break;
            default:
            if (i_cide)
            {
            if (i_cide<4||cide[4]==0x30)
            {
            i_cide--;
            cide[i_cide]=0+0x30;
            }
            else
            cide[i_cide]=0+0x30;
            }
            break;
        }
        if (i_cide<4&&key_cide<32)
        i_cide++;  
        for (i=0;i<5;i++)
        {
            if (cide[i]-0x30)
            Disp(2,i,1,cide+i);
            else
            Disp(2,i,2," ");
        }
        for (i=0;i<5;i++)
        {
        Write_Cmd(0x88+i);
        Write_Data(0x00);
        Write_Data(0x00);
        }
        Write_Cmd(0x88+i_cide);
        Write_Data(0x00);
        Write_Data(0x02);
        if (i_cide==4&&key_cide<32)
        {
            flag_cide=1;
            for (i=0;i<5;i++)
            if (cide[i]!=cide_check[i])
            {
            flag_cide=0;
            break;
            }
        }
        if (flag_cide)
        break;
    }

	
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
                if (key_1>=11&&key_1<=13)
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
                                if (key==11||key==12||key==14||key==43)
								break;	
								}
							}	
							}
							switch (key)
							{
							case 11:
								Ini_Lcd();
								Disp(4,5,6,"播放中");
						  	Disp(4,0,8,"16：退出");
								play_start(music1); 
								break;//显示数据到LCD12864子程序
							case 12:
								Ini_Lcd();
								Disp(4,5,6,"播放中");
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
                                        if (key==11||key==12||key==13||key==43)	
										break;
									}
								}
							}
							switch (key)
							{
							case 11:
								Ini_Lcd();
								Disp(4,5,6,"播放中");
						  	Disp(4,0,8,"16：退出");
								play_start(music3); 
								break;//显示数据到LCD12864子程序
							case 12:
                                if (music6[1][0]==0)
                                {
                                Ini_Lcd();
                                Disp(4,0,8,"16：退出");
                                Disp(4,5,6,"无音频");
                                KeyIO=0xf0;
                                while (1)
                                {
                                    if ((P1&0xf0)!=0xf0)
                					{
                						Delay_xMs(50);
                					 	if ((P1&0xf0)!=0xf0)
                					 	{
                                        if (scankey()==44)
                                        break;
                                        }
                					}
                                }
                                break;
    							}
								Ini_Lcd();
								Disp(4,5,6,"播放中");
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
                bit flag=0;
                Ini_Lcd();
				Disp(1,0,12,"进行弹奏模式");//显示数据到LCD12864子程序
				Disp(4,0,12,"1.录2.停3.放");//显示数据到LCD12864子程序
			  	while (1)
			  	{
			  		char tune=0;
					key=00;
					KeyIO=0xf0;
					if ((P1&0xf0)!=0xf0)
			  		{
				  		Delay_xMs(100);
						if ((P1&0xf0)!=0xf0)
						key=scankey();	
					} 
                    switch(key)
			  		{
			  			case 11:
							Disp(3,0,8,"录音开启");
							k=1;i=0;
							break;//显示数据到LCD12864子程序	
			  			case 12:
			  				Disp(3,0,8,"录音关闭");
							k=0;
                            flag=0;
                            music6[i][0]=0xff;
							music6[i][1]=0xff;
                            i=0;
							break;//显示数据到LCD12864子程序
						case 13:
                            if (music6[1][0]==0)
                            {
                            Disp(3,0,6,"无音频");
                            break;
							}
                            //show_score(music0);
                            Ini_Lcd();
                            Disp(4,0,8,"16：退出");
							play_start(music6+1);
                            Ini_Lcd();
                            Disp(1,0,12,"进行弹奏模式");//显示数据到LCD12864子程序
				            Disp(4,0,12,"1.录2.停3.放");//显示数据到LCD12864子程序
							break;//显示数据到LCD12864子程序
					}
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
							case 41:
							Disp(2,5,6,"high  ");
							tune=1;
							break;
							case 42:
							Disp(2,5,6,"low   ");
							tune=-1;
							break;
                            default:
                            Disp(2,5,6,"middle");
							tune=0;
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
                         if (k==1&&flag==0)
                         {
                         if (m!=0)
                         flag=1;
                         for (i=0;i++;i<60)
                         {
                         music6[i][0]=0;
                         music6[i][1]=0;
                         }
                         i=1;
                         }
						 if(k==1&&flag==1){
                         if (music6[i-1][0]==m&&music6[i-1][1]==4)
                         music6[i-1][1]=music6[i-1][1]+4;
                         else
                         {
                         music6[i][0]=m;
						 music6[i][1]=n*2;
                         i++;
                         }
						 }
						 if(i>=61){
						 	music6[i][0]=0xFF;
							music6[i][1]=0xFF;
							i=0;k=0;flag=0;
							Disp(3,0,8,"录音关闭");
						 } 
						 if(m==0)
							{
							TR0=0;
							delay(n);}
						 else
						 	{
							 TR0=1;
							 delay(n);
							}
						if (key==43)
                        {
                            TR0=0;
                            break;
                        }
						
			  	}
			  	break;
			}
       case 13:
		{  
            char key_game;
            while (1)
            {
                key_game=00;
                Ini_Lcd();
                Disp(1,0,10,"1:节奏大师");
                Disp(2,0,8,"2:sudoku");
                Disp(3,0,10,"3:圈圈叉叉");
                Disp(4,0,8,"15：退出");
                while (1)
                {
                    KeyIO=0xf0;
                    if ((KeyIO&0xf0)!=0xf0)
                    {
                        Delay_xMs(100);
                        if ((KeyIO&0xf0)!=0xf0)
                        {
                            key_game=scankey();
                            if (key_game==11||key_game==12||key_game==13||key_game==43)
                            break;
                        }
                    }
                }
                if (key_game==43)
                    break;
                switch (key_game)
                {
                case 11:
                {
                while(1)
                {
    			char flag2=1,flag=1,mm,nn,sum,check,choice;
					check=0;
					sum=0;
    			Ini_Lcd();	
    			Disp(1,0,8,"演奏大师");
    			Disp(2,0,8,"1:小星星");
    			Disp(3,0,10,"2:同桌的你");
                Disp(4,0,8,"15：退出");
    			key=00;
    		    KeyIO=0xf0;
                while (1)
    			{
    				if ((KeyIO&0xf0)!=0xf0)
    					{
    					Delay_xMs(100);
    					if ((KeyIO&0xf0)!=0xf0)
    					{
    						key=scankey();	
    						if (key==43||key==11||key==12)
    						break;
    						}
    					}
    			}
                if (key==43)
                {
                TR0=0;
                break;
                }
    				switch(key){
    					case 11:
    						flag2=0;
    						choice=1;
    					  break;	
    					case 12:
    						flag2=0;
    						choice=2;
    					  break;
    					default: break;
    				}
    			//sum=0;
    			if(flag2==0){
    				Ini_Lcd();
    			for(i=1;;i++)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               {
    				char tune=0;
    				sum++;
    				flag=1;
    				if(choice==1)
    					mm=music4[i][0];
    				else if(choice==2)
    					mm=music5[i][0];
    				if(mm==13) Disp(2,0,9,"弹奏：1 M");
    				else if(mm==15) Disp(2,0,9,"弹奏：2 M");
    				else if(mm==17) Disp(2,0,9,"弹奏：3 M");
    				else if(mm==18) Disp(2,0,9,"弹奏：4 M");
    				else if(mm==20) Disp(2,0,9,"弹奏：5 M");
    				else if(mm==22) Disp(2,0,9,"弹奏：6 M");
    				else if(mm==24) Disp(2,0,9,"弹奏：7 M");
    				
    				else if(mm==1) Disp(2,0,9,"弹奏：1 L");
    				else if(mm==3) Disp(2,0,9,"弹奏：2 L");
    				else if(mm==5) Disp(2,0,9,"弹奏：3 L");
    				else if(mm==6) Disp(2,0,9,"弹奏：4 L");
    				else if(mm==8) Disp(2,0,9,"弹奏：5 L");
    				else if(mm==10) Disp(2,0,9,"弹奏：6 L");
    				else if(mm==12) Disp(2,0,9,"弹奏：7 L");
    				
    				else if(mm==25) Disp(2,0,9,"弹奏：1 H");
    				else if(mm==27) Disp(2,0,9,"弹奏：2 H");
    				else if(mm==29) Disp(2,0,9,"弹奏：3 H");
    				else if(mm==30) Disp(2,0,9,"弹奏：4 H");
    				else if(mm==32) Disp(2,0,9,"弹奏：5 H");
    				else if(mm==34) Disp(2,0,9,"弹奏：6 H");
    				else if(mm==36) Disp(2,0,9,"弹奏：7 H");
    				
    				else if(mm==0) {
                        TR0=0;
    					flag2=1;break;
    				}
    				//++++++++++++++++++++++++++++++++++++++++++++++++
    					while(flag==1){
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
    							case 41:
    							Disp(3,4,1,"H");
    							tune=1;
    							break;
    							case 42:
    							Disp(3,4,1,"L");
    							tune=-1;
    							break;
                                default:
                                Disp(3,4,1,"M");
    							tune=0;
    							break;
    							}	
    						 }
                        if (key_tune==44)
                        {
                        TR0=0;
                        break;
                        }
                        
    				
    				//++++++++++++++++++++++++++++++++++++++++++++++++
    				
    			       // while(flag==1){
    				if(!(OPT_CHECK&0x01))
    				 {
    				    Disp(3,0,8,"音调：1");
    					  nn=13+12*tune;flag=0;
    					 m=13+12*tune,n=8;
    				 }
    				 else if(!(OPT_CHECK&0x02))
    				 {
    				   Disp(3,0,8,"音调：2");
    					 nn=15+12*tune;flag=0;
    					 m=15+12*tune,n=8;
    				 }
    				 else if(!(OPT_CHECK&0x04))
    				 {
    				   Disp(3,0,8,"音调：3");
    					 nn=17+12*tune;flag=0;
    					 m=17+12*tune,n=8;
    				 }
    				 else if(!(OPT_CHECK&0x08))
    				 {
    				   Disp(3,0,8,"音调：4");
    					 nn=18+12*tune;flag=0;
    					 m=18+12*tune,n=8;
    				 }
    				 else if(!(OPT_CHECK&0x10))
    				 {
    				  Disp(3,0,8,"音调：5");
    					 nn=20+12*tune;flag=0;
    					 m=20+12*tune,n=8;
    				 }
    				 else if(!(OPT_CHECK&0x20))
    				 {
    				   Disp(3,0,8,"音调：6");
    					 nn=22+12*tune;flag=0;
    					 m=22+12*tune,n=8;
    				 }
    				 else if(!(OPT_CHECK&0x40))
    				 {
    				   Disp(3,0,8,"音调：7");
    					 nn=24+12*tune;flag=0;
    					 m=24+12*tune,n=8;
    				 }
    				 else{
    				   nn=0;m=0,n=2;
    				 	 Disp(3,0,8,"音调：0");
    				 }
    				 if(m==0x00)
            			 {TR0=0;delay(n);} 
            			 else
            			 {TR0=1;delay(n);}
    			 }
                 if (key_tune==44)
                 {
                 TR0=0;
                 break;
                 }
    			 Delay_xMs(2000);
    			 if(mm==nn) check++;
    			 //if(i==42) flag2=1;
    			}
    		  }
    			if(sum-check<=1) Disp(4,0,4,"完美");
    			else if((sum-check>1)&&(sum-check<=5)) Disp(4,0,4,"不错");
    			else if((sum-check>5)&&(sum-check<=20)) Disp(4,0,4,"还行");
    			else if(sum-check>20) Disp(4,0,4,"失败");
    			check=0;
    			sum=0;
                Disp(1,0,10,"任意键返回");
                delay(200);
                KeyIO=0xf0;
                while (1)
    			{
    				if ((KeyIO&0xf0)!=0xf0)
                    {
    				Delay_xMs(100);
    				if((KeyIO&0xf0)!=0xf0)
    				break; 
                    }
    			} 
          
    		}
            break;
            }
            case 12:
            {
            for (i=0;i<4;i++)
                   {
                       for (j=0;j<4;j++)
                       num1[i][j]=num1_memo[i][j];
                   }
                   position[0]=1+0x30;
                   position[1]=1+0x30;
            Ini_Lcd();//液晶初始化子程序
            Disp(1,5,6,"x 位置");
            Disp(3,5,6,"y 位置");
            for (i=0;i<4;i++)
                {
                     for (j=0;j<4;j++)
                     {
                     if (num1[i][j]-0x30)
                     Disp(i+1,j,1,*(num1+i)+j);
                     }     
                } 
            while (1)
            {   
                char i,j;
                bit flag=1;
                char key_num; 
                
                Disp(2,5,1,position);
                Disp(4,5,1,position+1);
                key_num=00;
                while (1)
                {
                if ((KeyIO&0xf0)!=0xf0)
                Delay_xMs(100);
                if ((KeyIO&0xf0)!=0xf0)
                {
                   key_num=scankey();
                   if ((key_num>=11&&key_num<=14&&(!num1_lock[position[1]-1-0x30][position[0]-1-0x30]))||(key_num>=21&&key_num<=24)||key_num==43)
                   {
                   KeyIO=0xf0;
                   while (KeyIO!=0xf0);
                   break;
                   }
                }
                }
                if (key_num==43)
                break;
                switch (key_num)
                {
                case 11:
                num1[position[1]-1-0x30][position[0]-1-0x30]=1+0x30;
                break;
                case 12:
                num1[position[1]-1-0x30][position[0]-1-0x30]=2+0x30;
                break;
                case 13:
                num1[position[1]-1-0x30][position[0]-1-0x30]=3+0x30;
                break;
                case 14:
                num1[position[1]-1-0x30][position[0]-1-0x30]=4+0x30;
                break;
                case 21:
                if (position[1]>1+0x30)
                position[1]=position[1]-1;
                break;
                case 22:
                if (position[1]<4+0x30)
                position[1]=position[1]+1;
                break;
                case 23:
                if (position[0]>1+0x30)
                position[0]= position[0]-1;
                break;
                case 24:
                if (position[0]<4+0x30)
                position[0]= position[0]+1;
                break;
                }
                for (i=0;i<4;i++)
                {
                     for (j=0;j<4;j++)
                     {
                     if (num1[i][j]-0x30)
                     Disp(i+1,j,1,*(num1+i)+j);
                     }     
                }
                for (i=0;i<4;i++)
                {
                    for (j=0;j<4;j++)
                    if (num1[i][j]!=num1_right[i][j])
                    flag=0;
                } 
                if (flag)
                {
                Ini_Lcd();//液晶初始化子程序
                Disp(1,0,10,"excellent!") ;
                Disp(4,0,10,"任意键返回");
                start=1;
                play_start(music0);
                start=0;
                delay(100);
                KeyIO=0xf0;
                while (1)
    			{
    				if ((KeyIO&0xf0)!=0xf0)
                    {
    				Delay_xMs(100);
    				if((KeyIO&0xf0)!=0xf0)
    				break; 
                    }
    			}
                    
                   break;
                }
            }
                break;
            }
            case 13:
            {   
                char win=0,count=0,difficulty=0,ahead=0,key_diffi=00;
                while (1)
                {
                ahead=0;
                win=0;
                count=0;
                key_diffi=00;
                //选择难度
                Ini_Lcd();
                Disp(1,0,12,"1:不可战胜的");
                Disp(2,0,6,"2:大师");
                Disp(3,0,6,"3:小白");
                Disp(4,0,8,"15：退出");
                while (1)
                {
                    KeyIO=0xf0;
                    if ((KeyIO&0xf0)!=0xf0)
                    {
                        Delay_xMs(100);
                        if ((KeyIO&0xf0)!=0xf0)
                        {
                        key_diffi=scankey();
                        if ((key_diffi>=11&&key_diffi<=13)||key_diffi==43)
                            {
                            KeyIO=0xf0;
                            while (KeyIO!=0xf0);
                            break;
                            }
                        }
                    }
               }
               if (key_diffi==43)
               break;
               switch (key_diffi)
               {
                   case 11:
                   difficulty=3;
                   break;
                   case 12:
                   difficulty=2;
                   break;
                   case 13:
                   difficulty=1;
                   break;
                }
                while(1)
                {
                    Ini_Lcd();//刷新显示
                    for (i=0;i<3;i++)
                    {
                        for (j=0;j<3;j++)
                        {
                        if (xo[i][j])
                        switch (xo[i][j])
                        {
                        case 1:
                        Disp(i+1,j,1,"X");
                        break;
                        case 2:
                        Disp(i+1,j,1,"O");
                        break;
                        }
                        }     
                    }
                    Disp(1,5,6,"x 位置");
                    Disp(2,5,1,position_xo);
                    Disp(3,5,6,"y 位置");
                    Disp(4,5,1,position_xo+1);
                    while (1)
                    {
                        bit flag_1=0; 
                        //determine the position of player 1
                        if (difficulty==3||(difficulty==2&&ahead==1)||(difficulty==1&&ahead==1))
                        {
                        for (i=0;i<3;i++)
                        {
                            for (j=0;j<3;j++)
                            {
                                if ((!xo[i][j])&&win_1(i,j))
                                {
                                xo[i][j]=1;
                                flag_1=1;
                                break;
                                }
                            }
                            if (flag_1)
                            break;
                        }
                        if (!flag_1)
                        {
                            for (i=0;i<3;i++)
                            {
                                for (j=0;j<3;j++)
                                {
                                    if ((!xo[i][j])&&win_2(i,j))
                                    {
                                        xo[i][j]=1;
                                        flag_1=1;
                                        break;
                                    }
                                }
                                if (flag_1)
                                break;
                            }
                        }
                        if ((!flag_1)&&difficulty!=1)
                        {
                            if (!xo[1][1])
                            xo[1][1]=1;
                            else if (!xo[0][0])
                            xo[0][0]=1;
                            else if (!xo[2][0])
                            xo[2][0]=1;
                            else if (!xo[0][2])
                            xo[0][2]=1;
                            else if (!xo[2][0])
                            xo[2][0]=1;
                            else if (!xo[0][1])
                            xo[0][1]=1;
                            else if (!xo[1][0])
                            xo[1][0]=1;
                            else if (!xo[1][2])
                            xo[1][2]=1;
                            else
                            xo[2][1]=1;
                        }
                        if ((!flag_1)&&difficulty==1)
                        {
                            
                            if (!xo[0][1])
                            xo[0][1]=1;
                            else if (!xo[1][0])
                            xo[1][0]=1;
                            else if (!xo[1][2])
                            xo[1][2]=1;
                            else if (!xo[2][1])
                            xo[2][1]=1;
                            else if (!xo[0][0])
                            xo[0][0]=1;
                            else if (!xo[2][0])
                            xo[2][0]=1;
                            else if (!xo[0][2])
                            xo[0][2]=1;
                            else if (!xo[2][0])
                            xo[2][0]=1;
                            else if (!xo[1][1])
                            xo[1][1]=1;
                        }
                        for (i=0;i<3;i++)
                        {
                            for (j=0;j<3;j++)
                            {
                            if (xo[i][j])
                            switch (xo[i][j])
                            {
                            case 1:
                            Disp(i+1,j,1,"X");
                            break;
                            case 2:
                            Disp(i+1,j,1,"O");
                            break;
                            }
                            }     
                        }
                        count++;
                        }
                        win=win_xo();
                        if (win)
                        break;
                        if (count==9)
                        {
                        win=3;
                        break;
                        }
                        //determine the position of player 2
                        while (1)
                        {
                            unsigned char key_xo=00;
                            while (1)
                            {
                                KeyIO=0xf0;
                                if ((KeyIO&0xf0)!=0xf0)
                                {
                                    Delay_xMs(100);
                                    if ((KeyIO&0xf0)!=0xf0)
                                    {
                                        key_xo=scankey();
                                        if ((key_xo>=11&&key_xo<=14)||key_xo==21||key_xo==43)
                                        break;
                                    }
                                }
                            }
                            KeyIO=0xf0;
                            while (KeyIO!=0xf0);
                            if (key_xo==43)
                            {
                            win=4;
                            break;
                            }
                            if (key_xo>=11&&key_xo<=14)
                            {
                                switch (key_xo)
                                {
                                case 11:
                                if (position_xo[1]>1+0x30)
                                position_xo[1]=position_xo[1]-1;
                                break;
                                case 12:
                                if (position_xo[1]<3+0x30)
                                position_xo[1]=position_xo[1]+1;
                                break;
                                case 13:
                                if (position_xo[0]>1+0x30)
                                position_xo[0]= position_xo[0]-1;
                                break;
                                case 14:
                                if (position_xo[0]<3+0x30)
                                position_xo[0]= position_xo[0]+1;
                                break;
                                }
                                Disp(2,5,1,position_xo);
                                Disp(4,5,1,position_xo+1);
                            }
                            else
                            {
                                if (!xo[position_xo[1]-1-0x30][position_xo[0]-1-0x30])
                                {
                                    xo[position_xo[1]-1-0x30][position_xo[0]-1-0x30]=2;
                                    Disp(position_xo[1]-0x30,position_xo[0]-1-0x30,1,"O");
                                    count++;
                                    break;
                                }
                            } 
                        }
                        ahead=1;
                        if (win==4)
                        break;
                        win=win_xo();
                        if (win)
                        break;
                        if (count==9)
                        {
                        win=3;
                        break;
                        } 
                    }
                    for (i=0;i<3;i++)
                    {
                        for (j=0;j<3;j++)
                        xo[i][j]=0;
                    }
                    position_xo[0]=1+0x30;
                    position_xo[1]=1+0x30;
                    Ini_Lcd();
                    if (win==4)
                    break;
                    switch (win)
                    {
                    case 1:
                    Disp(1,0,8,"you lost");
                    break;
                    case 2:
                    Disp(1,0,7,"you win");
                    break;
                    case 3:
                    Disp(1,0,5,"equal");
                    break;
                    }
                    Disp(4,0,10,"任意键返回");
                    KeyIO=0xf0;
                    while (1)
        			{
        				if ((KeyIO&0xf0)!=0xf0)
                        {
        				Delay_xMs(100);
        				if((KeyIO&0xf0)!=0xf0)
        				break; 
                        }
        			}
                    break;
                    }
                }
                break;
            }

            default: break;
            }   
        }		
      	break;	 
		default: break;
		}
	}   //switch(key_1)
    }   //while(1)
}   //void main

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
	TH0=T[m][0]; 
	TL0=T[m][1];
}

void play_start(uchar (*music)[2])
{
    uchar i=0,ii=0; 
		uchar j,p=2;
    char xdata score[70][4]={0}; //score的第一个维度是tune，第二个维度是num，第三个维度是n，第四个维度是m
    char tune,num;
    TMOD=0x01; EA=1; ET0=1; 
    if (start==1)
    {
    while (1)
    {
    m=music[i][0];
    n=music[i][1];
    if(m==0x00)
	{
		TR0=0;delay(n);i++;
	} 
	else if(m==0xFF)
	{
		TR0=0;
		return;
	} 
	else
	{
		TR0=1;
		delay(n);
		i++;
	}
    }
    }
    //get score information
            while(1)
            {
            m=music[i][0];n=music[i][1];
            score[ii][3]=m;
            if (m==0||(m>=13&&m<=24))
            tune=0;
            else if (m>0&&m<13)
            tune=-1;
            else if (m>24&&m<=36)
            tune=1;
            else
            tune=2;
            score[ii][0]=tune;
            if (tune==2)
            break;
            num=m-12*tune;
            switch (num)
            {
                case 13:
                case 14:
                score[ii][1]=1; break;
                case 15:
                case 16:
                score[ii][1]=2; break;
                case 17:score[ii][1]=3; break;
                case 18:
                case 19:
                score[ii][1]=4; break;
                case 20:
                case 21:
                score[ii][1]=5; break;
                case 22:
                case 23:
                score[ii][1]=6; break;
                case 24:score[ii][1]=7; break;
                case 0:score[ii][1]=0;  break;
            }
            score[ii][2]=n;
            ii++;
            i++;
            }
        i=0;
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
				
		num=score[i][1];
        tune=score[i][0];
        n=score[i][2];
		//显示乐谱
            if (tune==2)
            {
            TR0=0;
            break;
            }
			j=i%8;
            switch (tune)
            {
                case -1:
                {
                    switch (num)
                    {
                        case 1: Disp(p,j,2,"1"); break;
                        case 2: Disp(p,j,2,"2"); break;
                        case 3: Disp(p,j,2,"3"); break;
                        case 4: Disp(p,j,2,"4"); break;
                        case 5: Disp(p,j,2,"5"); break;
                        case 6: Disp(p,j,2,"6"); break;
                        case 7: Disp(p,j,2,"7"); break;
                        
                    }
                    switch (n)
                    {
                        case 2: 
                        Write_Cmd(0x88+j);
                        Write_Data(0x00);
                        Write_Data(0x06);
                        break;
                        case 4:
                        Write_Cmd(0x88+j);
                        Write_Data(0x00);
                        Write_Data(0x04);
                        break;
                        case 8:
                        Disp(p+1,j,1,&dot_l);
                        break;
                    }
                    break;
                }
                case 0:
                {
                    switch (num)
                    {
                        case 0: Disp(p,j,2,"0"); break;
                        case 1: Disp(p,j,2,"1"); break;
                        case 2: Disp(p,j,2,"2"); break;
                        case 3: Disp(p,j,2,"3"); break;
                        case 4: Disp(p,j,2,"4"); break;
                        case 5: Disp(p,j,2,"5"); break;
                        case 6: Disp(p,j,2,"6"); break;
                        case 7: Disp(p,j,2,"7"); break;
                    }
                    switch (n)
                    {
                        case 2: 
                        Write_Cmd(0x88+j);
                        Write_Data(0x00);
                        Write_Data(0x02);
                        break;
                        case 4:
                        Write_Cmd(0x88+j);
                        Write_Data(0x00);
                        Write_Data(0x00);
                        break;
                        case 8:
                        break;
                    }
                    break;
                }
                case 1:
                {
                    switch (num)
                    {
                        case 1: Disp(p,j,2,"1"); break;
                        case 2: Disp(p,j,2,"2"); break;
                        case 3: Disp(p,j,2,"3"); break;
                        case 4: Disp(p,j,2,"4"); break;
                        case 5: Disp(p,j,2,"5"); break;
                        case 6: Disp(p,j,2,"6"); break;
                        case 7: Disp(p,j,2,"7"); break;
                    }
                    switch (n)
                    {
                        case 2: 
                        Write_Cmd(0x88+j);
                        Write_Data(0x00);
                        Write_Data(0x02);
                        Disp(p-1,j,1,&dot_h);
                        break;
                        case 4:
                        Write_Cmd(0x88+j);
                        Write_Data(0x00);
                        Write_Data(0x00);
                        Disp(p-1,j,1,&dot_h);
                        break;
                        case 8:
                        Disp(p-1,j,1,&dot_h);
                        break;
                    }
                    Disp(p-1,j,1,&dot_h);
                    break;
                }
            }

			if(j==7){
				p++;
				//if(p==4) {
                if (p==3)  {
					//p=1;
                    p=2;
					Ini_Lcd();
					Disp(4,0,8,"16：退出");
				}
			}	
	    	//排除开机显示乐谱
        if (num==0)
        {
              TR0=0;
              delay(score[i][2]);
        }	
        else 
        {
            TR0=1;
            m=score[i][3];
            delay(score[i][2]);
        }
        i++;
	}
    TR0=0;
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

unsigned char win_xo(void)
{
    if (xo[1][1]==1)
    {
    if (xo[0][0]==1&&xo[2][2]==1)
    return 1;
    if (xo[2][0]==1&&xo[0][2]==1)
    return 1;
    if (xo[0][1]==1&&xo[2][1]==1)
    return 1;
    if (xo[1][0]==1&&xo[1][2]==1)
    return 1;
    }
    if (xo[1][1]==2)
    {
    if (xo[0][0]==2&&xo[2][2]==2)
    return 2;
    if (xo[2][0]==2&&xo[0][2]==2)
    return 2;
    if (xo[0][1]==2&&xo[2][1]==2)
    return 2;
    if (xo[1][0]==2&&xo[1][2]==2)
    return 2;
    }
    if (xo[0][0]==1&&xo[0][1]==1&&xo[0][2]==1)
    return 1;
    if (xo[2][0]==1&&xo[2][1]==1&&xo[2][2]==1)
    return 1;
    if (xo[0][0]==1&&xo[1][0]==1&&xo[2][0]==1)
    return 1;
    if (xo[0][2]==1&&xo[1][2]==1&&xo[2][2]==1)
    return 1;
    if (xo[0][0]==2&&xo[0][1]==2&&xo[0][2]==2)
    return 2;
    if (xo[2][0]==2&&xo[2][1]==2&&xo[2][2]==2)
    return 2;
    if (xo[0][0]==2&&xo[1][0]==2&&xo[2][0]==2)
    return 2;
    if (xo[0][2]==2&&xo[1][2]==2&&xo[2][2]==2)
    return 2;
    return 0;
}

unsigned char win_1(unsigned char x, unsigned char y)
{
    unsigned char win;
    xo[x][y]=1;
    win=win_xo();
    xo[x][y]=0;
    return win;
}

unsigned char win_2(unsigned char x, unsigned char y)
{
    unsigned char win;
    xo[x][y]=2;
    win=win_xo();
    xo[x][y]=0;
    return win;
}