#include "point.h"
Point::Point()
{   
    game_map = new GameMap;
    game_map ->LoadMap("map.txt");
    _tile = new int*[MAX_MAP_Y];
    for (int i = 0; i < MAX_MAP_X; i++)
        _tile[i] = new int[MAX_MAP_Y];
}
Point::~Point()
{
}

void Point::setPosMap(){
    std::ifstream file("map.txt");
    while(!file.eof())
        for (int i = 0; i < MAX_MAP_Y; i++)
        {
            for (int j = 0; j < MAX_MAP_X; j++)
            {
                int c;
                file >> c;
                this->_tile[i][j] = c;
                std::cerr << this->_tile[i][j] << " ";
            }
            std::cerr << std::endl;     
        }
    file.close();
}
void Point::Show(SDL_Renderer *des)
{
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            if (this->_tile[i][j] == 0)
            {
                p_rect.x = j * TILE_SIZE;
                p_rect.y = i * TILE_SIZE;
                renderTexture(p_object, des, p_rect.x + 3, p_rect.y + 2, POINT_SIZE, POINT_SIZE);
            }
        }
    }
    // int ran_x = rand() % MAX_MAP_X, ran_y = rand() % MAX_MAP_Y;
    // renderTexture(p_object, des, ran_x * TILE_SIZE + 2, ran_y * TILE_SIZE + 2, POINT_SIZE + 6, POINT_SIZE + 6);
}

bool Point::_LoadImg(std::string path, SDL_Renderer *screen)
{

    bool ret = BaseObject::LoadImg(path, screen);
    return ret;
}

std::vector<SDL_Rect>& Point::getColliders()
{
    return mCollision;
}

int Point::setClipTile()
{
    mCollision.resize(166);
    int count = 0, score = 0;
    for (int i = 0; i < MAX_MAP_Y; i++){
        for (int j = 0; j < MAX_MAP_X; j++){
            if ( this->_tile[i][j] == 0){
                mCollision[count] = {TILE_SIZE * j + 5, TILE_SIZE * i + 5, POINT_SIZE, POINT_SIZE};
            }
            if ( this->_tile[i][j] == 3 ){
                score++;
                mCollision[count] = {0,0,0,0};
            }
        }
    }
    return score;
}
void Point::setSPoint(int x_){
    this->sPoint = x_;
}
int Point::getSPoint(){
    return this->sPoint;
}

void Point::deletePoint(int x_, int y_){
    this->_tile[y_ / TILE_SIZE][x_ / TILE_SIZE] = 3;
}