#include "../Includes/Rocket.h"
#include <iostream>

Rocket::Rocket(const char* name, int w, int h, int Max_Width, int Max_Height)
{
    srand(5);

    numRockets = 0;

    x_pos = rand() % SCREEN_WIDTH + 1;
    y_pos = rand() % SCREEN_HEIGHT + 1;
    width = w;
    height = h;
    spriteImageWidth = Max_Width;
    spriteImageHeight = Max_Height;

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

Rocket::~Rocket()
{
}

int Rocket::getNumRockets()
{
    return numRockets;
}

bool Rocket::update()
{
    //only going into this function if the player retrieves a rocket
    if (numRockets < MAX_LEVEL_ROCKETS - 1)
    {
        numRockets++;
        if (obj_SpriteRect.x + obj_SpriteRect.w > spriteImageWidth - 1)
        {
            obj_SpriteRect.x = 0;
            if (obj_SpriteRect.y + obj_SpriteRect.h > spriteImageHeight - 1) obj_SpriteRect.y = 0;
            else obj_SpriteRect.y += obj_SpriteRect.h;
        }
        else obj_SpriteRect.x+=obj_SpriteRect.w;

        obj_TargetRect.x = rand() % (SCREEN_WIDTH - obj_TargetRect.w);
        obj_TargetRect.y = rand() % (SCREEN_HEIGHT - obj_TargetRect.h);
        //returning to represent if the user has not won yet and the game is still going
        return false;
    }
    //returning to represent if the user has won
    return true;
}

void Rocket::render(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopyEx(ren, game_texture, &obj_SpriteRect, &obj_TargetRect, 0.0, NULL, objOrientation);
    SDL_DestroyTexture(game_texture);
}

SDL_Rect& Rocket::getScreenRect()
{
    return obj_TargetRect;
}

void Rocket::destroy()
{
    SDL_FreeSurface(ObjSurface);
    delete(this);
}
