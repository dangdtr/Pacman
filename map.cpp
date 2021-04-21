#include "map.h"
// #include "CommonFunction.h"
// #include "BaseObject.h"

//#include <stdafx.h>
GameMap::GameMap()
{
}
GameMap::~GameMap()
{
}
TileMap::TileMap()
{
}
TileMap::~TileMap()
{
}

void GameMap::LoadMap(char* path)
{
    std::ifstream file(path);
    while(!file.eof())
        for (int i = 0; i < MAX_MAP_Y; i++)
        {
            for (int j = 0; j < MAX_MAP_X; j++)
            {
                int c;
                file >> c;
                game_map.tile[i][j] = c;
            }
        }
    file.close();
}

void GameMap::setClipTile()
{
    mCollision.resize(37);
    mCollision[0] = {0,0, TILE_SIZE * 19, TILE_SIZE};
    mCollision[1] = {0,TILE_SIZE, TILE_SIZE, TILE_SIZE * 8};
    mCollision[2] = {TILE_SIZE * 2, TILE_SIZE * 2, TILE_SIZE * 2, TILE_SIZE};
    mCollision[3] = {TILE_SIZE * 5, TILE_SIZE * 2, TILE_SIZE * 3, TILE_SIZE};
    mCollision[4] = {TILE_SIZE * 9, TILE_SIZE, TILE_SIZE, TILE_SIZE * 2};
    mCollision[5] = {TILE_SIZE * 11, TILE_SIZE * 2, TILE_SIZE * 3, TILE_SIZE};
    mCollision[6] = {TILE_SIZE * 15, TILE_SIZE * 2, TILE_SIZE * 2, TILE_SIZE};
    mCollision[7] = {TILE_SIZE * 18, TILE_SIZE, TILE_SIZE, TILE_SIZE * 8};
    mCollision[8] = {TILE_SIZE * 2, TILE_SIZE * 4, TILE_SIZE * 2, TILE_SIZE};
    mCollision[9] = {TILE_SIZE * 5, TILE_SIZE * 4, TILE_SIZE, TILE_SIZE * 5};
    mCollision[10]= {TILE_SIZE * 7, TILE_SIZE * 4, TILE_SIZE * 5, TILE_SIZE};
    mCollision[11]= {TILE_SIZE * 13, TILE_SIZE * 4, TILE_SIZE, TILE_SIZE * 5};
    mCollision[12]= {TILE_SIZE * 15, TILE_SIZE * 4, TILE_SIZE * 2, TILE_SIZE};
    mCollision[13]= {TILE_SIZE, TILE_SIZE * 6, TILE_SIZE * 3, TILE_SIZE * 3};
    mCollision[14]= {TILE_SIZE * 6,TILE_SIZE * 6, TILE_SIZE * 2, TILE_SIZE};
    mCollision[15]= {TILE_SIZE * 9, TILE_SIZE * 5, TILE_SIZE, TILE_SIZE * 2};
    mCollision[16]= {TILE_SIZE * 11, TILE_SIZE * 6, TILE_SIZE * 2, TILE_SIZE};
    mCollision[17]= {TILE_SIZE * 15, TILE_SIZE * 6, TILE_SIZE * 3, TILE_SIZE * 3};
    mCollision[18]= {0, TILE_SIZE * 10, TILE_SIZE, TILE_SIZE * 9};
    mCollision[19]= {TILE_SIZE, TILE_SIZE * 10,TILE_SIZE * 3, TILE_SIZE * 3};
    mCollision[20]= {TILE_SIZE * 5, TILE_SIZE * 10, TILE_SIZE, TILE_SIZE * 5};
    mCollision[21]= {TILE_SIZE * 6, TILE_SIZE * 12, TILE_SIZE * 2, TILE_SIZE};
    mCollision[22]= {TILE_SIZE * 11, TILE_SIZE * 12, TILE_SIZE * 2, TILE_SIZE};
    mCollision[23]= {TILE_SIZE * 13, TILE_SIZE * 10, TILE_SIZE,TILE_SIZE * 5};
    mCollision[24]= {TILE_SIZE * 15, TILE_SIZE * 10, TILE_SIZE * 3, TILE_SIZE * 3};
    mCollision[25]= {TILE_SIZE * 18, TILE_SIZE * 10, TILE_SIZE, TILE_SIZE * 9};
    mCollision[26]= {TILE_SIZE * 2, TILE_SIZE * 14, TILE_SIZE * 2, TILE_SIZE};
    mCollision[27]= {TILE_SIZE * 9, TILE_SIZE * 12, TILE_SIZE, TILE_SIZE * 2};
    mCollision[28]= {TILE_SIZE * 7, TILE_SIZE * 14, TILE_SIZE * 5, TILE_SIZE};
    mCollision[29]= {TILE_SIZE * 15, TILE_SIZE * 14, TILE_SIZE * 2, TILE_SIZE};
    mCollision[30]= {TILE_SIZE * 2, TILE_SIZE * 16, TILE_SIZE * 2, TILE_SIZE};
    mCollision[31]= {TILE_SIZE * 5, TILE_SIZE * 16, TILE_SIZE * 3, TILE_SIZE};
    mCollision[32]= {TILE_SIZE * 9, TILE_SIZE * 16, TILE_SIZE, TILE_SIZE * 2};
    mCollision[33]= {TILE_SIZE * 11, TILE_SIZE * 16, TILE_SIZE * 3, TILE_SIZE};
    mCollision[34]= {TILE_SIZE * 15, TILE_SIZE * 16, TILE_SIZE * 2, TILE_SIZE};
    mCollision[35]= {TILE_SIZE, TILE_SIZE * 18, TILE_SIZE * 17, TILE_SIZE};
    mCollision[36]= {TILE_SIZE * 7, TILE_SIZE * 8, TILE_SIZE * 5, TILE_SIZE * 3};
}


std::vector<SDL_Rect>& GameMap::getColliders()
{
    return mCollision;
}
