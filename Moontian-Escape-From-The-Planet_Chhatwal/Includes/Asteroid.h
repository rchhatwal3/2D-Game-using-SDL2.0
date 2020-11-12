/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef ASTEROID_H
#define ASTEROID_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

class Asteroid
{
private:
    int x_pos, y_pos, width, height;
    SDL_Rect obj_TargetRect;
    SDL_Rect obj_SpriteRect;

    SDL_Surface* ObjSurface;

    int spriteImageWidth;

    SDL_RendererFlip objOrientation;

public:
    Asteroid(const char* name, int x, int y, int w, int h, int Max_Width);
    ~Asteroid();

    void updateAsteroid();
    void renderAsteroid(SDL_Renderer* ren);
    SDL_Rect& getScreenRect();
    void quitObj();
};

#endif