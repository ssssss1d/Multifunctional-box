#ifndef _TEST_H

#define _TEST_H

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <unistd.h>
#include <stdio.h>
static int lcd_fd;
static int  lcd_width;
static int lcd_height;
static int * lcd_ptr;
static int lcd_pixel;

/*
    功能：初始化屏幕(打开，映射)，成功之后才能在屏幕上做显示操作
    返回值：
        失败返回-1，成功返回0
*/
int init_lcd();
/*
    功能：把整块屏幕显示为 color
*/
void clear_lcd(int color);
/*
    功能：在屏幕上指定位置显示一个点
    参数：
        x,y 指定像素点的坐标位置
        color 指定像素点的颜色
*/
void draw_point(int x,int y,int color);
/*
    功能：在屏幕上打开图片
    
*/
int draw_pc(const char * path,int x0,int y0);



/*
    功能：释放屏幕资源
*/
void destory_lcd();
#endif