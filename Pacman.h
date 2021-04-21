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
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    bool checkCollisionWithWall( std::vector<SDL_Rect>& a);
    bool checkCollisionWithPoint( std::vector<SDL_Rect>& a);// không cần thiết
    bool checkCollisionWithGhost( SDL_Rect& a);

    bool _LoadImg(std::string path, SDL_Renderer* screen);

    int getX();
    int getY();

    void setClips();

    void move( std::vector<SDL_Rect>& otherColliders );

    SDL_Rect upPacman[2];
	SDL_Rect downPacman[2];
	SDL_Rect leftPacman[2];
	SDL_Rect rightPacman[2];

    input_ input_type_;

    int frame_ = 0;
    int status_ = -1;

    GameMap* game_map;
    

protected: 
    int Pacman_x_pos;
    int Pacman_y_pos;
    int stepX ;
    int stepY ;
    int step ;

    int *x = NULL;
    int *y = NULL;
};

#endif // Pacman_H_INCLUDED
