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
    void Show(SDL_Renderer* des, const int &index);
    void ShowHealth(SDL_Renderer *des);

    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    bool checkCollisionWith( std::vector<SDL_Rect>& a);
    //bool checkCollisionWithPoint( std::vector<SDL_Rect>& a);// không cần thiết
    bool checkCollisionWithEachGhost(SDL_Rect a);

    bool _LoadImg(const std::string& path, SDL_Renderer* screen);

    int getX();
    int getY();

    void setClips();
    void setPos(const int &x_pos, const int &y_pos);

    void move( std::vector<SDL_Rect>& otherColliders );

    bool leftable(const int &x_pos, const int &y_pos);
    bool rightable(const int &x_pos, const int &y_pos);
    bool downable(const int &x_pos, const int &y_pos);
    bool upable(const int &x_pos, const int &y_pos);

    bool IsGameOver(int &score_);

    void setFlagDead(const bool &flag_);
    bool getFlagDead();

    void setFlagEatBigPoint(const bool &flag_);
    bool getFlagEatBigPoint();
    
    void setHealth(const int &health_);
    int getHealth();

    SDL_Rect upPacman[2];
	SDL_Rect downPacman[2];
	SDL_Rect leftPacman[2];
	SDL_Rect rightPacman[2];
    SDL_Rect deadPacman[8];

    input_ input_type_;
    GameMap* game_map;

protected:
    int Pacman_x_pos;
    int Pacman_y_pos;
    int stepX ;
    int stepY ;
    int step ;

    bool flag_dead ;
    bool flag_eat_big_point ;
    int health;
    bool is_game_over;

    int frame_ = 0;
    int status_ = -1;

    int *x = NULL;
    int *y = NULL;
};

#endif // Pacman_H_INCLUDED
