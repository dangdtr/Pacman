#include "Pacman.h"

Pacman::Pacman()
{
    Pacman_x_pos = 252; //x9
    Pacman_y_pos = 420; //x15

    stepX = 0;
    stepY = 0;
    step = 7 * 2 * 2;

    x = &Pacman_x_pos;
    y = &Pacman_y_pos;

    game_map = new GameMap;
    game_map->LoadMap("map.txt");
}

Pacman::~Pacman()
{
    x = NULL;
    y = NULL;
    delete game_map;
}

int Pacman::getX()
{
    return *x;
}
int Pacman::getY()
{
    return *y;
}

void Pacman::Show(SDL_Renderer *des)
{
    if (input_type_.up_ == true || input_type_.right_ == true || input_type_.down_ == true || input_type_.left_ == true)
    {
        frame_++;
    }

    if (*x > SCREEN_WIDTH)
        *x = 0;
    else if (*y > SCREEN_HEIGHT)
        *y = 0;
    else if (*x < 0)
        *x = SCREEN_WIDTH;
    else if (*y < 0)
        *y = SCREEN_HEIGHT;

    if (this->flag_dead == false)
    {

        switch (status_)
        {
        case MOVE_UP:
        {
            p_clip = &upPacman[frame_ % 2];
            break;
        }

        case MOVE_DOWN:
        {
            p_clip = &downPacman[frame_ % 2];
            break;
        }
        case MOVE_LEFT:
        {
            p_clip = &leftPacman[frame_ % 2];
            break;
        }
        case MOVE_RIGHT:
        {
            p_clip = &rightPacman[frame_ % 2];
            break;
        }
        default:
        {
            p_clip = &leftPacman[frame_ % 2];
            break;
        }
        }
        
        renderTexture(p_object, des, p_rect.x, p_rect.y, PACMAN_SIZE, PACMAN_SIZE);
    }
    // else{
    //     for (int i = 0; i < 7; i++){
    //         p_clip = &deadPacman[i];
    //         renderTexture(p_object, des, p_rect.x, p_rect.y, PACMAN_SIZE, PACMAN_SIZE);

    //     }
    // }
}
void Pacman::Show(SDL_Renderer *des, int index)
{
    p_clip = &deadPacman[index];
    renderTexture(p_object, des, p_rect.x, p_rect.y, PACMAN_SIZE, PACMAN_SIZE);
}

bool Pacman::leftable(int x_pos, int y_pos)
{
    if (g_tile[(y_pos + 1) / TILE_SIZE][(x_pos - 1) / 28] == 1 ||
        g_tile[(y_pos + TILE_SIZE - 1) / TILE_SIZE][(x_pos - 1) / 28] == 1)
    {
        return false;
    }
    return true;
}
bool Pacman::rightable(int x_pos, int y_pos)
{
    if (g_tile[(y_pos + 1) / TILE_SIZE][(x_pos + TILE_SIZE + 1) / 28] == 1 ||
        g_tile[(y_pos + TILE_SIZE - 1) / TILE_SIZE][(x_pos + TILE_SIZE + 1) / 28] == 1)
    {
        return false;
    }
    return true;
}
bool Pacman::downable(int x_pos, int y_pos)
{
    if (g_tile[(y_pos + TILE_SIZE + 1) / TILE_SIZE][(x_pos + 1) / 28] == 1 ||
        g_tile[(y_pos + TILE_SIZE + 1) / TILE_SIZE][(x_pos + TILE_SIZE - 1) / 28] == 1)
    {
        return false;
    }
    return true;
}
bool Pacman::upable(int x_pos, int y_pos)
{
    if (g_tile[(y_pos - 1) / TILE_SIZE][(x_pos + 1) / 28] == 1 ||
        g_tile[(y_pos - 1) / TILE_SIZE][(x_pos + TILE_SIZE - 1) / 28] == 1)
    {
        return false;
    }
    return true;
}

void Pacman::HandleInputAction(SDL_Event events, SDL_Renderer *screen)
{
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (this->leftable(this->getX(), this->getY()) == true)
            {

                stepX = -step;
                stepY = 0;
                status_ = MOVE_LEFT;
                input_type_.left_ = 1;
                break;
            }
            else
            {
                break;
            }
        case SDLK_RIGHT:
            if (this->rightable(this->getX(), this->getY()) == true)
            {
                stepX = step;
                stepY = 0;
                status_ = MOVE_RIGHT;
                input_type_.right_ = 1;
                break;
            }
            else
            {
                break;
            }
        case SDLK_DOWN:
            if (this->downable(this->getX(), this->getY()) == true)
            {
                stepY = step;
                stepX = 0;
                status_ = MOVE_DOWN;
                input_type_.down_ = 1;
                break;
            }
            else
            {
                break;
            }
        case SDLK_UP:
            if (this->upable(this->getX(), this->getY()) == true)
            {
                stepY = -step;
                stepX = 0;
                status_ = MOVE_UP;
                input_type_.up_ = 1;
                break;
            }
            else
            {
                break;
            }
        }
    }
    else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (this->leftable(this->getX(), this->getY()) == true)
            {

                stepX = -step;
                stepY = 0;
                status_ = MOVE_LEFT;
                input_type_.left_ = 1;
                break;
            }
            else
            {
                break;
            }
        case SDLK_RIGHT:
            if (this->rightable(this->getX(), this->getY()) == true)
            {
                stepX = step;
                stepY = 0;
                status_ = MOVE_RIGHT;
                input_type_.right_ = 1;
                break;
            }
            else
            {
                break;
            }
        case SDLK_DOWN:
            if (this->downable(this->getX(), this->getY()) == true)
            {
                stepY = step;
                stepX = 0;
                status_ = MOVE_DOWN;
                input_type_.down_ = 1;
                break;
            }
            else
            {
                break;
            }
        case SDLK_UP:
            if (this->upable(this->getX(), this->getY()) == true)
            {
                stepY = -step;
                stepX = 0;
                status_ = MOVE_UP;
                input_type_.up_ = 1;
                break;
            }
            else
            {
                break;
            }
        }
    }
}

void Pacman::setClips()
{
    if (width_frame_ > 0 && hight_frame_ > 0)
    {
        upPacman[0].x = width_frame_ * 2;
        upPacman[0].y = hight_frame_;
        upPacman[0].w = width_frame_;
        upPacman[0].h = hight_frame_;

        upPacman[1].x = width_frame_ * 3;
        upPacman[1].y = hight_frame_;
        upPacman[1].w = width_frame_;
        upPacman[1].h = hight_frame_;

        downPacman[0].x = width_frame_ * 2;
        downPacman[0].y = 0;
        downPacman[0].w = width_frame_;
        downPacman[0].h = hight_frame_;

        downPacman[1].x = width_frame_ * 3;
        downPacman[1].y = 0;
        downPacman[1].w = width_frame_;
        downPacman[1].h = hight_frame_;

        rightPacman[0].x = width_frame_ * 0;
        rightPacman[0].y = hight_frame_;
        rightPacman[0].w = width_frame_;
        rightPacman[0].h = hight_frame_;

        rightPacman[1].x = width_frame_ * 1;
        rightPacman[1].y = hight_frame_;
        rightPacman[1].w = width_frame_;
        rightPacman[1].h = hight_frame_;

        leftPacman[0].x = width_frame_ * 0;
        leftPacman[0].y = 0;
        leftPacman[0].w = width_frame_;
        leftPacman[0].h = hight_frame_;

        leftPacman[1].x = width_frame_ * 1;
        leftPacman[1].y = 0;
        leftPacman[1].w = width_frame_;
        leftPacman[1].h = hight_frame_;

        deadPacman[0] = {width_frame_ * 0, hight_frame_ * 2, width_frame_, hight_frame_};
        deadPacman[1] = {width_frame_ * 1, hight_frame_ * 2, width_frame_, hight_frame_};
        deadPacman[2] = {width_frame_ * 2, hight_frame_ * 2, width_frame_, hight_frame_};
        deadPacman[3] = {width_frame_ * 3, hight_frame_ * 2, width_frame_, hight_frame_};
        deadPacman[4] = {width_frame_ * 0, hight_frame_ * 3, width_frame_, hight_frame_};
        deadPacman[5] = {width_frame_ * 1, hight_frame_ * 3, width_frame_, hight_frame_};
        deadPacman[6] = {width_frame_ * 2, hight_frame_ * 3, width_frame_, hight_frame_};
        deadPacman[7] = {width_frame_ * 3, hight_frame_ * 3, width_frame_, hight_frame_};
    }
}
bool Pacman::_LoadImg(std::string path, SDL_Renderer *screen)
{

    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame_ = p_rect.w / 4;
        hight_frame_ = p_rect.h / 4;
    }
    return ret;
}

bool Pacman::checkCollisionWith(std::vector<SDL_Rect> &a)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftB = this->getX();
    rightB = leftB + TILE_SIZE;
    topB = this->getY();
    bottomB = topB + TILE_SIZE;

    for (int Abox = 0; Abox < a.size(); Abox++)
    {
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        bottomA = a[Abox].y + a[Abox].h;

        if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
        {
            return true;
        }
    }

    return false;
}
bool Pacman::checkCollisionWithPoint(std::vector<SDL_Rect> &a) // thừa
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftB = this->getX();
    rightB = leftB + PACMAN_SIZE;
    topB = this->getY();
    bottomB = topB + PACMAN_SIZE;

    for (int Abox = 0; Abox < a.size(); Abox++)
    {
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        bottomA = a[Abox].y + a[Abox].h;

        if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
        {
            return true;
        }
    }
    return false;
}
bool Pacman::checkCollisionWithEachGhost(SDL_Rect a)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftB = this->getX();
    rightB = leftB + PACMAN_SIZE;
    topB = this->getY();
    bottomB = topB + PACMAN_SIZE;

    
    {
        leftA = a.x;
        rightA = a.x + a.w;
        topA = a.y;
        bottomA = a.y + a.h;

        if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
        {
            return true;
        }
    }
    return false;
}

void Pacman::move(std::vector<SDL_Rect> &otherColliders)
{
    *x += stepX;
    p_rect.x = *x;
    if ((*x < 0) || (*x + PACMAN_SIZE > SCREEN_WIDTH) || checkCollisionWith(otherColliders))
    {
        *x -= stepX;
        p_rect.x = *x;
    }

    *y += stepY;
    p_rect.y = *y;

    if ((*y < 0) || (*y + PACMAN_SIZE > SCREEN_HEIGHT) || checkCollisionWith(otherColliders))
    {
        *y -= stepY;
        p_rect.y = *y;
    }
}

void Pacman::setFlagDead(bool flag_)
{
    this->flag_dead = flag_;
}
bool Pacman::getFlagDead()
{
    return this->flag_dead;
}
void Pacman::setPos(int x_pos, int y_pos){
    *x = x_pos;
    *y = y_pos;

}
void Pacman::setSatus(){
    // stepX = 0;
    // stepY = 0;
    // this->status_ = NO_MOVE;
}
void Pacman::setFlagEatBigPoint(bool flag_){
    this->flag_eat_big_point = flag_;
}
bool Pacman::getFlagEatBigPoint(){
    return this->flag_eat_big_point;
}
