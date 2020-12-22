 #ifndef SPRITE_H
 #define SPRITE_H

 #include "SDL2_Files.h"
 #include <iostream>

class Sprite
{
private:
    int totalFrames, currentFrame, frame_duration;

    SDL_Rect frame_rect;

public:
    Sprite(int frameNum, int start_width, int start_height);
    ~Sprite();

    bool idle;

    void sprite_update();
    SDL_Rect& getSpriteRect();
};

#endif