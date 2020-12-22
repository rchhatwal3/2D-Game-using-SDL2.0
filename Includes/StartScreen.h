/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

class StartScreen
{
private:
    int x_pos, y_pos, width, height;
    bool inStartScreen;

    SDL_Rect obj_TargetRect;
    SDL_Surface* ObjSurface;
public:
    StartScreen(const char* name, int x, int y, int w, int h);
    ~StartScreen();

    void handleInput();
    void renderBackground(SDL_Renderer* ren);
    void quitObj();
    bool getInStartScreen();
};

#endif