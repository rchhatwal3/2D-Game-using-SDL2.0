#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"

class GameObject
{
private:
    int x_pos, y_pos, width, height;
    double angle;
    char* obj_name;

    SDL_Rect obj_TargetRect;
    SDL_Rect obj_SpriteRect;

    SDL_Renderer* ObjRenderer;
    SDL_Texture* ObjTexture;
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
        LEFT
    };

    StateMachine state; 

    GameObject(const char* name, int x, int y, int w, int h);
    ~GameObject();

    void setPlayerState(StateMachine new_state);
    void setMaxImageWidth(int max_w);
    void renderBackground(SDL_Renderer* ren);
    void renderSprite(SDL_Renderer* ren);
    void updateAsteroid();
    void updatePlayableObj();
    void quitObj();

    int obj_get_x_pos();
    void obj_set_x_pos(int pos);

    int obj_get_y_pos();
    void obj_set_y_pos(int pos);

    SDL_Rect& get_ScreenRect();
};



#endif