/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/TextManager.h"

TextManager::TextManager(const char* file, int size, int xPos, int yPos, SDL_Color color)
{
    textFilePath = file;
    fontSize = size;
    textXpos = xPos;
    textYpos = yPos;
    textColor = color;

    textRect.x = textXpos;
    textRect.y = textYpos;

    font = TTF_OpenFont(textFilePath, fontSize);
    if(!font)
    {
        std::cout << "Font did not load: " << TTF_GetError() << std::endl;
    }
}

TextManager::~TextManager(){}

void TextManager::updateText(std::string newText)
{
    //textSurface = TTF_RenderText_Solid(font, newText.c_str(), textColor);
    if(!(textSurface = TTF_RenderText_Solid(font, newText.c_str(), textColor)))
    {
        std::cout << "error converting font to surface" << std::endl;
    }  
    else 
    {
        textSurface = TTF_RenderText_Solid(font, newText.c_str(), textColor);
    }
}

void TextManager::text_render(SDL_Renderer* ren)
{
    text_texture = SDL_CreateTextureFromSurface(ren, textSurface);
    SDL_QueryTexture(text_texture, NULL, NULL, &textW, &textH);
    textRect.w = textW;
    textRect.h = textH;

    SDL_RenderCopy(ren, text_texture, NULL, &textRect);
    SDL_DestroyTexture(text_texture);
}

void TextManager::text_destroy()
{
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    delete(this);
}