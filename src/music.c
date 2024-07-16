#include "music.h"

char* mp3path[]={"0.mp3","1.mp3","2.mp3","3.mp3"};
#define MAX  1000

pthread_t tid1;
pthread_t tid2;





void send_message(char *message){
   if(access("/tmp/myfifo",F_OK) == -1)
	{
		if(mkfifo("/tmp/myfifo",0666) < 0)
		{
			perror("mkfifo erro!\n");
			//exit(1);
		}
	}

    int fd = open("/tmp/myfifo", O_WRONLY);
        if (fd == -1) 
    perror("open failed");

    printf("初始化fifo success!");
    printf("%s",message);
    write(fd,message,strlen(message));
}


void* m_work1(){
    
}
int ans;
void* m_work2(){
    system("killall -9 madplay");
   // while(1){
    //char m[MAX];
    //sprintf(m,"madplay %s &",mp3path);
    //system(m);
    system("madplay *.mp3 -r -v &");
    ans=0;
    printf("start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    draw_pc("music.bmp",0,0);
    draw_pc("recede.bmp",100,380);
    draw_pc("vs.bmp",200,380);
    draw_pc("start.bmp",300,380);
    draw_pc("va.bmp",500,380);
    draw_pc("advance.bmp",600,380);
    draw_pc("exit3.bmp",700,0);
   // }
}



void fun_music(){

    // int chioce,i=0;
    // static int j=0;
    draw_pc("music.bmp",0,0);
    system("killall -9 madplay");
   // system("killall -9 madplay");
    // printf("i==%d\n",i++);
    // printf("j==%d\n",j++);
    // printf("准备播放！！！\n");
   //  system("madplay ./0.mp3 &");
    // printf("开始播放！！！！\n");
    // pthread_create(&tid1,NULL,m_work1,NULL);
     pthread_create(&tid2,NULL,m_work2,NULL);
    // pthread_join(tid1,NULL);
     //  pthread_join(tid2,NULL);
    int flag=1;
    while(1)
    {
    struct point pp;
    pp=get_point();
    int sx=pp.x;//起始点横纵坐标
    int sy=pp.y;
    if(sx >700 && sx<800 &&sy>0&&sy<100)
         {
        pthread_cancel(tid2);
        system("killall -9 madplay");
        lcd_menu();
       
        break;
         }
    if(sx>300 && sx<500 && sy>380 &&sy<480){
        if(flag==1){
            system("killall -STOP madplay &");
            draw_pc("suspend.bmp",300,380);
            flag=0;
        }
        else{
          system("killall -CONT madplay &");
            flag=1;
            draw_pc("start.bmp",300,380);
        }
    }
    if(sx > 500 && sx < 600 && sy > 380 && sy < 480)//音量＋
   // send_message("volume +10");
    if(sx > 200 && sx < 300 && sy > 380 && sy < 480)//音量-
   // send_message("volume -10");
   system("volume -10");
    if(sx > 600 && sx < 700 && sy > 380 && sy < 480)//前进
    {
        system("killall -9 madplay");
        ans++;
        ans%=sizeof(mp3path)/sizeof(mp3path[0]);
       // system("madplay *.mp3 -r -v &");
       char m[MAX];
       sprintf(m,"madplay %s -r -v &",mp3path[ans]);
         system(m);
    }
    // send_message("seek +10");
    if(sx > 100 && sx < 200 && sy > 380 && sy < 480)//后退
    {
        system("killall -9 madplay");
        ans--;
        if(ans<0)
        ans=sizeof(mp3path)/sizeof(mp3path[0])-1;
        ans%=sizeof(mp3path)/sizeof(mp3path[0]);
       // system("madplay *.mp3 -r -v &");
       char m[MAX];
       sprintf(m,"madplay %s -r -v &",mp3path[ans]);
         system(m);
    }
   // send_message("seek -10");
    }
}