#ifndef MENU_GAME_H_
#define MENU_GAME_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "algorithm"
class MenuGame : public BaseObject
{
public:
   MenuGame();
    ~MenuGame();

    void Menu_game(SDL_Renderer* ren, SDL_Window* window);
    void Pause_game(SDL_Renderer* ren, SDL_Window* window);
    void Save_high_score(long &score);
    long get_high_score();
private:
    long high_score = 0;

    SDL_Event m_event;
    bool playing = true;
    bool playing_when_pause = true;
};

#endif
