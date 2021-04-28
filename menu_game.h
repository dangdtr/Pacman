#ifndef MENU_GAME_H_
#define MENU_GAME_H_

#include "CommonFunction.h"
#include "BaseObject.h"
class MenuGame : public BaseObject
{
public:
   MenuGame();
    ~MenuGame();

    void Menu_game(SDL_Renderer* ren, SDL_Window* window);
    bool Play_again(SDL_Renderer* ren, SDL_Window* window, long score);

private:
    

    SDL_Event m_event;
    bool playing = true;
};

#endif
