#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED
#include "CommonFunction.h"
#include "BaseObject.h"
#include "map.h"
#include "point.h"

class Pacman: public BaseObject
{
public:
    Pacman();
    ~Pacman();
    void Show(SDL_Renderer* des);
    void Show(SDL_Renderer* des, int index);

    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    bool checkCollisionWith( std::vector<SDL_Rect>& a);
    bool checkCollisionWithPoint( std::vector<SDL_Rect>& a);// không cần thiết
    bool checkCollisionWithEachGhost(SDL_Rect a);

    bool _LoadImg(std::string path, SDL_Renderer* screen);

    int getX();
    int getY();

    void setClips();
    void setPos(int x_pos, int y_pos);
    void setSatus();

    void move( std::vector<SDL_Rect>& otherColliders );

    bool leftable(int x_pos, int y_pos);
    bool rightable(int x_pos, int y_pos);
    bool downable(int x_pos, int y_pos);
    bool upable(int x_pos, int y_pos);


    SDL_Rect upPacman[2];
	SDL_Rect downPacman[2];
	SDL_Rect leftPacman[2];
	SDL_Rect rightPacman[2];
    SDL_Rect deadPacman[8];

    input_ input_type_;

    int frame_ = 0;
    int status_ = -1;

    GameMap* game_map;

    void setFlagDead(bool flag_);
    bool getFlagDead();

    void setFlagEatBigPoint(bool flag_);
    bool getFlagEatBigPoint();

protected:
    int Pacman_x_pos;
    int Pacman_y_pos;
    int stepX ;
    int stepY ;
    int step ;

    bool flag_dead = false;
    bool flag_eat_big_point = false;


    int *x = NULL;
    int *y = NULL;
};

#endif // Pacman_H_INCLUDED
