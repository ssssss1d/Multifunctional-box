#include"test.h"
#include"ev.h"
#include "menu.h"




/*
	position数组用来记录棋盘对应位置上是否落子
*/
int position[700][480];
int win_black,win_white,win;

/*
	初始化棋盘，无落子
*/
void init_local(){
    for(int i=40;i<480;i+=40){
        for(int j=40;j<700;j+=40){
            position[j][i]=0;
        }
    }
}

 
/*
	judge:判断是否胜利
	参数：无
	返回值：无
*/
void judge(){
    for(int i=40;i < 480; i+=40)
	{
		for(int j=40 ;j < 700; j+=40)
		{
			/*
				判断五子连珠的8种情况
			*/
			if(position[j][i]==1 && position[j][i+40]==1 && position[j][i+80]==1 && position[j][i+120]==1 && position[j][i+160]==1){draw_pc("over.bmp",0,0);win++;break;}
			if(position[j][i]==1 && position[j+40][i]==1 && position[j+80][i]==1 && position[j+120][i]==1 && position[j+160][i]==1){draw_pc("over.bmp",0,0);win++;break;}
			if(position[i][j]==1 && position[i+40][j]==1 && position[i+80][j]==1 && position[i+120][j]==1 && position[i+160][j]==1){draw_pc("over.bmp",0,0);win++;break;}
			if(position[i][j]==1 && position[i][j+40]==1 && position[i][j+80]==1 && position[i][j+120]==1 && position[i][j+160]==1){draw_pc("over.bmp",0,0);win++;break;}
			if(position[j][i]==2 && position[j][i+40]==2 && position[j][i+80]==2 && position[j][i+120]==2 && position[j][i+160]==2){draw_pc("over.bmp",0,0);win++;break;}
			if(position[j][i]==2 && position[j+40][i]==2 && position[j+80][i]==2 && position[j+120][i]==2 && position[j+160][i]==2){draw_pc("over.bmp",0,0);win++;break;}
			if(position[i][j]==2 && position[i+40][j]==2 && position[i+80][j]==2 && position[i+120][j]==2 && position[i+160][j]==2){draw_pc("over.bmp",0,0);win++;break;}
			if(position[j][i]==2 && position[i][j+40]==2 && position[i][j+80]==2 && position[i][j+120]==2 && position[i][j+160]==2){draw_pc("over.bmp",0,0);win++;break;}
		}
	}
 
	for(int i=40;i < 480; i+=40)
	{
		for(int j=40 ;j < 700; j+=40)
		{
			if(position[j][i]==1 && position[j+40][i+40]==1 && position[j+80][i+80]==1 && position[j+120][i+120]==1 && position[j+160][i+160]==1){draw_pc("over.bmp",0,0);win++;break;}
			if(position[j][i]==2 && position[j+40][i+40]==2 && position[j+80][i+80]==2 && position[j+120][i+120]==2 && position[j+160][i+160]==2){draw_pc("over.bmp",0,0);win++;break;}
			
		}
	}
 
	for(int i=40; i < 480; i+=40)
	{
		for(int j=40;j < 700; j+=40)
		{
			
			if(position[j][i]==1 && position[j-40][i+40]==1 && position[j-80][i+80]==1 && position[j-120][i+120]==1 && position[j-160][i+160]==1){draw_pc("over.bmp",0,0);win++;break;}
			if(position[j][i]==2 && position[j-40][i+40]==2 && position[j-80][i+80]==2 && position[j-120][i+120]==2 && position[j-160][i+160]==2){draw_pc("over.bmp",0,0);win++;break;}
		}
	}
}
/*
	画背景色
*/
void backgroud(){
    for(int y=0;y<480;y++){
        for(int x=0;x<800;x++){
            draw_point(x,y,0x8B4513);
        }
    }
}
/*
	画棋盘的线
*/
void lineation(){
for(int i=0;i < 480; i++)
	{
		if(i%40 == 0)//隔40像素点画行线
		{
			for(int j=0; j<680; j++)
			{
				draw_point(j,i,0x0);
			}
		}
	}
	for(int j=0 ;j < 700; j++)
	{
		if(j%40 == 0)//隔40像素点画列线
		{
			for(int i=0; i<480; i++)
			{
				draw_point(j,i,0x0);
			}
		}
	}
 
	for(int j=0; j<=800; j++)
	{
		for(int i=0; i<=480; i++)
		{
			if((j - 160)*(j - 160) + (i - 80)*(i - 80) <= 18 || (j - 160)*(j - 160) + (i - 400)*(i - 400) <= 18|| (j - 520)*(j - 520) + (i - 80)*(i - 80) <= 18|| (j - 520)*(j - 520) + (i - 400)*(i - 400) <= 18)//棋盘上的小黑点（用圆的公式）
			{
				draw_point(j,i,0x0);
			}
		}
	}

}

/*
	black:落子黑棋
	参数：
		@a:横坐标
		@b:纵坐标
	返回值：无
*/
void black(int a, int b)
{
	for(int j=0; j<=800; j++)
	{
		for(int i=0; i<=480; i++)
		{
			if((j - a)*(j - a) + (i - b)*(i - b) <= 18*18)
			{
				draw_point(j,i,0x0);
			}
		}
	}
}
 
/*
	white:落子白棋
	参数：
		@a:横坐标
		@b:纵坐标
	返回值：无
*/
void white(int a, int b)
{
	for(int j=0; j<=800; j++)
	{
		for(int i=0; i<=480; i++)
		{
			if((j - a)*(j - a) + (i - b)*(i - b) <= 18*18)
			{
				draw_point(j,i,0xffffff);
			}
		}
	}
}


int get_ev(int *x,int *y){
    int fd=open("/dev/input/event0",O_RDWR);
    if(-1==fd){
        perror("open error");
        return -1;
    }
    /*
		x1：记录横坐标
		y1：记录纵坐标
		num：标记五子棋进行到哪一步了
		flag：决定是黑棋下还是白起下（1为白棋下，0为黑棋下）
	*/
	
    struct input_event ev;
    int x1,y1,num=0,flag=0;

    while(1){
        read(fd,&ev,sizeof(ev));
        printf("ev.type:%d ev.code:%d ev.value:%d\n",ev.type,ev.code,ev.value);

        if(ev.type==EV_ABS){
            if(ev.code==0)// REL_X==0
                x1=ev.value*800/1024;
            else  //REL_Y==1
                y1=ev.value*800/1024;
        }
        
        if(ev.type==EV_KEY && ev.code==330 && ev.value==1){// 330==0x14a==BTN_TOUCH  ，触摸事件，1表示点击触摸屏
            *x=x1;
            *y=y1;
        }
        
        if(ev.type==EV_KEY && ev.code==330 && ev.value==0){ //触摸事件，0表示离开触摸屏
            if(*x==x1 && *y==y1) //开始位置与离开位置相同，构成点击事件
            {
				if(x1>700 && x1<800 && y1>0 && y1<100){
					lcd_menu(); 
					break;
				}
				if(x1>700 && x1<800 && y1>100 && y1<200){ //重新开始游戏
					num=3;
					win=0;
					init_local();
					flag=0;
					break;
				}
                if(0 == num)//如果还没进入过游戏，第一步，进入游戏阶段
				{
					backgroud();
					lineation();
					draw_pc("exit.bmp",700,0);//退出按钮
					draw_pc("reload1.bmp",700,100);//重新开始按钮
					sleep(1);
					draw_pc("s.bmp",700,200);
					num++;//进入了下一步
				}
				else if(1 == num)//第二步，下棋阶段
				{
					for(int i=40;i < 480; i+=40)
					{
						for(int j=40 ;j < 700; j+=40)
						{
							if((x1 - j) * (x1 - j) + (y1 - i) * (y1 - i) <= 18*18 && flag == 0 && position[j][i]==0)//黑棋2
							{
								draw_pc("s1.bmp",700,200);//白方走棋
								draw_pc("exit.bmp",700,0);//退出按钮
								draw_pc("reload1.bmp",700,100);//重新开始按钮
								black(j, i);
								flag += 1;
								position[j][i]=2;
								judge();
								
							}
							else if((x1 - j) * (x1 - j) + (y1 - i) * (y1 - i) <= 18*18 && flag == 1 && position[j][i]==0)//白棋1
							{
								draw_pc("s.bmp",700,200);//黑方走棋
								draw_pc("exit.bmp",700,0);//退出按钮
								draw_pc("reload1.bmp",700,100);//重新开始按钮
								white(j, i);
								flag -= 1;
								position[j][i]=1;
								judge();
							}
							
						}
						if(win != 0)//有一方胜利
						{
							num++;//进入下一阶段
							win=0;
							init_local();
                           // backgroud();
							flag=0;
							break;
						}
					}
				}
                else if(2==num){
                    draw_pc("reload.bmp",0,0);
					draw_pc("exit.bmp",700,0);//退出按钮
                    num++;
                }
                else if(3==num){
                    draw_pc("bigan.bmp",0,0);
                    num=0;
                }
            }
        }
    }

}

