#ifndef COMMONFUNCTION_H_
#define COMMONFUNCTION_H_

#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


using namespace std;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int SCREEN_WIDTH = 532 ;
const int SCREEN_HEIGHT = 532 + 100;
const int SCREEN_BPP = 32;

const int imgCOLOR_KEY_R = 167;
const int imgCOLOR_KEY_G = 175;
const int imgCOLOR_KEY_B = 180;

const int pngCOLOR_KEY_R = 0;
const int pngCOLOR_KEY_G = 0;
const int pngCOLOR_KEY_B = 0;
const SDL_Color BLUE_COLOR = { 0,255,255};

const int RENDER_DRAW_COLOR = 0xff;

typedef struct input_{
    int left_;
    int right_;
    int up_;
    int down_;
};
#define PACMAN_SIZE 26
#define GHOST_SIZE 26
#define POINT_SIZE 20
//map
#define TILE_SIZE 28
#define MAX_MAP_X 19
#define MAX_MAP_Y 19
// #define MAX_TILES 2 // so luong anh tile

typedef struct Map{
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};
const int g_tile[19][19] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,4,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
    {1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1},
    {1,1,1,1,0,1,0,1,1,2,1,1,0,1,0,1,1,1,1},
    {0,0,0,0,0,0,0,1,2,2,2,1,0,0,0,0,0,0,0},
    {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
    {1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1},
    {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,4,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,4,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


#endif // COMMONFUNCTION_H_
