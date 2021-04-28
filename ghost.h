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
    bool _LoadImg(const std::string &path, SDL_Renderer* screen);
    void setClips();
    void Action();

    void setPos(const int &x_pos, const int &y_pos);

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

    void setSTEPWhenDead();
    void setSTEPWhenALive();

    bool checkCollision( std::vector<SDL_Rect>& a);
    void move( std::vector<SDL_Rect>& otherColliders );

    bool leftable(const int &x_pos, const int &y_pos);
    bool rightable(const int &x_pos, const int &y_pos);
    bool downable(const int &x_pos, const int &y_pos);
    bool upable(const int &x_pos, const int &y_pos);

    void setFlagWhenPacEatBig(const bool &flag_);
    bool getFlagWhenPacEatBig();

    void setFlagEatWeakGhost(const bool &flag_);
    bool getFlagEatWeakGhost();

    SDL_Rect getRect();

protected:
    const int STEP = 14;
    int Ghost_x_pos = 252; //x9
    int Ghost_y_pos = 196; //x7
    int stepX = 0;
    int stepY = 0;
    int step;

    bool flag_when_pac_eat_big ;
    bool flag_pac_eat_weak_ghost ;

    int *x = NULL;
    int *y = NULL;
}; 

#endif
