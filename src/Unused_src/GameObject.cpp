#include "../Includes/Unused_Includes/GameObject.h"
#include <iostream>

GameObject::GameObject(const char* name, int x, int y, int w, int h)
{
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    angle = 0.0;
    objOrientation = SDL_FLIP_NONE;

    obj_TargetRect.h = height;
    obj_TargetRect.w = width;
    obj_TargetRect.x = x_pos;
    obj_TargetRect.y = y_pos;

    obj_SpriteRect.h = height;
    obj_SpriteRect.w = width;
    obj_SpriteRect.x = 0;
    obj_SpriteRect.y = 0;

    ObjSurface = IMG_Load(name);
    
}

GameObject::~GameObject()
{
}

void GameObject::setPlayerState(StateMachine new_state)
{
    state = new_state;
}

void GameObject::setMaxImageWidth(int max_w)
{
    spriteImageWidth = max_w;
}

void GameObject::updateAsteroid()
{
    if (obj_SpriteRect.x + obj_SpriteRect.w > spriteImageWidth) obj_SpriteRect.x = 0;
    else obj_SpriteRect.x+=obj_SpriteRect.w; 

    if ((x_pos - ASTEROID_VEL) < GAME_BOUND_LEFT_X) x_pos = SCREEN_WIDTH;
    else x_pos -= ASTEROID_VEL;

    obj_TargetRect.x = x_pos;
}

void GameObject::renderBackground(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopy(ren, game_texture, NULL, &obj_TargetRect);
}

void GameObject::renderSprite(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopyEx(ren, game_texture, &obj_SpriteRect, &obj_TargetRect, angle, NULL, objOrientation);
}

void GameObject::quitObj()
{
    delete(this);
}

int GameObject::obj_get_x_pos()
{
    return x_pos;
}
    
void GameObject::obj_set_x_pos(int pos)
{
    x_pos = pos;
}

int GameObject::obj_get_y_pos()
{
    return y_pos;
}
    
void GameObject::obj_set_y_pos(int pos)
{
    y_pos = pos;
}

SDL_Rect& GameObject::get_ScreenRect()
{
    return obj_TargetRect;
}