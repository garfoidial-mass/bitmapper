#define STB_IMAGE_IMPLEMENTATION

#include "bitmapper.h"



WINDOW* bm_window_init(int x, int y, int width, int height, COLOR clearcolor , const char* title)
{
    WINDOW* window = malloc(sizeof(WINDOW));
    window->quit = 0;
    window->numlayers = 1;
    window->width = width;
    window->height = height;
    window->layers = (LAYER*)calloc(1,sizeof(LAYER));
    window->keys = calloc(550,sizeof(uint8_t));

    int rendererflags = SDL_RENDERER_ACCELERATED;
    int windowflags = 0;

    int error = 0;
    error = SDL_Init(SDL_INIT_VIDEO);

    if(error < 0){
        return NULL;
    }

    window->window = SDL_CreateWindow(title,x,y,width,height,windowflags);

    if(!window->window)
    {
        return NULL;
    }
    error = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    if(error != 1){
        return NULL;
    }

    window->renderer = SDL_CreateRenderer(window->window,-1,rendererflags);

    SDL_SetRenderDrawColor(window->renderer,clearcolor.r,clearcolor.g,clearcolor.b,clearcolor.a);
    SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);

    if(!window->renderer)
    {
        return NULL;
    }

    return window;
}



int bm_window_cleanup(WINDOW* window)
{
    printf("cleaning up\n");
    for(int x = 0; x < window->numlayers; x++)
    {
        bm_layer_remove(&(window->layers[x]));
    }
    free(window->layers);
    free(window->keys);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
}


int bm_window_process(WINDOW* window)
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
    SDL_Delay(16);
}

void bm_window_render(WINDOW* window)
{
    for(int x = 0; x < window->numlayers; x++)
    {
        bm_layer_render(&(window->layers[x]),window);
    }
    SDL_RenderPresent(window->renderer);
}

uint8_t bm_window_is_open(WINDOW* window)
{
    return !window->quit;
}

void bm_window_clear(WINDOW* window)
{
    SDL_RenderClear(window->renderer);
}

//Layer functions

LAYER* bm_layer_add(int x, int y,int w, int h, FONT* font, WINDOW* window)
{   
    window->numlayers += 1;
    window->layers = realloc(window->layers,sizeof(LAYER) * window->numlayers);
    window->layers[window->numlayers-1] = (LAYER){ font, (COLOR){255,255,255,255},x,y,w,h };
    window->layers[window->numlayers-1].chars = calloc(w*h,sizeof(BMCHAR));
    window->layers[window->numlayers-1].texture = SDL_CreateTexture(window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,w*window->layers[window->numlayers-1].font->cw,h*window->layers[window->numlayers-1].font->ch);
    SDL_SetTextureBlendMode(window->layers[window->numlayers-1].texture, SDL_BLENDMODE_BLEND);
    return &(window->layers[window->numlayers-1]);
}

void bm_layer_remove(LAYER* layer)
{
    SDL_DestroyTexture(layer->texture);
    free(layer->chars);
}

void bm_layer_tint(COLOR color, LAYER* layer,WINDOW* window)
{
    layer->color = color;
    SDL_SetTextureColorMod(layer->texture,color.r,color.g,color.b);
    SDL_SetTextureAlphaMod(layer->texture,color.a);
    bm_layer_update(layer,window);
}

void bm_layer_clear(LAYER* layer,WINDOW* window)
{
    memset(layer->chars,0,sizeof(BMCHAR)*layer->w*layer->h);
    bm_layer_update(layer,window);
}

void bm_layer_update(LAYER* layer,WINDOW* window)
{
    SDL_SetRenderTarget(window->renderer,layer->texture);
    COLOR color;
    SDL_GetRenderDrawColor(window->renderer,&color.r,&color.g,&color.b,&color.a);
    SDL_SetRenderDrawColor(window->renderer,color.r,color.g,color.b,0);
    SDL_RenderClear(window->renderer);
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
        dstRect = (SDL_Rect){(x*layer->font->cw),(y*layer->font->ch),layer->font->cw,layer->font->ch};
        SDL_RenderCopy(window->renderer,layer->font->image,&rect,&dstRect);
    }

    SDL_SetRenderTarget(window->renderer,NULL);
    SDL_SetRenderDrawColor(window->renderer,color.r,color.g,color.b,color.a);
}

void bm_layer_render(LAYER* layer,WINDOW* window)
{
    int w,h;
    SDL_QueryTexture(layer->texture,NULL,NULL,&w,&h);
    SDL_RenderCopy(window->renderer,layer->texture,NULL,&(SDL_Rect){layer->x,layer->y,w,h});
}

//Font functions
FONT* bm_font_load(int w, int h, const char* layout, const char* filepath, WINDOW* window)
{
    //couldn't get SDL_Image to work lmao
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    unsigned char* data = stbi_load(filepath,&width,&height,&orig_format,req_format);

    if(data == NULL)
    {
        return NULL;
    }

    int depth, pitch;
    uint32_t pixelformat;
    if(req_format == STBI_rgb)
    {
        depth = 24;
        pitch = 3*width;
        pixelformat = SDL_PIXELFORMAT_RGB24;
    }
    else
    {
        depth = 32;
        pitch = 4*width;
        pixelformat = SDL_PIXELFORMAT_RGBA32;
    }

    SDL_Surface* imagesurface = SDL_CreateRGBSurfaceWithFormatFrom((void*)data,width,height,depth,pitch,pixelformat);

    if(imagesurface == NULL)
    {
        return NULL;
    }

    FONT* font = calloc(1,sizeof(FONT));
    *font = (FONT){w,h,(char*)layout};
    font->chars = NULL;
    font->image = SDL_CreateTextureFromSurface(window->renderer, imagesurface);
    SDL_SetTextureBlendMode(font->image,SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(imagesurface);
    stbi_image_free(data);

    int charsinfont = strlen(layout);
    int texw, texh;
    SDL_QueryTexture(font->image,NULL,NULL,&texw,&texh);

    int x = 0,y = 0;
    for(int currentchar = 0; currentchar < charsinfont; currentchar+=1)
    {
        BMCHAR* bmrep; 
        bmrep = (BMCHAR*)malloc(sizeof(BMCHAR));
        bmrep->associate = font->charassociation[currentchar];
        bmrep->rect = (SDL_Rect){x,y,font->cw,font->ch};
        HASH_ADD(hh,font->chars,associate,sizeof(char),bmrep);

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
    return font;
}

void bm_font_destroy(FONT* font){
    SDL_DestroyTexture(font->image);
    BMCHAR* c, *tmp;
    HASH_ITER(hh, font->chars,c,tmp){
        HASH_DEL(font->chars,c);
        free(c);
    }
}


//## Other Functions
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
    bm_layer_update(layer,window);
}

int bm_getkey(KEY key, WINDOW* window)
{
    return window->keys[key];
}