/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/EndScreen.h"
#include <iostream>

EndScreen::EndScreen(const char* name, int x, int y, int w, int h)
{
    inEndScreen = true;

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

EndScreen::~EndScreen()
{
}

void EndScreen::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT)
        {
            playAgain = false;
            inEndScreen = false;
        }

        if (event.type == SDL_KEYDOWN) 
        {
            switch (event.key.keysym.sym) 
            {
                case SDLK_RETURN:
                    playAgain = true;
                    inEndScreen = false;
                    break;

                case SDLK_RETURN2:
                    playAgain = true;
                    inEndScreen = false;
                    break;

                case SDLK_ESCAPE:
                    playAgain = false;
                    inEndScreen = false;
                    break;
                default:
                    break;
            }
        }
    }
}

void EndScreen::renderBackground(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopy(ren, game_texture, NULL, &obj_TargetRect);
    SDL_RenderPresent(ren);
    SDL_DestroyTexture(game_texture);
}

void EndScreen::quitObj()
{
    SDL_FreeSurface(ObjSurface);
    delete(this);
}

bool EndScreen::getInEndScreen()
{
    return inEndScreen;
}

bool EndScreen::getPlayAgain()
{
    return playAgain;
}