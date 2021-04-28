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

    if (menu_screen == NULL)
    {
        SDL_DestroyTexture(menu_screen);
    }

    renderTexture(menu_screen, ren, 0, 0);

    while (playing)
    {
        SDL_RenderPresent(ren);

        SDL_Delay(1000);

        if (SDL_WaitEvent(&m_event) != 0 && m_event.key.keysym.sym == SDLK_LEFT)
        {
            SDL_DestroyTexture(menu_screen);
            //continue;
        }

        if (m_event.type == SDL_QUIT)
        {
            BaseObject::Destroy(menu_screen, window, ren);
            playing = false;
            //quit = true;
        };
    }
}

// bool MenuGame::Play_again(SDL_Renderer *ren, SDL_Window *window, long score)
// {

//     SDL_Texture *try_again = LoadPNG("image//e_try.png", ren);
//     SDL_Texture *e_background = LoadPNG("image//e_background.png", ren);
//     SDL_Texture *e_quit = LoadPNG("image//e_quit.png", ren);

//     if (try_again == nullptr || e_background == nullptr || e_quit == nullptr)
//     {
//         SDL_DestroyTexture(try_again);
//         SDL_DestroyTexture(e_background);
//         SDL_DestroyTexture(e_quit);
//     }

//     TextObject YourScore("Your Score: ");
//     YourScore.str_ += std::to_string(score);
//     SDL_Texture *your_text = YourScore.GetText(30, ren);

//     renderTexture(e_background, ren, 0, 0);
//     int x, y;
//     while (true)
//     {
//         renderTexture(your_text, ren, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 25);
//         SDL_RenderPresent(ren);
//         if (SDL_WaitEvent(&m_event) == 0)
//             continue;

//         if (m_event.type == SDL_QUIT)
//             return false;

//         else if (m_event.type == SDL_MOUSEMOTION)
//         {
//             x = m_event.motion.x;
//             y = m_event.motion.y;
//             if (116 <= x && x <= 116 + 129 && 421 <= y && y <= 421 + 83)
//                 renderTexture(try_again, ren, 0, 0);
//             else if (303 <= x && x <= 303 + 129 && 421 <= y && y <= 421 + 83)
//                 renderTexture(e_quit, ren, 0, 0);
//             else
//                 renderTexture(e_background, ren, 0, 0);
//         }
//         else if (m_event.type == SDL_MOUSEBUTTONDOWN)
//             if (m_event.button.button == SDL_BUTTON_LEFT)
//             {
//                 if (116 <= x && x <= 116 + 129 && 421 <= y && y <= 421 + 83)
//                     return true;
//                 else if (303 <= x && x <= 303 + 129 && 421 <= y && y <= 421 + 83)
//                     return false;
//             }
//     }
//     SDL_DestroyTexture(try_again);
//     SDL_DestroyTexture(e_background);
//     SDL_DestroyTexture(e_quit);
// }
