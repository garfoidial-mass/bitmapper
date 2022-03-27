#ifndef BM_MAIN_H
#define BM_MAIN_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "layouts.h"
#include "scancodes.h"

#include "ut/uthash.h"

//structs & enums

typedef struct _color{
    uint8_t r,g,b;
} COLOR;

typedef struct _bitmap_char{
    char associate; //associated character
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
    BMCHAR* chars; // array of all the characters in the layer
} LAYER;

typedef struct _bmpfontlib_window{
    int numlayers;
    LAYER* layers;
    int width, height; // height and width in pixels
    SDL_Renderer* renderer;
    SDL_Window* window;
    uint8_t quit;
    uint8_t* keys;
} WINDOW;

//Window functions

int bm_init_window(int x, int y, int width, int height, COLOR clearcolor , const char* title, WINDOW* window);

int bm_cleanup_window(WINDOW* window);

int bm_process_window(WINDOW* window);

void bm_render_window(WINDOW* window);

void bm_window_clear(WINDOW* window);

int bm_getkey(KEY key, WINDOW* window);

//Layer functions

LAYER* bm_add_layer(int x, int y,int w, int h, FONT* font, WINDOW* window);

void bm_clear_layer(LAYER* layer);

void bm_render_layer(LAYER* layer,WINDOW* window);

//Font functions
FONT bm_load_font(int w, int h, const char* layout, const char* filepath, WINDOW* window);

void bm_destroy_font(FONT* font);


//displaying functions
void bm_putchar(char c, int x, int y, LAYER* layer, WINDOW* window);

void bm_print(char* s,int x, int y,LAYER* layer, WINDOW* window);

#endif