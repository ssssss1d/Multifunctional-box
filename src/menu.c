#include"menu.h"
/*功能：获取点击坐标*/
struct point get_point()
{   
    struct point p;
    int fd = open("/dev/input/event0",O_RDONLY);
    if(-1 == fd)
    {
        perror("");
        p.x = p.y = -1;
        return p;
    }

    struct input_event ev;
    
    while(1)//点击/滑动屏幕时，并不是只有一个输入事件发生，更加不是只有一个 结构体数据，所以我们需要循环读取
    {
        read(fd,&ev,sizeof(ev));
        printf("type:%d,code:%d,value:%d\n",ev.type,ev.code,ev.value);
        if(ev.type==EV_ABS&&ev.code==REL_X)
            p.x = ev.value*800/1024;
        if(ev.type==EV_ABS&&ev.code==REL_Y)
            p.y = ev.value*480/600;
        if(ev.type==EV_KEY&&ev.code==BTN_TOUCH&&ev.value==0)//手指松开，跳出循环
            break;
    }

    close(fd);
    return p;
}

int lcd_choice(){
    int choices = 0;
    draw_pc("menu.bmp", 0,0);//显示菜单
    struct point pp;
    pp=get_point();
    int sx=pp.x;//起始点横纵坐标
    int sy=pp.y;
   // return 1;
   printf("sx=%d sy=%d\n",sx,sy);
    if(sx > 0 && sx < 390 && sy > 130 && sy < 300)    return 1;
    else if(sx > 390 && sx < 800 && sy > 130 && sy < 300)    return 2;
    else if(sx > 0 && sx < 390 && sy > 300 && sy < 480)    return 3;
    else if(sx > 390 && sx < 800 && sy > 300 && sy < 480)    return 4;
    else    return 0;
}
/*
    功能：启动五子棋程序
*/
void gomoku(){
    int x,y;
    draw_pc("bigan.bmp",0,0);
    draw_pc("exit3.bmp",700,0);
   init_local();
   get_ev(&x,&y);
}
/*功能：显示未开发的功能模块*/
void underdevelopment(){
    draw_pc("undev.bmp",0,0);
    draw_pc("exit3.bmp",700,0);
  while(1){
     struct point p =get_point();
   int x=p.x;
   int y=p.y;
    if(x>700 && x<800 && y>0 &&y<100)//点击退出按钮
    {
        lcd_menu();
        break;
    }
  }
    return ;
}
void func()
{
    while (1)
    {
        /* code */
    }
    
}
/*
    功能：显示菜单
*/
int lcd_menu(){
    draw_pc("menu.bmp", 0,0);//显示菜单
    int chioce = lcd_choice();

    do{
        printf("%d\n",chioce);
        switch(chioce){
            case 0:
            {
              //  underdevelopment();
               //  clear_lcd(0xffff00);
          //  perror("open failed!");
          lcd_menu();
                break;
            }
            case 1:
           {
            gomoku();
             break;  //进入五子棋游戏
           }
            case 2:
            {
              //  clear_lcd(0xff0000);
               underdevelopment();
                break;
            }
            case 3:
            {
                ep_fun();
             //   perror("ep open failed!");
                break;
            }
            case 4:
            {
          // underdevelopment();
         // system("killall -9 madplay");
         // printf("准备播放！！！\n");
                fun_music();
         //   func();
                break;
            }
        }
    }while(1);
    return 0;
}

