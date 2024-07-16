#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include<stdlib.h>
#include <linux/input.h>
#include <pthread.h>
#include "test.h"
#include "ep.h"
#include "menu.h"
const char *ep[]={"8.bmp","1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp"};
 pthread_t tid1,tid2;
int lx,ly,num=0;
/*功能：获取电子相册功能的点击坐标*/
int  get_ep_point()
{

    int  fd=open("/dev/input/event0",O_RDWR);
    if(-1==fd){
        perror("open error");
        return -1;
    }

    struct input_event ev;
    int sx=-1,sy=-1;
    int ex,ey;
    while(1)
    {
        read(fd,&ev,sizeof(ev));
        printf("ev.type:%d ev.code:%d ev.value:%d\n",ev.type,ev.code,ev.value);

        //触摸事件
        if(ev.type==EV_ABS && ev.code==0)
        {
            if(-1==sx)
                sx=ev.value*800/1024;
            ex=ev.value*800/1024;
        }
        else if(ev.type==EV_ABS && ev.code==1)
        {
            if(-1==sy)
                sy=ev.value*480/600;
            ey=ev.value*480/600;
        }
        if(ev.type==EV_KEY && ev.code == 330 && ev.value == 0)//手松开，跳出循环
            break;
    }
   // return exit3;
  //  printf("sx = %d sy = %d ex = %d ey = %d \n",sx,sy,ex,ey);
    if(sx>700 && sx<800 && sy>0 && sy<100 && sx==ex &&sy == ey)
   {
    // printf("sx = %d sy = %d ex = %d ey = %d \n",sx,sy,ex,ey);
        return exit3;
   }

     if(sx>700 && sx<800 && sy>100 && sy<200 && sx==ex &&sy == ey)
   {
    // printf("sx = %d sy = %d ex = %d ey = %d \n",sx,sy,ex,ey);
        lx=sx;
        ly=sy;
        return AUTO;
   }

    int dx=ex-sx;
    int dy=ey-sy;
    if(abs(dx)>abs(dy))
    {
        printf("sx = %d sy = %d ex = %d ey = %d \n",sx,sy,ex,ey);
        if(dx>20)
        return RIGHT;//右
        if(dx<-20)
        return LEFT;//左
    }
    else if(abs(dx)<abs(dy))
    {
        printf("sx = %d sy = %d ex = %d ey = %d \n",sx,sy,ex,ey);
        if(dy>20)
        return DOWN;//下
        if(dy<-20)
        return UP;//上
    }
    else
    {
        printf("你已误触！");
        return OTHER;
    }
    close(fd);

}
/*功能:获取点击事件杀死word1、tid1*/
void* do_work2(){
    while(1){
        num=0;
        struct point pt= get_point();
        int sx=pt.x;
        int sy=pt.y;
      //  printf("word2.num==%d\n",num);
       if(sx>700 && sx<800 && sy>0 && sy<100 )
            {
               // num=1;
                //sx=sy=0;
                pthread_cancel(tid1);
                lcd_menu();
                break;
            }
    }
    return NULL;
}
/*功能：循环播放相册*/
void* do_work1(){
      int i=0;
      while(1){
    //   if(num==1)//此时线程2结束，杀死线程1，返回菜单
    //   {
    //     num=0;
    //     lcd_menu();
    //     break;
    //   }
        for(int i=1;i<7;i++)
        {
            draw_pc(ep[i],0,0);
            draw_pc("exit3.bmp",700,0);
           // draw_pc("auto.bmp",700,100);
            sleep(1);
        }
        
        if(7==i)
            i=0;    
    }

        return NULL;
}


/*功能：多线程创建*/
void p_auto(){
   
    pthread_create(&tid2,NULL,do_work2,NULL);
    pthread_create(&tid1,NULL,do_work1,NULL);
         pthread_join(tid2,NULL);
    pthread_join(tid1,NULL);

}

void ep_func(){
    return ;
}
 /*
    功能：调用我的电子相册
 */
void ep_fun(){
    init_lcd();
    int a=0,i=0;
    draw_pc(ep[i],0,0);
    draw_pc("exit3.bmp",700,0);
    draw_pc("auto.bmp",700,100);
    while(1){
    a=get_ep_point();
    printf("a=%d\n",a);

        if(exit3==a)
        {
             lcd_menu();
             break;
        }
        else if(AUTO == a){
           p_auto();
        }
        else if(OTHER == a)
        {
            draw_pc(ep[i],0,0);
            draw_pc("exit3.bmp",700,0);
            draw_pc("auto.bmp",700,100);
        }
        else if(RIGHT ==a || DOWN==a){
            if(6==i)
            i=0;
            else
            i++;

            printf("i = %d\n",i);
            draw_pc(ep[i],0,0);
            draw_pc("exit3.bmp",700,0);
            draw_pc("auto.bmp",700,100);
        }

        else{
            if(0==i)
            i=6;
            else
            i--;
            printf("i = %d\n",i);
            draw_pc(ep[i],0,0);
            draw_pc("exit3.bmp",700,0);
            draw_pc("auto.bmp",700,100);
        }
    }
   
    destory_lcd();
}
        