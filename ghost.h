#ifndef GHOST_H_
#define GHOST_H_
#include "CommonFunction.h"
#include "BaseObject.h"
#include <ctime>
#include <cstdlib>


class Ghost: public BaseObject
{
public:

    Ghost();
    ~Ghost();

    void Show(SDL_Renderer* des);
    bool _LoadImg(std::string path, SDL_Renderer* screen);
    void setClips();
    void Action();

    void setPos(int x_, int y_);

    SDL_Rect upGhost[2];
	SDL_Rect downGhost[2];
	SDL_Rect leftGhost[2];
	SDL_Rect rightGhost[2];

    input_ input_type_;

    int frame_ = 0;
    int status_ = -1;

    int getX();
    int getY();

    bool checkCollision( std::vector<SDL_Rect>& a);
    void move( std::vector<SDL_Rect>& otherColliders );

protected:
    int Ghost_x_pos = 364 - 28;
    int Ghost_y_pos = 364;
    int stepX = 1;
    int stepY = 1;
    int step = 14;

    int *x = NULL;
    int *y = NULL;
};

#endif
