#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Astronaut.h"
#include "Asteroid.h"
#include "Background.h"
#include <iostream>

class StateMachine;

class GameEngine
{
    private:
        std::string windowName;
        int FPS;
        int frame_duration;
        bool game_running;

        SDL_Renderer* game_renderer;
        SDL_Window* game_window;

    public:
        GameEngine(std::string windowName, int user_FPS);
        ~GameEngine();

        Astronaut* astronaut;
        Asteroid* asteroid;
        Background* background;

        void init();
        void handleInput();
        void updateMechanics();
        bool get_is_game_running();
        void render();
        Uint32 get_frame_duration();
};

#endif
