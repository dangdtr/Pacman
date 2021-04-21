#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED
#include"CommonFunction.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    void SetRect(const int&x, const int&y);
    SDL_Rect GetRect() const;
    SDL_Texture* GetObject() const;
    SDL_Texture* LoadPNG(std::string path, SDL_Renderer* screen);
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    virtual bool BGLoadImg(std::string path, SDL_Renderer* screen);



    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
    void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
    virtual void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

    void Free();
    void waitUntilKeyPressed();
    void Destroy(SDL_Texture* texture, SDL_Window* window,SDL_Renderer* ren);

     int width_frame_ = 0;
     int hight_frame_ = 0;

    enum MoveType{
        MOVE_UP = 0,
        MOVE_LEFT = 1,
        MOVE_DOWN = 2,
        MOVE_RIGHT = 3,
        NO_MOVE = 4,
        DEAD = 5
    };

protected:
    SDL_Texture* p_object;
    SDL_Rect p_rect;
    SDL_Rect* p_clip = NULL;

};

#endif // BASEOBJECT_H_INCLUDED
