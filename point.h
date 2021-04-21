#ifndef POINT_H_
#define POINT_H_


#include "CommonFunction.h"
#include "BaseObject.h"
#include "map.h"
class Point : public BaseObject
{
public:
    Point();
    ~Point();
    void Show(SDL_Renderer* des);
    //void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    //bool checkCollision( std:: vector<SDL_Rect>& a);

    bool _LoadImg(std::string path, SDL_Renderer* screen);
    void setPosMap();// load from txt

    int setClipTile(); // reurn số point mà pacman ăn đc
    std::vector<SDL_Rect>& getColliders();

    int getX();
    int getY();
    void setSPoint(int s_);
    int getSPoint();
    void deletePoint(int x_, int y_);
    
    GameMap* game_map;
    Map _map;
protected:
    int** _tile;//[MAX_MAP_Y][MAX_MAP_X];
    SDL_Rect point[2];

    int sPoint;
    std::vector<SDL_Rect> mCollision;


};

#endif
