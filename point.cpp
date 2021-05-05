#include "point.h"
Point::Point()
{
    game_map = new GameMap;
    game_map->LoadMap("map.txt");
    _tile = new int *[MAX_MAP_Y];
    for (int i = 0; i < MAX_MAP_X; i++)
        _tile[i] = new int[MAX_MAP_Y];
}
Point::~Point()
{
    for (int i = 0; i < MAX_MAP_X; i++)
        _tile[i] = NULL;
    _tile = NULL;
    game_map = NULL;
}

void Point::setPosMap()
{
    std::ifstream file("map.txt");
    while (!file.eof())
        for (int i = 0; i < MAX_MAP_Y; i++)
        {
            for (int j = 0; j < MAX_MAP_X; j++)
            {
                int c;
                file >> c;
                this->_tile[i][j] = c;
            }
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
                renderTexture(p_object, des, p_rect.x + 4, p_rect.y + 4, POINT_SIZE, POINT_SIZE);
            }
            else if (this->_tile[i][j] == 4 && frame % 2 == 0)
            {
                p_rect.x = j * TILE_SIZE;
                p_rect.y = i * TILE_SIZE;
                renderTexture(p_object, des, p_rect.x - 14, p_rect.y - 14, TILE_SIZE * 2, TILE_SIZE * 2);
            }
        }
    }
}

bool Point::_LoadImg(const std::string &path, SDL_Renderer *screen)
{

    bool ret = BaseObject::LoadImg(path, screen);
    return ret;
}

std::vector<SDL_Rect> &Point::getColliders()
{
    return mCollision;
}

int Point::setClipTile()
{
    frame++;
    mCollision.resize(167);
    int count = 0, score = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            if (this->_tile[i][j] == 0)
            {
                mCollision[count] = {TILE_SIZE * j + 5, TILE_SIZE * i + 5, POINT_SIZE, POINT_SIZE};
            }

            if (this->_tile[i][j] == 3)
            {
                score++;
                mCollision[count] = {0, 0, 0, 0};
            }
            if (this->_tile[i][j] == 5)
            {
                score += 4;
                mCollision[count] = {0, 0, 0, 0};
            }
        }
    }
    return score;
}
void Point::setSPoint(const int &x_)
{
    this->sPoint = x_;
}
int Point::getSPoint()
{
    return this->sPoint;
}

void Point::deletePoint(const int &x_, const int &y_)
{
    if (this->_tile[y_ / TILE_SIZE][x_ / TILE_SIZE] == 0)
    {   
        Mix_PlayChannel(-1,g_chomp,0);
        this->_tile[y_ / TILE_SIZE][x_ / TILE_SIZE] = 3;
    }
    else if (this->_tile[y_ / TILE_SIZE][x_ / TILE_SIZE] == 4)
    {
        Mix_PlayChannel(-1,g_eat_big,0);
        this->_tile[y_ / TILE_SIZE][x_ / TILE_SIZE] = 5;
    }
}

bool Point::checkBigPoint(const int &x_, const int &y_)
{
    if (this->_tile[y_ / TILE_SIZE][x_ / TILE_SIZE] == 4 || //||
        this->_tile[(y_ + TILE_SIZE / 2 - 1) / TILE_SIZE][(x_ + TILE_SIZE / 2 - 1) / TILE_SIZE] == 4)
    {
        return true;
    }
    return false;
}
