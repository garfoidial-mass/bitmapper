#include <stdint.h>
#include <stdio.h>

#include "bitmapper/bitmapper.h"

//MAKE THE LAYERS TRANSPARENT!!! MAKE THE SDL_IMAGE STUFF WORK (BMP SUCK!)

int main(int argc, char* argv[])
{

    WINDOW* window;

    printf("started\n");

    window = bm_init_window(200,200,640,480,(COLOR){0,0,0},"test window");
    printf("window created\n");
    
    FONT* testfont = bm_load_font(32,32,BM_LAYOUT_DEFAULT, "./Fonts/32X32-FD.png", window);
    if(testfont == NULL)
    {
        printf("testfont not loaded correctly\n");
    }

    FONT* funnyfont = bm_load_font(32,32,BM_LAYOUT_DEFAULT,"./Fonts/32X32-FG.png", window);
    if(funnyfont == NULL)
    {
        printf("testfont not loaded correctly\n");
    }

    printf("font loading done\n");

    LAYER* testlayer = bm_add_layer(0,0,20,20,testfont,window);
    if(testlayer == NULL)
    {
        printf("testlayer null\n");
    }
    LAYER* funnylayer = bm_add_layer(0,0,20,20,funnyfont,window);
    if(testlayer == NULL)
    {
        printf("funnylayer null\n");
    }

    printf("added layers\n");

    bm_print("HELLO",1,1,testlayer,window);
    bm_print("WORLD",3,3,funnylayer,window);



    while(bm_open_window(window))
    {
        bm_process_window(window);
        bm_clear_window(window);

        if(bm_getkey(BM_KEY_LEFT,window))
        {
            testlayer->x -= 5;
        }
        if(bm_getkey(BM_KEY_RIGHT,window))
        {
            testlayer->x += 5;
        }
        if(bm_getkey(BM_KEY_UP,window))
        {
            testlayer->y -= 5;
        }
        if(bm_getkey(BM_KEY_DOWN,window))
        {
            testlayer->y += 5;
        }

        if(bm_getkey(BM_KEY_A,window))
        {
            funnylayer->x -= 5;
        }
        if(bm_getkey(BM_KEY_D,window))
        {
            funnylayer->x += 5;
        }
        if(bm_getkey(BM_KEY_W,window))
        {
            funnylayer->y -= 5;
        }
        if(bm_getkey(BM_KEY_S,window))
        {
            funnylayer->y += 5;
        }

        if(bm_getkey(BM_KEY_TAB,window))
        {
            bm_tint_layer((COLOR){255,0,0,255},testlayer,window);
        }

        if(bm_getkey(BM_KEY_LSHIFT,window))
        {
            bm_tint_layer((COLOR){255,255,255,255},testlayer,window);
        }
        
        bm_render_window(window);
    }

    printf("loop ended\n");
    bm_destroy_font(testfont);
    bm_destroy_font(funnyfont);
    bm_cleanup_window(window);

    return 0;
}