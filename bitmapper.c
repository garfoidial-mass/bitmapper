#include "bitmapper.h"

//Window functions

int bm_init_window(int x, int y, int width, int height, COLOR clearcolor , const char* title, WINDOW* window)
{
    window->quit = 0;
    window->numlayers = 1;
    window->width = width;
    window->height = height;
    window->layers = (LAYER*)malloc(sizeof(LAYER));
    window->keys = calloc(550,sizeof(uint8_t));

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

int bm_cleanup_window(WINDOW* window)
{
    printf("cleaning up\n");
    free(window->layers);
    free(window->keys);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
}

int bm_process_window(WINDOW* window)
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

            case SDL_KEYDOWN:
                window->keys = (uint8_t*)SDL_GetKeyboardState(NULL);
            break;
            case SDL_KEYUP:
                window->keys = (uint8_t*)SDL_GetKeyboardState(NULL);
            break;

            default:
            break;
        }
    }
    SDL_RenderPresent(window->renderer);
    SDL_Delay(16);
}

void bm_render_window(WINDOW* window)
{
    for(int x = 0; x < window->numlayers; x++)
    {
        bm_render_layer(&(window->layers[x]),window);
    }
}

void bm_window_clear(WINDOW* window)
{
    SDL_RenderClear(window->renderer);
}

int bm_getkey(KEY key, WINDOW* window)
{
    return window->keys[key];
}

//Layer functions

LAYER* bm_add_layer(int x, int y,int w, int h, FONT* font, WINDOW* window)
{   
    window->numlayers += 1;
    window->layers = realloc(window->layers,sizeof(LAYER) * window->numlayers);
    window->layers[window->numlayers-1] = (LAYER){ font,x,y,w,h };
    window->layers[window->numlayers-1].chars = calloc(w*h,sizeof(BMCHAR));

    return &(window->layers[window->numlayers-1]);
}

void bm_clear_layer(LAYER* layer)
{
    memset(layer->chars,0,sizeof(BMCHAR)*layer->w*layer->h);
}

void bm_render_layer(LAYER* layer,WINDOW* window)
{
    const int w = layer->w;
    const int h = layer->h;

    for(int index = 0; index < layer->w*layer->h; index++)
    {
        BMCHAR bmc = layer->chars[index];
        int x = index % w;
        int y = index / w;
        SDL_Rect rect;
        SDL_Rect dstRect;
        rect = bmc.rect;
        dstRect = (SDL_Rect){(x*layer->font->cw)+layer->x,(y*layer->font->ch)+layer->y,layer->font->cw,layer->font->ch};
        SDL_RenderCopy(window->renderer,layer->font->image,&rect,&dstRect);
    }
}

//Font functions
FONT bm_load_font(int w, int h, const char* layout, const char* filepath, WINDOW* window)
{
    FONT font = (FONT){w,h,(char*)layout};
    font.chars = NULL;
    SDL_Surface* imagesurface = SDL_LoadBMP(filepath);
    font.image = SDL_CreateTextureFromSurface(window->renderer, imagesurface);
    SDL_FreeSurface(imagesurface);

    int charsinfont = strlen(layout);
    int texw, texh;
    SDL_QueryTexture(font.image,NULL,NULL,&texw,&texh);

    int x = 0,y = 0;
    for(int currentchar = 0; currentchar < charsinfont; currentchar+=1)
    {
        BMCHAR* bmrep; 
        bmrep = (BMCHAR*)malloc(sizeof(BMCHAR));
        bmrep->associate = font.charassociation[currentchar];
        bmrep->rect = (SDL_Rect){x,y,font.cw,font.ch};
        HASH_ADD(hh,font.chars,associate,sizeof(char),bmrep);

        if(x < texw - font.cw)
        {
            x += font.cw;
        }
        else
        {
            x = 0;
            y += font.ch;
        }
    }
    return font;
}

void bm_destroy_font(FONT* font){
    SDL_DestroyTexture(font->image);
    BMCHAR* c, *tmp;
    HASH_ITER(hh, font->chars,c,tmp){
        HASH_DEL(font->chars,c);
        free(c);
    }
}


//displaying functions
void bm_putchar(char c, int x, int y, LAYER* layer, WINDOW* window)
{
    int index = x+(y*layer->w);
    BMCHAR* bmc;
    if(index < (layer->w*layer->h))
    {
        HASH_FIND(hh,layer->font->chars,&c,sizeof(char),bmc);
        layer->chars[index] = *bmc;
    }
}

void bm_print(char* s,int x, int y,LAYER* layer, WINDOW* window)
{
    int length = strlen(s);

    for(int z = 0; z < length; z++)
    {
        bm_putchar(s[z],x+z,y,layer,window);
    }
}