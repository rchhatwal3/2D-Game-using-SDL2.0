/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef ROCKET_H
#define ROCKET_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

class Rocket
{
private:
    int numRockets;
    int x_pos, y_pos, width, height;
    int spriteImageWidth;
    int spriteImageHeight;

    SDL_Rect obj_TargetRect;
    SDL_Rect obj_SpriteRect;
    SDL_Surface* ObjSurface;
    SDL_RendererFlip objOrientation;

public:
    Rocket(const char* name, int w, int h, int Max_Width, int Max_Height);
    ~Rocket();

    int getNumRockets();
    bool update();
    void render(SDL_Renderer* ren);
    SDL_Rect& getScreenRect();
    void destroy();
};


#endif