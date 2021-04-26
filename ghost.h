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

    SDL_Rect upGhost[3];
	SDL_Rect downGhost[3];
	SDL_Rect leftGhost[3];
	SDL_Rect rightGhost[3];
    SDL_Rect weakGhostBlue[4];
    SDL_Rect weakGhostWhite[2];
    
    

    input_ input_type_;

    int frame_ = 0;
    int status_ = -1;

    int getX();
    int getY();

    bool checkCollision( std::vector<SDL_Rect>& a);
    void move( std::vector<SDL_Rect>& otherColliders );

    bool leftable(int x_pos, int y_pos);
    bool rightable(int x_pos, int y_pos);
    bool downable(int x_pos, int y_pos);
    bool upable(int x_pos, int y_pos);

    void setFlagWhenPacEatBig(bool flag_);
    bool setFlagWhenPacEatBig();

    void setFlagEatWeakGhost(bool flag_);
    bool setFlagEatWeakGhost();

    SDL_Rect getRect();

protected:
    int Ghost_x_pos = 252; //x9
    int Ghost_y_pos = 196; //x7
    int stepX = 0;
    int stepY = 0;
    int step = 14;

    bool flag_when_pac_eat_big = false;
    bool flag_pac_eat_weak_ghost = false;

    int *x = NULL;
    int *y = NULL;
}; 

#endif
