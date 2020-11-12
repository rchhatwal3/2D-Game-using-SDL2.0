/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/Background.h"

Background::Background(const char* name, int x, int y, int w, int h)
{
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

Background::~Background()
{
}

void Background::renderBackground(SDL_Renderer* ren)
{
    SDL_Texture* game_texture = SDL_CreateTextureFromSurface(ren, ObjSurface);
    SDL_RenderCopy(ren, game_texture, NULL, &obj_TargetRect);
    SDL_DestroyTexture(game_texture);
}

void Background::quitObj()
{
    SDL_FreeSurface(ObjSurface);
    delete(this);
}