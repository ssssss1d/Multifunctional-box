#include"test.h"
#include"ev.h"
#include"menu.h"

int main(){
    int x,y;
    init_lcd();
     // clear_lcd(0xff0000);
    //draw_pc("bigan.bmp",0,0);
   // init_local();
   //get_ev(&x,&y);
    lcd_menu();
    return 0;
}