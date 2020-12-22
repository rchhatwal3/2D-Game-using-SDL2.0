/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include "SDL2_Files.h"
#include "CONSTANTS.h"
#include <iostream>

class TextManager
{
private:
    const char* text;
    const char* textFilePath;
    int fontSize;
    int textXpos;
    int textYpos;
    int textW;
    int textH;

    TTF_Font* font;
    SDL_Color textColor;
    SDL_Surface* textSurface;
    SDL_Texture* text_texture;
    SDL_Rect textRect;

public:
    TextManager(const char* file, int size, int xPos, int yPos, SDL_Color color);
    ~TextManager();

    void updateText(std::string newText);
    void text_render(SDL_Renderer* ren);
    void text_destroy();

};

#endif