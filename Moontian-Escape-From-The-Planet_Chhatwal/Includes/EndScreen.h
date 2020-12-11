/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

class EndScreen
{
private:
    int x_pos, y_pos, width, height;
    bool inEndScreen, playAgain;

    SDL_Rect obj_TargetRect;
    SDL_Surface* ObjSurface;
public:
    EndScreen(const char* name, int x, int y, int w, int h);
    ~EndScreen();

    void handleInput();
    void renderBackground(SDL_Renderer* ren);
    void quitObj();
    bool getInEndScreen();
    bool getPlayAgain();
};

#endif