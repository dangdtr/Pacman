#include "ghost.h"


Ghost::Ghost()
{
    srand((int)time(0));
    //flag = false;
    //waifu = false;
    x = &Ghost_x_pos;
    y = &Ghost_y_pos;
}

Ghost::~Ghost()
{
    x = NULL;
    y = NULL;
}
int Ghost::getX(){
    return *x;
}
int Ghost::getY(){
    return *y;
}

void Ghost::Show(SDL_Renderer *des)
{
    if (input_type_.up_ == true || input_type_.right_ == true || input_type_.down_ == true || input_type_.left_ == true){
        frame_ ++;
    }


    if (*x > SCREEN_WIDTH) *x = 0;// - width_frame_;
    else if (*y > SCREEN_HEIGHT) *y = 0;// - hight_frame_;
    else if (*x < 0) *x = SCREEN_WIDTH;
    else if (*y < 0) *y = SCREEN_HEIGHT;

    switch (status_){
        case MOVE_UP:{
            p_clip = &upGhost[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,GHOST_SIZE,GHOST_SIZE);
            }
            break;
        case MOVE_DOWN:{
            p_clip = &downGhost[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,GHOST_SIZE,GHOST_SIZE);
            }
            break;
        case MOVE_LEFT:{
            p_clip = &leftGhost[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,GHOST_SIZE,GHOST_SIZE);
            }
            break;
        case MOVE_RIGHT:{
            p_clip = &rightGhost[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,GHOST_SIZE,GHOST_SIZE);
            }
            break;
    }
}




void Ghost::setClips(){
    if (width_frame_ > 0 && hight_frame_ > 0){
        upGhost[0].x = width_frame_ * 2;
        upGhost[0].y = hight_frame_ ;
        upGhost[0].w =  width_frame_;
        upGhost[0].h = hight_frame_ ;

        upGhost[1].x = width_frame_ * 3;
        upGhost[1].y = hight_frame_ ;
        upGhost[1].w =  width_frame_;
        upGhost[1].h = hight_frame_ ;

        downGhost[0].x = width_frame_ * 2;
        downGhost[0].y = 0;
        downGhost[0].w = width_frame_;
        downGhost[0].h = hight_frame_;

        downGhost[1].x = width_frame_ * 3;
        downGhost[1].y = 0;
        downGhost[1].w = width_frame_;
        downGhost[1].h = hight_frame_;

        rightGhost[0].x = width_frame_ * 0;
        rightGhost[0].y = hight_frame_;
        rightGhost[0].w = width_frame_;
        rightGhost[0].h = hight_frame_;

        rightGhost[1].x = width_frame_ * 1;
        rightGhost[1].y = hight_frame_;
        rightGhost[1].w = width_frame_;
        rightGhost[1].h = hight_frame_;

        leftGhost[0].x = width_frame_ * 0;
        leftGhost[0].y = 0;
        leftGhost[0].w = width_frame_;
        leftGhost[0].h = hight_frame_;

        leftGhost[1].x = width_frame_ * 1;
        leftGhost[1].y = 0;
        leftGhost[1].w = width_frame_;
        leftGhost[1].h = hight_frame_;
    }
}

void Ghost::Action()
{
    int n = rand()%8;

    switch (n)
    {
    case 1:
        stepY = -step;
        stepX = 0;
        status_ = MOVE_UP;
        input_type_.up_ = 1;
        break;

    case 3:
        stepX = -step;
        stepY = 0;
        status_ = MOVE_LEFT;
        input_type_.left_ = 1;
        break;
    case 5:
        stepY = step;
        stepX = 0;
        status_ = MOVE_DOWN;
        input_type_.down_ = 1;
        break;
    case 7:
        stepX = step;
        stepY = 0;
        status_ = MOVE_RIGHT;
        input_type_.right_ = 1;
        break;
    }
}

bool Ghost::_LoadImg(std::string path, SDL_Renderer* screen){

    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true){
        width_frame_ = p_rect.w /4;
        hight_frame_ = p_rect.h/4;
    }
    return ret;
}

bool Ghost::checkCollision( std::vector<SDL_Rect>& a)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    SDL_Rect b;

    leftB = this->getX();
    rightB = leftB + PACMAN_SIZE;
    topB = this->getY();
    bottomB = topB + PACMAN_SIZE;

    //Go through the A boxes
    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        //Calculate the sides of rect A
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;
            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                return true;
            }

    }
    return false;
}

void Ghost::move( std::vector<SDL_Rect>& otherColliders )
{
    //Move the dot left or right
    *x += stepX;
    //shiftColliders();
    p_rect.x =  *x;
    //If the dot collided or went too far to the left or right
    if( ( *x < 0 ) || ( *x + PACMAN_SIZE > SCREEN_WIDTH ) || checkCollision(otherColliders ) )
    {
        //Move back
        *x -= stepX;
        p_rect.x =  *x;
        //shiftColliders();
    }

    //Move the dot up or down
    *y += stepY;
    p_rect.y = *y;
    //shiftColliders();

    //If the dot collided or went too far up or down
    if( ( *y < 0 ) || ( *y + PACMAN_SIZE > SCREEN_HEIGHT ) || checkCollision(otherColliders ) )
    {
        //Move back
        *y -= stepY;
        p_rect.y = *y;
        //shiftColliders();
    }
}

void Ghost::setPos(int x_, int y_){
    *x = x_;
    *y = y_;
}