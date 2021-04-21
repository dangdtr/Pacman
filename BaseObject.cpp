#include "BaseObject.h"

BaseObject::BaseObject()
{
    p_object = NULL;
    p_rect.x = 0;
    p_rect.y = 0;
    p_rect.h = 0;
    p_rect.w = 0;
}

BaseObject::~BaseObject()
{
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer *screen)
{   //dung de load backround
    SDL_DestroyTexture(p_object);
    SDL_Texture *new_texture = NULL;
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        //set color key
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, pngCOLOR_KEY_R, pngCOLOR_KEY_G, pngCOLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            p_rect.w = load_surface->w;
            p_rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }

    p_object = new_texture;

    return p_object != NULL;
}

SDL_Texture *BaseObject::LoadPNG(std::string path, SDL_Renderer *screen)
{   //dung de load texture
    SDL_Texture *new_texture = NULL;
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, pngCOLOR_KEY_R, pngCOLOR_KEY_G, pngCOLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            p_rect.w = load_surface->w;
            p_rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }

    p_object = new_texture;
    return p_object;
}

bool BaseObject::BGLoadImg(std::string path, SDL_Renderer *screen)// dành riêng load back
{   //dung de load backround
    SDL_DestroyTexture(p_object);
    SDL_Texture *new_texture = NULL;
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        //set color key
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, imgCOLOR_KEY_R, imgCOLOR_KEY_G, imgCOLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            p_rect.w = load_surface->w;
            p_rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }

    p_object = new_texture;

    return p_object != NULL;
}

void BaseObject::Render(SDL_Renderer *des, const SDL_Rect *clip /* = NULL */)
{
    SDL_Rect renderquad = {p_rect.x, p_rect.y, p_rect.w, p_rect.h};

    SDL_RenderCopy(des, p_object, clip, &renderquad);
}

void BaseObject::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(ren, tex, NULL, &rect);
}

void BaseObject::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    // sau dòng này có cái //
    //SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);

    SDL_RenderCopy(ren, tex, p_clip, &rect);
}



void BaseObject::waitUntilKeyPressed() // ok
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) != 0 &&
                (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}


void BaseObject::Free()
{
    if (p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        p_rect.w = 0;
        p_rect.h = 0;
    }
}

void BaseObject::SetRect(const int &x, const int &y)
{
    p_rect.x = x, p_rect.y = y;
}
SDL_Rect BaseObject::GetRect() const
{
    return p_rect;
}
SDL_Texture *BaseObject::GetObject() const
{
    return p_object;
}

void BaseObject::Destroy(SDL_Texture *texture, SDL_Window *window, SDL_Renderer *ren)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}
