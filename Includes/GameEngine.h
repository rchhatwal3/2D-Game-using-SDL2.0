/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Astronaut.h"
#include "Asteroid.h"
#include "Background.h"
#include "Particle.h"
#include "TextManager.h"
#include "StartScreen.h"
#include "EndScreen.h"
#include "Rocket.h"

#include <iostream>
#include <string>
#include <sstream>

class StateMachine;

class GameEngine
{
    private:
        std::string windowName;
        int FPS;
        int frame_duration;
        bool game_running;
        bool winStatus;
        bool playAgain;
        bool asteroidCollision;
        int renderedParticleFrames;

        SDL_Renderer* game_renderer;
        SDL_Window* game_window;

    public:
        GameEngine(std::string windowName, int user_FPS);
        ~GameEngine();

        Astronaut* astronaut;
        Asteroid* asteroid;
        Background* background;
        ParticleEmitter* particle_emitter;
        TextManager* text_manager;
        Rocket* rocket;
        StartScreen* startscreen;
        EndScreen* endscreen;

        void init();
        void destroyEngine();
        void startScreen();
        void endScreen();
        void handleInput();
        void updateMechanics();
        bool get_is_game_running();
        void render();
        bool boxCollisionCheck(SDL_Rect left_rect, SDL_Rect right_rect);
        Uint32 get_frame_duration();
        bool getWinStatus();
};

#endif
