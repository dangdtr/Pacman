#ifndef MAP_H_
#define MAP_H_
#include "CommonFunction.h"
#include "BaseObject.h"


class TileMap : public BaseObject{
public:
    TileMap();
    ~TileMap();

};

class GameMap : public BaseObject
{
public:
    GameMap();
    ~GameMap();
    virtual void LoadMap(char* path);
    
    void setClipTile();

    std::vector<SDL_Rect>& getColliders();

protected:
    Map game_map;
    //TileMap tile_map[MAX_TILES];
    std::vector<SDL_Rect> mCollision;

};


#endif
