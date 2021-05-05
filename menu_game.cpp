#include "Menu_game.h"

MenuGame::MenuGame()
{
    ;
}

MenuGame::~MenuGame()

{
    ;
}

void MenuGame::Menu_game(SDL_Renderer *ren, SDL_Window *window)
{
    SDL_Texture *menu_screen = LoadPNG("image/menu_game.png", ren);

    SDL_Texture *help_screen = LoadPNG("image/help_game.png", ren);

    if (menu_screen == NULL || help_screen == NULL)
    {
        SDL_DestroyTexture(menu_screen);
    }

    renderTexture(menu_screen, ren, 0, 0);

    while (playing)
    {

        SDL_Delay(1);

        SDL_RenderPresent(ren);

        if (SDL_WaitEvent(&m_event) == 0)
        {
            continue;
        }

        if (m_event.type == SDL_QUIT)
        {
            BaseObject::Destroy(menu_screen, window, ren);
            playing = false;
        };
        if (m_event.type == SDL_KEYDOWN)
        {
            switch (m_event.key.keysym.sym)
            {
            case SDLK_SPACE:
                playing = false;
                continue;
            case SDLK_q:
                BaseObject::Destroy(menu_screen, window, ren);
                playing = false;
                break;
            case SDLK_h:
                SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
                renderTexture(help_screen, ren, 0, 0);
                continue;
            case SDLK_m:
                renderTexture(menu_screen, ren, 0, 0);
                continue;

            }
        }
    }
    SDL_DestroyTexture(menu_screen);
    SDL_DestroyTexture(help_screen);
}

void MenuGame::Pause_game(SDL_Renderer *ren, SDL_Window *window)
{
    SDL_Texture *pause_screen = LoadPNG("image/pause_game.png", ren);

    if (pause_screen == NULL)
    {
        SDL_DestroyTexture(pause_screen);
    }

    renderTexture(pause_screen, ren, 100, 100);
    SDL_RenderPresent(ren);

    while (playing_when_pause)
    {

        SDL_Delay(1);


        if (SDL_WaitEvent(&m_event) == 0)
        {
            continue;
        }

        if (m_event.type == SDL_QUIT)
        {
            BaseObject::Destroy(pause_screen, window, ren);
            playing_when_pause = false;
        };
        if (m_event.type == SDL_KEYDOWN)
        {
            switch (m_event.key.keysym.sym)
            {
            case SDLK_SPACE:
                playing_when_pause = false;
                continue;
            case SDLK_q:
                BaseObject::Destroy(pause_screen, window, ren);
                playing_when_pause = false;
                break;
            }
        }
    }
    cerr << "done pause" << endl;
    SDL_DestroyTexture(pause_screen);
    playing_when_pause = true;
}
void MenuGame::Save_high_score(long &score)
{
    using namespace std;
    ifstream high_score("high_score.txt");
    vector<int> v_score;
    while (!high_score.eof())
    {
        int a;
        high_score >> a;
        v_score.push_back(a);
    }
    if (score > v_score[2])
    {
        v_score.push_back(score);
        sort(v_score.rbegin(), v_score.rend());

        ofstream high_score("high_score.txt");
        for (int i = 0; i < 3; i++)
            high_score << v_score[i] << endl;
    }
    high_score.close();
}
long MenuGame::get_high_score(){
    ifstream high_score("high_score.txt");
    long a;
    high_score >> a;
    this->high_score = a;
    return this->high_score;
}
