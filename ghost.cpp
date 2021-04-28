#include "ghost.h"

Ghost::Ghost()
{
    srand((int)time(0));
    //flag = false;
    //waifu = false;
    x = &Ghost_x_pos;
    y = &Ghost_y_pos;
    step = STEP;
    flag_when_pac_eat_big = false;
    flag_pac_eat_weak_ghost = false;
}

Ghost::~Ghost()
{
    x = NULL;
    y = NULL;
}
int Ghost::getX()
{
    return *x;
}
int Ghost::getY()
{
    return *y;
}


void Ghost::Show(SDL_Renderer *des)
{
    if (input_type_.up_ == true || input_type_.right_ == true || input_type_.down_ == true || input_type_.left_ == true)
    {
        frame_++;
    }

    if (*x < 0){
        *x = SCREEN_WIDTH - TILE_SIZE;
    }
    
    if (*x + GHOST_SIZE > SCREEN_WIDTH){
        *x = 0;
    }

    //alive
    if (flag_when_pac_eat_big == false)
    {

        switch (status_)
        {
        case MOVE_UP:
        {
            p_clip = &upGhost[frame_ % 2];
        }
        break;
        case MOVE_DOWN:
        {
            p_clip = &downGhost[frame_ % 2];
        }
        break;
        case MOVE_LEFT:
        {
            p_clip = &leftGhost[frame_ % 2];
        }
        break;
        case MOVE_RIGHT:
        {
            p_clip = &rightGhost[frame_ % 2];
        }
        break;
        }
        renderTexture(p_object, des, p_rect.x, p_rect.y, GHOST_SIZE, GHOST_SIZE);
        //SDL_RenderPresent(des);
    }
    else if (flag_when_pac_eat_big == true && flag_pac_eat_weak_ghost == false)
    {
        switch (status_)
        {
            case MOVE_UP:
            {
                p_clip = &weakGhostBlue[frame_ % 2];
            }
            break;
            case MOVE_DOWN:
            {
                p_clip = &weakGhostBlue[frame_ % 2];
            }
            break;
            case MOVE_LEFT:
            {
                p_clip = &weakGhostBlue[frame_ % 2];
            }
            break;
            case MOVE_RIGHT:
            {
                p_clip = &weakGhostBlue[frame_ % 2];
            }
        }
        renderTexture(p_object, des, p_rect.x, p_rect.y, GHOST_SIZE, GHOST_SIZE);
    }else if (flag_when_pac_eat_big == true && flag_when_pac_eat_big == true){
        switch (status_)
        {
        case MOVE_UP:
        {
            p_clip = &upGhost[3];
        }
        break;
        case MOVE_DOWN:
        {
            p_clip = &downGhost[3];
        }
        break;
        case MOVE_LEFT:
        {
            p_clip = &leftGhost[3];
        }
        break;
        case MOVE_RIGHT:
        {
            p_clip = &rightGhost[3];
        }
        break;
        }
        renderTexture(p_object, des, p_rect.x, p_rect.y, GHOST_SIZE, GHOST_SIZE);
    }
}

void Ghost::setClips()
{
    if (width_frame_ > 0 && hight_frame_ > 0)
    {
        upGhost[0].x = width_frame_ * 0;
        upGhost[0].y = hight_frame_ * 0;
        upGhost[0].w = width_frame_;
        upGhost[0].h = hight_frame_;

        upGhost[1].x = width_frame_ * 1;
        upGhost[1].y = hight_frame_ * 0;
        upGhost[1].w = width_frame_;
        upGhost[1].h = hight_frame_;

        upGhost[2].x = width_frame_ * 0;
        upGhost[2].y = hight_frame_ * 3;
        upGhost[2].w = width_frame_;
        upGhost[2].h = hight_frame_;

        downGhost[0].x = width_frame_ * 2;
        downGhost[0].y = 0;
        downGhost[0].w = width_frame_;
        downGhost[0].h = hight_frame_;

        downGhost[1].x = width_frame_ * 3;
        downGhost[1].y = 0;
        downGhost[1].w = width_frame_;
        downGhost[1].h = hight_frame_;

        downGhost[2].x = width_frame_ * 1;
        downGhost[2].y = hight_frame_ * 3;
        downGhost[2].w = width_frame_;
        downGhost[2].h = hight_frame_;

        rightGhost[0].x = width_frame_ * 0;
        rightGhost[0].y = hight_frame_;
        rightGhost[0].w = width_frame_;
        rightGhost[0].h = hight_frame_;

        rightGhost[1].x = width_frame_ * 1;
        rightGhost[1].y = hight_frame_;
        rightGhost[1].w = width_frame_;
        rightGhost[1].h = hight_frame_;

        rightGhost[2].x = width_frame_ * 3;
        rightGhost[2].y = hight_frame_ * 3;
        rightGhost[2].w = width_frame_;
        rightGhost[2].h = hight_frame_;

        leftGhost[0].x = width_frame_ * 2;
        leftGhost[0].y = hight_frame_ * 1;
        leftGhost[0].w = width_frame_;
        leftGhost[0].h = hight_frame_;

        leftGhost[1].x = width_frame_ * 3;
        leftGhost[1].y = hight_frame_ * 1;
        leftGhost[1].w = width_frame_;
        leftGhost[1].h = hight_frame_;

        leftGhost[2].x = width_frame_ * 2;
        leftGhost[2].y = hight_frame_ * 3;
        leftGhost[2].w = width_frame_;
        leftGhost[2].h = hight_frame_;

        weakGhostBlue[0] = {0, hight_frame_ * 2, width_frame_, hight_frame_};
        weakGhostBlue[1] = {width_frame_, hight_frame_ * 2, width_frame_, hight_frame_};
        weakGhostWhite[0] = {width_frame_ * 2, hight_frame_ * 2, width_frame_, hight_frame_};
        weakGhostWhite[1] = {width_frame_ * 3, hight_frame_ * 2, width_frame_, hight_frame_};

        
    }
}

void Ghost::Action()
{
    int n = rand() % 4;

    switch (n)
    {
    case 0:
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
    case 1:
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
    case 2:
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
    case 3:
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


bool Ghost::leftable(const int &x_pos, const int &y_pos)
{
    if (g_tile[(y_pos + 1) / TILE_SIZE][(x_pos - 1) / 28] == 1 ||
        g_tile[(y_pos + TILE_SIZE - 1) / TILE_SIZE][(x_pos - 1) / 28] == 1)
    {
        return false;
    }
    return true;
}
bool Ghost::rightable(const int &x_pos, const int &y_pos)
{
    if (g_tile[(y_pos + 1) / TILE_SIZE][(x_pos + TILE_SIZE + 1) / 28] == 1 ||
        g_tile[(y_pos + TILE_SIZE - 1) / TILE_SIZE][(x_pos + TILE_SIZE + 1) / 28] == 1)
    {
        return false;
    }
    return true;
}
bool Ghost::downable(const int &x_pos, const int &y_pos)
{
    if (g_tile[(y_pos + TILE_SIZE + 1) / TILE_SIZE][(x_pos + 1) / 28] == 1 ||
        g_tile[(y_pos + TILE_SIZE + 1) / TILE_SIZE][(x_pos + TILE_SIZE - 1) / 28] == 1)
    {
        return false;
    }
    return true;
}
bool Ghost::upable(const int &x_pos, const int &y_pos)
{
    if (g_tile[(y_pos - 1) / TILE_SIZE][(x_pos + 1) / 28] == 1 ||
        g_tile[(y_pos - 1) / TILE_SIZE][(x_pos + TILE_SIZE - 1) / 28] == 1)
    {
        return false;
    }
    return true;
}
bool Ghost::_LoadImg(const std::string &path, SDL_Renderer *screen)
{

    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame_ = p_rect.w / 4;
        hight_frame_ = p_rect.h / 4;
    }
    return ret;
}

bool Ghost::checkCollision(std::vector<SDL_Rect> &a)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    SDL_Rect b;

    leftB = this->getX();
    rightB = leftB + GHOST_SIZE;
    topB = this->getY();
    bottomB = topB + GHOST_SIZE;

    //Go through the A boxes
    for (int Abox = 0; Abox < a.size(); Abox++)
    {
        //Calculate the sides of rect A
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

void Ghost::move(std::vector<SDL_Rect> &otherColliders)
{
    //Move the dot left or right
    *x += stepX;
    //shiftColliders();
    p_rect.x = *x;
    //If the dot collided or went too far to the left or right
    if ((*x < 0) || (*x + GHOST_SIZE > SCREEN_WIDTH) || checkCollision(otherColliders))
    {
        //Move back
        *x -= stepX;
        p_rect.x = *x;
        //shiftColliders();
    }

    //Move the dot up or down
    *y += stepY;
    p_rect.y = *y;
    //shiftColliders();

    //If the dot collided or went too far up or down
    if ((*y < 0) || (*y + GHOST_SIZE > SCREEN_HEIGHT) || checkCollision(otherColliders))
    {
        //Move back
        *y -= stepY;
        p_rect.y = *y;
        //shiftColliders();
    }
}

void Ghost::setPos(const int &x_, const int &y_)
{
    *x = x_;
    *y = y_;
}

SDL_Rect Ghost::getRect(){
    p_rect = {*x, *y, GHOST_SIZE, GHOST_SIZE};
    return this->p_rect;
}

void Ghost::setFlagEatWeakGhost(const bool &flag_){
    this->flag_pac_eat_weak_ghost = flag_;
}

bool Ghost::getFlagEatWeakGhost(){
    return this->flag_pac_eat_weak_ghost;
}
void Ghost::setSTEPWhenDead(){
    if (this->step == STEP){
        step = STEP/2;
    }
}
void Ghost::setSTEPWhenALive(){
    if (this->step != STEP){
        step = STEP;
    }
}

void Ghost::setFlagWhenPacEatBig(const bool &flag_)
{
    this->flag_when_pac_eat_big = flag_;
}
bool Ghost::getFlagWhenPacEatBig(){
    return this->flag_when_pac_eat_big;
}