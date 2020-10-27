/***********************
 *Ramneek Chhatwal
 *rchhatw
 *Assignment 3
 **********************/

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

class Background
{
private:
    int x_pos, y_pos, width, height;

    SDL_Rect obj_TargetRect;
    SDL_Surface* ObjSurface;

public:
    Background(const char* name, int x, int y, int w, int h);
    ~Background();

    void renderBackground(SDL_Renderer* ren);
    void quitObj();
};

#endif