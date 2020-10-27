/***********************
 *Ramneek Chhatwal
 *rchhatw
 *Assignment 3
 **********************/

#include "../Includes/GameEngine.h"
#include "../Includes/CONSTANTS.h"

//from CONSTANTS.h
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int PLAYER_VEL = 5;
int ASTEROID_VEL = 4;

int GAME_BOUND_LEFT_X = 0;
int GAME_BOUND_RIGHT_X = SCREEN_WIDTH;
int GAME_BOUND_UPPER_Y = SCREEN_HEIGHT;
int GAME_BOUND_LOWER_Y = 0;

int main(int argc, char const *argv[])
{
    Uint32 start_time, this_duration;

    // params are (Screen Width, Screen Height, FPS, Screen Width, Screen Height)
    GameEngine* engine = new GameEngine("my_game", 20);

    engine->init();

    while (engine->get_is_game_running())
    {
        start_time = SDL_GetTicks();

        engine->handleInput();
        engine->updateMechanics();
        engine->render();

        this_duration = SDL_GetTicks() - start_time;

        if (this_duration < engine->get_frame_duration())
        {
            SDL_Delay(engine->get_frame_duration() - this_duration);
        }
    }

    delete(engine);
    
    return 0;
}