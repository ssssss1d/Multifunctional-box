#ifndef _MENU_H

#define _MENU_H

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/input.h>
 #include <stdlib.h>

#include"ev.h"
#include"test.h"
#include"ep.h"
#include "music.h"
static struct point{
    int x;
    int y;
}p;
struct point get_point();
/*功能：菜单界面选择功能*/
int lcd_choice();
/*
    功能：启动菜单
*/
int lcd_menu();
void gomoku();
void underdevelopment();
#endif