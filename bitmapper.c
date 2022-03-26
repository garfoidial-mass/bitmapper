#define SDL_MAIN_HANDLED
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "layouts.h"
#include "ut/uthash.h"

//in load_font, create hash map of associated characters and their bitmap characters (really just a rect of the base font texture and a color tint)

typedef struct _color{
    uint8_t r,g,b;
} COLOR;

typedef struct _bitmap_char{
    char associate; //associated character
    COLOR color;
    SDL_Rect rect;
    UT_hash_handle hh;
} BMCHAR;

typedef struct _font{
    int cw,ch; // char width and height
    char* charassociation; //a string with all of the characters in the font's associated chars
    BMCHAR* chars;
    SDL_Texture* image;
} FONT;

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

int init_window(int x, int y, int width, int height, COLOR clearcolor , const char* title, WINDOW* window){
    window->quit = 0;
    window->numlayers = 1;
    window->width = width;
    window->height = height;
    window->layers = malloc(sizeof(LAYER));

    int rendererflags = SDL_RENDERER_ACCELERATED;
    int windowflags = 0;

    int error = 0;
    error = SDL_Init(SDL_INIT_VIDEO);

    if(error < 0){
        return error;
    }

    window->window = SDL_CreateWindow(title,x,y,width,height,windowflags);

    if(!window->window)
    {
        return -1;
    }
    error = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    if(error != 1){
        return -3;
    }

    window->renderer = SDL_CreateRenderer(window->window,-1,rendererflags);

    SDL_SetRenderDrawColor(window->renderer,clearcolor.r,clearcolor.g,clearcolor.b,255);

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

int process_window(WINDOW* window)
{
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

    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);
    SDL_Delay(16);
}

LAYER* add_layer(int x, int y,int w, int h, FONT* font, WINDOW* window)
{   
    window->numlayers += 1;
    window->layers = realloc(window->layers,sizeof(LAYER) * window->numlayers);
    window->layers[window->numlayers-1] = (LAYER){ font,x,y,w,h,0,0,NULL };

    return &(window->layers[window->numlayers-1]);
}

void bm_putchar(char c, int x, int y, LAYER* layer, WINDOW* window)
{
    BMCHAR* bmc;
    SDL_Rect rect;
    SDL_Rect dstRect;
    HASH_FIND_INT(layer->font->chars,&c,bmc);
    rect = bmc->rect;
    dstRect = (SDL_Rect){x*layer->font->cw,y*layer->font->ch,layer->font->cw,layer->font->ch};
    SDL_RenderCopy(window->renderer,layer->font->image,&rect,&dstRect);
}

int load_font(int w, int h, const char* layout, const char* filepath, FONT* font, WINDOW* window){
    *font = (FONT){w,h,layout};
    font->chars = NULL;
    SDL_Surface* imagesurface = IMG_Load(filepath);
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

    int charsinfont = strlen(layout);
    int texw, texh;
    SDL_QueryTexture(font->image,NULL,NULL,&texw,&texh);

    int x = 0,y = 0;
    for(int currentchar = 0; currentchar < charsinfont; currentchar+=1)
    {
        BMCHAR* bmrep; 
        bmrep = malloc(sizeof(BMCHAR));
        bmrep->associate = font->charassociation[currentchar];
        bmrep->rect = (SDL_Rect){x,y,font->cw,font->ch};
        bmrep->color = (COLOR){255,255,255};
        HASH_ADD_INT(font->chars,associate,bmrep);

        if(x < texw - font->cw)
        {
            x += font->cw;
        }
        else
        {
            x = 0;
            y += font->ch;
        }
    }

    return 0;
}

void destroy_font(FONT* font){
    SDL_DestroyTexture(font->image);
    BMCHAR* c, *tmp;
    HASH_ITER(hh, font->chars,c,tmp){
        HASH_DEL(font->chars,c);
        free(c);
    }
}


int main(int argc, char* argv[])
{
    FONT testfont;
    WINDOW window;

    printf("started\n");

    printf("%i\n",init_window(200,200,320,200,(COLOR){255,255,255},"test window",&window));
    printf("window created\n");
    
    printf("%i\n", load_font(16,16,BM_LAYOUT_DEFAULT,"./Fonts/16X16-FA.png",&testfont,&window));

    printf("font loaded\n");

    LAYER* testlayer = add_layer(0,0,50,50,&testfont,&window);

    while(!window.quit)
    {
        bm_putchar('A',1,1,testlayer,&window);
        process_window(&window);
    }

    printf("loop ended\n");
    destroy_font(&testfont);
    cleanup_window(&window);

    return 0;
}