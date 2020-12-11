/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/GameEngine.h"
#include "../Includes/CONSTANTS.h"

//from CONSTANTS.h
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int PLAYER_VEL = 7;
int ASTEROID_VEL = 10;

int GAME_BOUND_LEFT_X = 0;
int GAME_BOUND_RIGHT_X = SCREEN_WIDTH;
int GAME_BOUND_UPPER_Y = SCREEN_HEIGHT;
int GAME_BOUND_LOWER_Y = 0;

int MAX_LEVEL_ROCKETS = 5;

int main(int argc, char const *argv[])
{
    Uint32 start_time, this_duration;
    int desiredFPS = 20;
    bool playAgain = true;

    // params are ("Screen name, desiredFPS")
    GameEngine* engine = new GameEngine("Moontian - Escape from the Planet", desiredFPS);

    while (playAgain)
    {
       engine->init();
       std::cout<< "engine has beein inited" << std::endl;

        //call start screen
        engine->startScreen();
        std::cout << "would be at the start screen" << std::endl;

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

        //call end screen
        engine->endScreen();
        std::cout << "at the end screen" << std::endl;
        playAgain = engine->endscreen->getPlayAgain();

        std::cout << "Play again? " << playAgain << std::endl;

        engine->destroyEngine();
        std::cout<< "Engine Destroyed " << std::endl;
    }

    delete(engine);
    
    return 0;
}