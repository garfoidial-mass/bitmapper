#define SDL_MAIN_HANDLED
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "layouts.h"
#include "ut/uthash.h"


typedef struct _color{
    uint8_t r,g,b;
} COLOR;

typedef struct _font{
    int cw,ch; // char width and height
    char* charassociation; //a string with all of the characters in the font's associated chars
    SDL_Texture* image;
} FONT;

typedef struct _bitmap_char{
    FONT *font;
    COLOR color;
    int index;
} BMCHAR;

typedef struct _layer{
    FONT *font;
    int x,y; //x and y offset in chars
    int w,h; // width and height in chars
    int scrolloffsetx, scrolloffsety; //smooth scrolling offset (pixels)
    BMCHAR* chars; // array of all the characters in the layer
} LAYER;


typedef struct _bmpfontlib_window{
    int numlayers;
    LAYER* layers;
    int width, height; // height and width in pixels
    SDL_Renderer* renderer;
    SDL_Window* window;
    uint8_t quit;
} WINDOW;

int init_window(int x, int y, int width, int height, const char* title, FONT *font, WINDOW* window){
    window->quit = 0;
    window->numlayers = 1;
    window->width = width;
    window->height = height;
    window->layers = malloc(sizeof(LAYER));
    window->layers[0].font = font;
    window->layers[0].w = width;
    window ->layers[0].h = height;

    int rendererflags = SDL_RENDERER_ACCELERATED;
    int windowflags = 0;

    int error = 0;
    error = SDL_Init(SDL_INIT_VIDEO);

    if(error < 0){
        return error;
    }

    window->window = SDL_CreateWindow(title,x,y,width*font->cw,height*font->ch,windowflags);

    if(!window->window)
    {
        return -1;
    }
    error = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    if(error != 1){
        return -3;
    }

    window->renderer = SDL_CreateRenderer(window->window,-1,rendererflags);

    if(!window->renderer)
    {
        return -2;
    }

    return 0;
}

int cleanup_window(WINDOW* window)
{
    printf("cleaning up\n");
    free(window->layers);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
}

int process_window(WINDOW* window){
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    SDL_Quit();
                    window->quit = 1;
                    break;
                
                default:
                    break;
                }
            break;
            default:
            break;
        }
    }

    SDL_SetRenderDrawColor(window->renderer,255,255,255,255);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);
    SDL_Delay(16);
}

int load_font(int w, int h, const char* layout, const char* filepath, FONT* font, WINDOW* window){
    *font = (FONT){w,h,layout};
    SDL_Surface* imagesurface = IMG_LOAD(filepath);
    if(!imagesurface)
    {
        return -1;
    }
    font->image = SDL_CreateTextureFromSurface(window->renderer, imagesurface);
    if(!font->image)
    {
        return -2;
    }
    SDL_FreeSurface(imagesurface);
    return 0;
}

void destroy_font(FONT* font){
    SDL_DestroyTexture(font->image);
}


int main(int argc, char* argv[])
{
    FONT defaultfont;
    WINDOW window;

    printf("%i\n",init_window(200,200,50,50,"test window",&defaultfont,&window));
    printf("%i\n", load_font(16,16,BM_LAYOUT_DEFAULT,"./Fonts/16X16-FA.png",&defaultfont,&window));

    while(!window.quit)
    {
        process_window(&window);
    }
    printf("loop ended\n");
    destroy_font(&defaultfont);
    cleanup_window(&window);

    return 0;
}