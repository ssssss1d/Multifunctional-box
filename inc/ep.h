#ifndef _EP_H

#define _EP_H

#include <pthread.h>
enum DIREC
{
    ERROR=0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    OTHER,
    exit3,
    AUTO
};
int  get_ep_point();
void ep_fun();
void p_auto();
void ep_func();
void* do_work2();
void* do_work1();
#endif