/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/StartScreen.h"
#include <iostream>

StartScreen::StartScreen(const char* name, int x, int y, int w, int h)
{
    inStartScreen = true;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;

    obj_TargetRect.h = height;
    obj_TargetRect.w = width;
    obj_TargetRect.x = x_pos;
    obj_TargetRect.y = y_pos;

    ObjSurface = IMG_Load(name);
}

StartScreen::~StartScreen()
{
}

void StartScreen::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT) inStartScreen = false;

        if (event.type == SDL_KEYDOWN) 
        {
            switch (event.key.keysym.sym) 
            {
                case SDLK_RETURN:
                    inStartScreen = false;
                    break;

                case SDLK_RETURN2:
                    inStartScreen = false;
                    break;

                default:
                    break;
            }
        }
    }
}

void StartScreen::renderBackground(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopy(ren, game_texture, NULL, &obj_TargetRect);
    SDL_RenderPresent(ren);
    SDL_DestroyTexture(game_texture);
}

void StartScreen::quitObj()
{
    SDL_FreeSurface(ObjSurface);
    delete(this);
}

bool StartScreen::getInStartScreen()
{
    return inStartScreen;
}