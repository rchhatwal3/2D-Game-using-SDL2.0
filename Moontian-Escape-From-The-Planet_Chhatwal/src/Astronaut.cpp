/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/Astronaut.h"

Astronaut::Astronaut(const char* name, int x, int y, int w, int h, int Max_Width)
{
    srand(5);

    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    spriteImageWidth = Max_Width;

    angle = 0.0;
    objOrientation = SDL_FLIP_NONE;

    obj_TargetRect.h = height;
    obj_TargetRect.w = width;
    obj_TargetRect.x = x_pos;
    obj_TargetRect.y = rand() % SCREEN_HEIGHT + 1;

    obj_SpriteRect.h = height;
    obj_SpriteRect.w = width;
    obj_SpriteRect.x = 0;
    obj_SpriteRect.y = 0;

    ObjSurface = IMG_Load(name);
}

Astronaut::~Astronaut()
{
}

void Astronaut::setPlayerState(int enum_index)
{
    switch (enum_index)
    {
    case 1:
        state = StateMachine::UP;
        break;
    
    case 2:
        state = StateMachine::DOWN;
        break;

    case 3:
        state = StateMachine::LEFT;
        break;

    case 4:
        state = StateMachine::RIGHT;
        break;

    case 5:
        state = StateMachine::IDLE;
        break;    
    }
}

void Astronaut::setPlayerState(StateMachine value)
{
   state = value;
}

void Astronaut::updateAstronaut()
{
    switch (Astronaut::state)
    {
    case StateMachine::UP:
        objOrientation = SDL_FLIP_NONE;
        angle = 270;

        if ((y_pos - PLAYER_VEL) > GAME_BOUND_LOWER_Y)
        {
            y_pos -= PLAYER_VEL;
        }

        else y_pos = GAME_BOUND_LOWER_Y;

        if (obj_SpriteRect.x + obj_SpriteRect.w > spriteImageWidth) obj_SpriteRect.x = 0;
        else obj_SpriteRect.x+=obj_SpriteRect.w; 
        break;
    
    case StateMachine::DOWN:
        objOrientation = SDL_FLIP_NONE;
        angle = 90;

        if ((y_pos + PLAYER_VEL) < GAME_BOUND_UPPER_Y)
        {
            y_pos += PLAYER_VEL;
        }

        else y_pos = GAME_BOUND_UPPER_Y;

        if (obj_SpriteRect.x + obj_SpriteRect.w > spriteImageWidth) obj_SpriteRect.x = 0;
        else obj_SpriteRect.x+=obj_SpriteRect.w; 

        break;

    case StateMachine::LEFT:
        objOrientation = SDL_FLIP_HORIZONTAL;
        angle = 0;

        if ((x_pos - PLAYER_VEL) > GAME_BOUND_LEFT_X)
        {
            x_pos -= PLAYER_VEL;
        }

        else x_pos = GAME_BOUND_LEFT_X;

        if (obj_SpriteRect.x + obj_SpriteRect.w > spriteImageWidth) obj_SpriteRect.x = 0;
        else obj_SpriteRect.x+=obj_SpriteRect.w; 

        break;

    case StateMachine::RIGHT:
        objOrientation = SDL_FLIP_NONE;
        angle = 0;

        if ((x_pos + PLAYER_VEL) < GAME_BOUND_RIGHT_X)
        {
            x_pos += PLAYER_VEL;
        }

        else x_pos = GAME_BOUND_RIGHT_X;

        if (obj_SpriteRect.x + obj_SpriteRect.w > spriteImageWidth) obj_SpriteRect.x = 0;
        else obj_SpriteRect.x+=obj_SpriteRect.w; 

        break;

    case StateMachine::IDLE: //IDLE CASE
        objOrientation = SDL_FLIP_NONE;
        angle = 0;
        obj_SpriteRect.x = 0;
        break;

    case StateMachine::DEAD:
        break;
    }

    obj_TargetRect.x = x_pos;
    obj_TargetRect.y = y_pos;
    obj_TargetRect.w = width;
    obj_TargetRect.h = height;
}

void Astronaut::renderAstronaut(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopyEx(ren, game_texture, &obj_SpriteRect, &obj_TargetRect, angle, NULL, objOrientation);
    SDL_DestroyTexture(game_texture);
}

void Astronaut::quitObj()
{
    SDL_FreeSurface(ObjSurface);
    delete(this);
}

SDL_Rect& Astronaut::getScreenRect()
{
    return obj_TargetRect;
}