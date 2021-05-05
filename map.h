#ifndef MAP_H_
#define MAP_H_
#include "CommonFunction.h"
#include "BaseObject.h"




class GameMap : public BaseObject
{
public:
    GameMap();
    ~GameMap();
    virtual void LoadMap(char* path);
    
    void setClipTile();
    

    std::vector<SDL_Rect>& getColliders();
    std::vector<SDL_Rect>& getCollidersGHO();


protected:
    Map game_map;
    std::vector<SDL_Rect> mCollision;
    std::vector<SDL_Rect> mCollisionGHO;


};


#endif
