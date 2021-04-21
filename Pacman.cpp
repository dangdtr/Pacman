#include "Pacman.h"

Pacman::Pacman()
{
    Pacman_x_pos = 476;
    Pacman_y_pos = 476;
    
    stepX = 0;
    stepY = 0;
    step = 14;

    x = &Pacman_x_pos;
    y = &Pacman_y_pos;

    game_map = new GameMap;
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
        frame_ ++;
    }

    if (*x > SCREEN_WIDTH) *x = 0;// - width_frame_;
    else if (*y > SCREEN_HEIGHT) *y = 0;// - hight_frame_;

    else if (*x < 0) *x = SCREEN_WIDTH;
    else if (*y < 0) *y = SCREEN_HEIGHT;


    if (this->checkCollisionWithWall(game_map->getColliders()) == false)

    switch (status_)
    {

    case MOVE_UP:
    {
        //if (this->checkCollisionWithWall(game_map->getColliders()) == false)
        {
            p_clip = &upPacman[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,PACMAN_SIZE,PACMAN_SIZE);//, p_clip->w, p_clip->h);
        }

    }

    break;
    case MOVE_DOWN:
    {
        //if (this->checkCollisionWithWall(game_map->getColliders()) == false)
        {
            p_clip = &downPacman[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,PACMAN_SIZE,PACMAN_SIZE);//, p_clip->w, p_clip->h);
        }
    }
    break;
    case MOVE_LEFT:
    {
        //if (this->checkCollisionWithWall(game_map->getColliders()) == false)
        {
            p_clip = &leftPacman[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,PACMAN_SIZE,PACMAN_SIZE);
        }

    }
    break;
    case MOVE_RIGHT:
    {
        //if (this->checkCollisionWithWall(game_map->getColliders()) == false)
        {
            p_clip = &rightPacman[frame_ % 2];
            renderTexture(p_object, des,p_rect.x, p_rect.y,PACMAN_SIZE,PACMAN_SIZE);
        }
    }
    break;
    default:
    {
        p_clip = &leftPacman[frame_ % 2];
        renderTexture(p_object, des,p_rect.x, p_rect.y,PACMAN_SIZE,PACMAN_SIZE);
        break;
    }
    }
}


void Pacman::HandleInputAction(SDL_Event events, SDL_Renderer *screen)
{
    if (events.type == SDL_KEYDOWN && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {

                stepX = -step;
                stepY = 0;
                status_ = MOVE_LEFT;
                input_type_.left_ = 1;
                break;
            }
        case SDLK_RIGHT:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {
                stepX = step;
                stepY = 0;
                status_ = MOVE_RIGHT;
                input_type_.right_ = 1;
                break;

            }
        case SDLK_DOWN:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {
                stepY = step;
                stepX = 0;
                status_ = MOVE_DOWN;
                input_type_.down_ = 1;
                break;

            }
        case SDLK_UP:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {
                stepY = -step;
                stepX = 0;
                status_ = MOVE_UP;
                input_type_.up_ = 1;
                break;

            }
        }
    }else if (events.type == SDL_KEYUP && events.key.repeat == 0)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_LEFT:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {

                stepX = -step;
                stepY = 0;
                status_ = MOVE_LEFT;
                input_type_.left_ = 1;
                break;
            }
        case SDLK_RIGHT:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {
                stepX = step;
                stepY = 0;
                status_ = MOVE_RIGHT;
                input_type_.right_ = 1;
                break;

            }
        case SDLK_DOWN:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {
                stepY = step;
                stepX = 0;
                status_ = MOVE_DOWN;
                input_type_.down_ = 1;
                break;

            }
        case SDLK_UP:
            if (this->checkCollisionWithWall(game_map->getColliders()) == false)
            {
                stepY = -step;
                stepX = 0;
                status_ = MOVE_UP;
                input_type_.up_ = 1;
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
        upPacman[0].y = hight_frame_ ;
        upPacman[0].w =  width_frame_;
        upPacman[0].h = hight_frame_ ;

        upPacman[1].x = width_frame_ * 3;
        upPacman[1].y = hight_frame_ ;
        upPacman[1].w =  width_frame_;
        upPacman[1].h = hight_frame_ ;

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
    }
}
bool Pacman::_LoadImg(std::string path, SDL_Renderer* screen)
{

    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true)
    {
        width_frame_ = p_rect.w/4;
        hight_frame_ = p_rect.h/4;
    }
    return ret;
}

bool Pacman::checkCollisionWithWall( std::vector<SDL_Rect>& a)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


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

        //Go through the B boxes
        //for( int Bbox = 0; Bbox < b.size(); Bbox++ )

        //Calculate the sides of rect B


        //If no sides from A are outside of B
        if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
        {
            //A collision is detected
            return true;
        }

    }

    //If neither set of collision boxes touched
    return false;
}
bool Pacman::checkCollisionWithPoint( std::vector<SDL_Rect>& a)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


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

        //Go through the B boxes
        //for( int Bbox = 0; Bbox < b.size(); Bbox++ )

        //Calculate the sides of rect B


        //If no sides from A are outside of B
        if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
        {
            //A collision is detected
            return true;
        }

    }

    //If neither set of collision boxes touched
    return false;
}

void Pacman::move( std::vector<SDL_Rect>& otherColliders )
{
    //Move the dot left or right
    *x += stepX;
    //shiftColliders();
    p_rect.x =  *x;
    //If the dot collided or went too far to the left or right
    if( ( *x < 0 ) || ( *x + PACMAN_SIZE > SCREEN_WIDTH ) || checkCollisionWithWall(otherColliders ) )
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
    if( ( *y < 0 ) || ( *y + PACMAN_SIZE > SCREEN_HEIGHT ) || checkCollisionWithWall(otherColliders ) )
    {
        //Move back
        *y -= stepY;
        p_rect.y = *y;
        //shiftColliders();
    }
}
