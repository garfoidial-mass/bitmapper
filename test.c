#define SDL_MAIN_HANDLED
#include <stdint.h>
#include <stdio.h>

#include "bitmapper.h"

//MAKE IT SO PRINTING PRINTS TO THE LAYER'S BUFFER, NOT JUST TO THE SCREEN
//ALSO ADD FUNCTIONS RELATING TO LAYER BUFFER
//MAKE bm_render FUNCTION THAT RENDERS ALL OF A WINDOW'S LAYERS

int main(int argc, char* argv[])
{
    WINDOW window;

    printf("started\n");

    printf("%i\n",bm_init_window(200,200,800,800,(COLOR){0,0,0},"test window",&window));
    printf("window created\n");
    
    FONT testfont = bm_load_font(16,16,BM_LAYOUT_DEFAULT, "./Fonts/16X16-FA.bmp", &window);

    FONT funnyfont = bm_load_font(32,32,BM_LAYOUT_DEFAULT,"./Fonts/32X32-FG.bmp", &window);

    printf("font loaded\n");

    LAYER* testlayer = bm_add_layer(0,0,50,50,&testfont,&window);
    LAYER* funnylayer = bm_add_layer(0,0,20,20,&funnyfont,&window);

    bm_print("EPIC BALLS!",1,1,testlayer,&window);
    bm_print("(AND KNUCKLES)",3,3,funnylayer,&window);


    while(!window.quit)
    {
        bm_process_window(&window);
        bm_window_clear(&window);

        if(bm_getkey(BM_KEY_LEFT,&window))
        {
            testlayer->x -= 5;
        }
        if(bm_getkey(BM_KEY_RIGHT,&window))
        {
            testlayer->x += 5;
        }
        if(bm_getkey(BM_KEY_UP,&window))
        {
            testlayer->y -= 5;
        }
        if(bm_getkey(BM_KEY_DOWN,&window))
        {
            testlayer->y += 5;
        }

        if(bm_getkey(BM_KEY_A,&window))
        {
            funnylayer->x -= 5;
        }
        if(bm_getkey(BM_KEY_D,&window))
        {
            funnylayer->x += 5;
        }
        if(bm_getkey(BM_KEY_W,&window))
        {
            funnylayer->y -= 5;
        }
        if(bm_getkey(BM_KEY_S,&window))
        {
            funnylayer->y += 5;
        }

        if(bm_getkey(BM_KEY_RETURN,&window))
        {
            bm_clear_layer(funnylayer);
        }
        
        bm_render_window(&window);
    }

    printf("loop ended\n");
    bm_destroy_font(&testfont);
    bm_cleanup_window(&window);

    return 0;
}