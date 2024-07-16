#ifndef _EV_H

#define _EV_H

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <unistd.h>
#include <stdio.h>
#include<linux/input.h>
#include"test.h"

 
/*
	get_ev:打开触摸屏，获取屏幕信息
	参数：
		@x:记录横坐标
		@y:记录纵坐标
	返回值：
		-1：打开屏幕失败
*/
int get_ev(int *x,int *y);
void init_local();
void judge();
void backgroud();
void lineation();
void black(int a, int b);
void white(int a, int b);
void draw_point(int x,int y,int color);
#endif