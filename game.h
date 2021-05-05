#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "Pacman.h"
#include "ghost.h"
#include "map.h"
#include "point.h"
#include "menu_game.h"
#include "TextObject.h"

class Game
{
public:

    bool loadBackground();
    bool init();
    void close();

    void waitUntilKeyPressed();
    bool run();

protected:
    BaseObject g_background;
    TTF_Font *g_font = NULL;
    Mix_Music *g_begin = Mix_LoadMUS("sound/pacman_beginning.wav");
};

#endif // GAME_H_
