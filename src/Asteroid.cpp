/***********************
 *Ramneek Chhatwal
 *rchhatw
 *Assignment 3
 **********************/

#include "../Includes/Asteroid.h"

Asteroid::Asteroid(const char* name, int x, int y, int w, int h, int Max_Width)
{
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    spriteImageWidth = Max_Width;

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

Asteroid::~Asteroid()
{
}

void Asteroid::updateAsteroid()
{
    if (obj_SpriteRect.x + obj_SpriteRect.w > spriteImageWidth) obj_SpriteRect.x = 0;
    else obj_SpriteRect.x+=obj_SpriteRect.w; 

    if ((x_pos - ASTEROID_VEL) < GAME_BOUND_LEFT_X) x_pos = SCREEN_WIDTH;
    else x_pos -= ASTEROID_VEL;

    obj_TargetRect.x = x_pos;
}

void Asteroid::renderAsteroid(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopyEx(ren, game_texture, &obj_SpriteRect, &obj_TargetRect, 0.0, NULL, objOrientation);
    SDL_DestroyTexture(game_texture);
}

void Asteroid::quitObj()
{
    SDL_FreeSurface(ObjSurface);
    delete(this);
}