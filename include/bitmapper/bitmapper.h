#ifndef BM_MAIN_H
#define BM_MAIN_H

#define SDL_MAIN_HANDLED

#include <stdint.h>
#include <SDL2/SDL.h>
#include "stb/stb_image.h"

#include "layouts.h"
#include "scancodes.h"

#include "ut/uthash.h"

//RGBA color
typedef struct _color{
    uint8_t r,g,b,a;
} COLOR;

//Defines an individual character in a bitmap font.
typedef struct _bitmap_char{
    char associate; //associated character
    SDL_Rect rect;
    UT_hash_handle hh;
} BMCHAR;

//Bitmap font loaded from an image.
typedef struct _font{
    int cw,ch; // char width and height
    char* charassociation; //a string with all of the characters in the font's associated chars
    BMCHAR* chars;
    SDL_Texture* image;
} FONT;

//A text layer with x and y offset, specific font and color tint.
typedef struct _layer{
    FONT *font;
    COLOR color;
    int x,y; //x and y offset in chars
    int w,h; // width and height in chars
    BMCHAR* chars; // array of all the characters in the layer
    SDL_Texture* texture;
} LAYER;

//Defines a window to draw to.
typedef struct _bmpfontlib_window{
    int numlayers;
    LAYER* layers;
    int width, height; // height and width in pixels
    SDL_Renderer* renderer;
    SDL_Window* window;
    uint8_t quit;
    uint8_t* keys;
} WINDOW;

/*Initializes a window, returning a pointer to the initialized window structure. x and y are the coordinates of 
the window on screen, and width and height are measured in pixels (some other things in the library are measured 
by number of characters in a bitmap font). The clearcolor is the color the window will be filled with when calling 
bm_clear_window().*/
WINDOW* bm_window_init(int x, int y, int width, int height, COLOR clearcolor , const char* title);

//Frees all memory associated with a window and its layers. It must be called after you are done with your window.
int bm_window_cleanup(WINDOW* window);

/*Called to check inputs and events happening in the specified window. Currently it only supports keyboard input, 
but mouse support may be added later. This function must be called at the beginning of your main loop.*/
int bm_window_process(WINDOW* window);

//Draws all layers in the given window to the screen
void bm_window_render(WINDOW* window);

//Fills the window with the clear color specified in bm_init_window().
void bm_window_clear(WINDOW* window);

//Checks if the specified window should be open, returning 1 if yes, 0 if no.
uint8_t bm_window_is_open(WINDOW* window);

//Adds a layer using the specified FONT to the specified window and returns a pointer to the layer. w and h here are in chars.
LAYER* bm_layer_add(int x, int y,int w, int h, FONT* font, WINDOW* window);

//Frees memory for a layer, automatically handled when destroying a window. 
void bm_layer_remove(LAYER* layer);

//Adds a color tint to the layer, as specified by the color's r, g and b values (between 0 and 255), and sets the layer's alpha to the color's alpha value. A tint value of (255,255,255,255) resets the layer to its original settings.
void bm_layer_tint(COLOR color, LAYER* layer,WINDOW* window);

//Updates the layer's texture that all of the text is rendered to. This does not usually need to be called manually.
void bm_layer_update(LAYER* layer,WINDOW* window);

//Removes all printed characters from the layer.
void bm_layer_clear(LAYER* layer,WINDOW* window);

//Copies the layer texture into the framebuffer, does not actually display anything.
void bm_layer_render(LAYER* layer,WINDOW* window);

/*This function loads a font from an image file (of any type that stb_image supports) for the specified window. w and h are in pixels, 
and specify the size of one character in the font. The layout is a raw (hence the need for gnu extensions) c string containing the order 
of associated text chars in a font. For example, the layout for a font that only has uppercase letters with the space character at the 
the end would be R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ )". Some layouts I have seen commonly used are provided as the BM_LAYOUT defines, and most
newer bitmap and textmode fonts come with a file specifying their layout.*/
FONT* bm_font_load(int w, int h, const char* layout, const char* filepath, WINDOW* window);

//Frees memory for a font. Call this after you are done with a font, after you are done printing any characters on a layer that uses it.
void bm_font_destroy(FONT* font);

//Prints the specified character to the specified layer. x and y are in chars. It will fail if you attempt to print a character not in the font.
void bm_putchar(char c, int x, int y, LAYER* layer, WINDOW* window);

//Prints the string specified b s at the x and y (char position) on screen, on the specified layer. It will fail if you attempt to print a character not in the font.
void bm_print(char* s,int x, int y,LAYER* layer, WINDOW* window);

//Checks if the specified key is pressed for the specified window, returns 1 if yes, 0 if no. Key can be specified using the BM_KEY defines.
int bm_getkey(KEY key, WINDOW* window);

#endif