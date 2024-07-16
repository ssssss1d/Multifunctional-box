
#include "test.h"





int init_lcd(){
    //1打开
    int lcd_fd = open("/dev/fb0",O_RDWR);
    if(-1 == lcd_fd)
    {
        perror("");
        return -1;
    }
    //2获取屏幕信息
    struct fb_var_screeninfo info;
   	ioctl(lcd_fd,FBIOGET_VSCREENINFO,&info);
   	//如果 ioctl成功了，那么屏幕相关信息就保存在 info中了
   	 lcd_width = info.xres;
   	 lcd_height = info.yres;
   	 lcd_pixel = info.bits_per_pixel/8;//lcd_pixel表示一个像素点占多少字节

  
    lcd_ptr = mmap(NULL,lcd_width*lcd_height*lcd_pixel,PROT_READ | PROT_WRITE,
     		MAP_SHARED,lcd_fd,0);

            return 1;

}

void draw_point(int x,int y,int color){
    if(x>=0&&x<lcd_width&&y>=0&&y<lcd_height)
        *(lcd_ptr+lcd_width*y+x) = color;
        
}

void clear_lcd(int color){
    for(int y=0;y<lcd_height;y++){
        for(int x=0;x<lcd_width;x++){
            draw_point(x,y,color);
        }
    }
}

int draw_pc(const char * path,int x0,int y0){
    
     int fd=open(path,O_RDONLY);
    if(-1==fd){
        perror("");
        return -1;
    }
    char c[2];
    read(fd,c,2);
    
    if(c[0] != 'B' || c[1] != 'M')
    {
        printf("该文件不是BMP格式\n");
        close(fd);
        return -1;
    }
    int w,h;
    lseek(fd,0x12,SEEK_SET);
    read(fd,&w,4);
    read(fd,&h,4);
    unsigned char bgr[3];
    int laizi=w%4;
    lseek(fd,54,SEEK_SET);;
    
    for(int y=h-1;y>=0;y--){
        for(int x=0;x<w;x++){
            read(fd,bgr,3);
            int color=bgr[0] | bgr[1]<<8 | bgr[2]<<16;
            draw_point(x+x0,y+y0,color);
        }
        lseek(fd,laizi,SEEK_CUR);
    }
    close(fd);
    return 0;
}

void destory_lcd(){
    munmap(lcd_ptr,lcd_height*lcd_width*lcd_pixel);
     close(lcd_fd);
}