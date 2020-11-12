/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

class Astronaut
{
private:
    int x_pos, y_pos, width, height;
    double angle;

    SDL_Rect obj_TargetRect;
    SDL_Rect obj_SpriteRect;

    SDL_Surface* ObjSurface;

    int spriteImageWidth;

    SDL_RendererFlip objOrientation;

public:
    enum StateMachine 
    {
        IDLE,
        UP,
        DOWN,
        RIGHT,
        LEFT,
        DEAD
    };

    StateMachine state; 

    Astronaut(const char* name, int x, int y, int w, int h, int Max_Width);
    ~Astronaut();

    void setPlayerState(int enum_index);
    void setPlayerState(StateMachine value);
    void updateAstronaut();
    void renderAstronaut(SDL_Renderer* ren);
    void quitObj();

    int obj_get_x_pos();
    void obj_set_x_pos(int pos);

    int obj_get_y_pos();
    void obj_set_y_pos(int pos);

    SDL_Rect& getScreenRect();
    
};

#endif 

