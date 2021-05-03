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

        SDL_Delay(100);

        SDL_RenderPresent(ren);

        if (SDL_WaitEvent(&m_event) == 0){
            SDL_RenderPresent(ren);
            continue;
        }


        if (m_event.type == SDL_QUIT)
        {
            BaseObject::Destroy(menu_screen, window, ren);
            playing = false;
            //quit = true;
        };
        if (m_event.type == SDL_KEYDOWN){
            switch (m_event.key.keysym.sym){
                case SDLK_SPACE:
                    playing = false;
                    continue;
                case SDLK_q:
                    BaseObject::Destroy(menu_screen, window, ren);
                    playing = false;
                    //continue;
                    break;
                case SDLK_h:
                    SDL_RenderClear(ren);
                    SDL_SetRenderDrawColor(ren,0,0,0,0);

                    renderTexture(help_screen, ren, 0, 0);
                    //continue;
                    break;
                case SDLK_m:
                    SDL_RenderClear(ren);
                    //SDL_SetRenderDrawColor(ren,0,0,0,0);
                    renderTexture(menu_screen, ren, 0, 0);
                    SDL_RenderPresent(ren);
                    //continue;
                    break;
            }
        }
    }
    SDL_DestroyTexture(menu_screen);
    SDL_DestroyTexture(help_screen);


}
