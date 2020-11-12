#include "../Includes/Unused_Includes/Sprite.h"

Sprite::Sprite(int frameNum, int start_width, int start_height)
{
    totalFrames = frameNum;
    currentFrame = 0;

    frame_rect.w = start_width;
    frame_rect.h = start_height;
    frame_rect.x = 0;
    frame_rect.y = 0;
}

Sprite::~Sprite()
{
}

void Sprite::sprite_update()
{
    int frame_time = (int) (SDL_GetTicks() / frame_duration) % currentFrame;

    static int last_frame_time = 0;
    if (last_frame_time != frame_time)
    {
        if (frame_time < 1) frame_rect.x = 0; //reseting x value
        else frame_rect.x += frame_rect.w;
    }
    last_frame_time = frame_time;
}


SDL_Rect& Sprite::getSpriteRect()
{
    return frame_rect;
}




