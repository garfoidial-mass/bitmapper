#include "bitmapper/bitmapper.h"

int main(int argc, char* argv[])
{
    WINDOW* window = window = bm_init_window(200,200,640,480,(COLOR){0,0,0,255},"test window");

    FONT* font = bm_load_font(32,32,BM_LAYOUT_DEFAULT, "./fonts/32X32-FD.png", window);
    LAYER* layer = bm_add_layer(0,0,20,20,font,window);

    bm_print("HELLO WORLD",1,1,layer,window);

    while(bm_open_window(window))
    {
        bm_process_window(window);
        bm_clear_window(window);
        bm_render_window(window);
    }
    
    //free memory used for font
    bm_destroy_font(font);
    //free memory and close down the window
    bm_cleanup_window(window);
    
    //yeah
    return 0;
}