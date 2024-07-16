#ifndef _MUSIC_H

#define _MUSIC_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <linux/input.h>	
#include <sys/mman.h>
#include <pthread.h>
#include "menu.h"
#include "test.h"
int fd_fifo;//管道文件
/*功能：调用音乐播放*/
void fun_music(); 
/*功能：创建管道文件
   失败返回-1；
   成功返回0；
   */
//int c_fifo();
/*功能：传输管道文件控制播放*/
void send_message(char *message);
/*获取点击坐标*/
void *m_work1();
void* m_work2();
#endif