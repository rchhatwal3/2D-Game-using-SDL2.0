/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/GameEngine.h"
#include <iostream>

GameEngine::GameEngine(std::string windowName, int user_FPS)
{
    windowName = this->windowName;
    FPS = user_FPS;
    frame_duration = 1000 / FPS;
    game_running = true;
    collision = false;
    renderedParticleFrames = 0;

    //height x width of frame is 93 X 70 giving a scale of 1.33.
    astronaut = new Astronaut("./Images/AstronautSpriteSheet210by93.png", 0, 200, 70, 93, 210);

    //height x width of frame is 50 x 50 giving a scale of 1.
    asteroid = new Asteroid("./Images/asteroid800by50.png", 400, 300, 50, 50, 800);

    background = new Background("./Images/moon_surface.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    particle_emitter = new ParticleEmitter();
}

GameEngine::~GameEngine()
{
    astronaut->quitObj();
    asteroid->quitObj();
    particle_emitter->emitter_quit();

    SDL_DestroyRenderer(game_renderer);
    SDL_DestroyWindow(game_window);

    IMG_Quit();
    SDL_Quit();
}

//This function will initialize the Game Screen as well as create the renderer to be used in the rest of the program
void GameEngine::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }

    //Enable gpu_enhanced textures
    IMG_Init(IMG_INIT_PNG);

    game_window = SDL_CreateWindow("Moontian - Escape from the Planet",
			       SDL_WINDOWPOS_CENTERED,
			       SDL_WINDOWPOS_CENTERED,
			       SCREEN_WIDTH,
			       SCREEN_HEIGHT, 0);
    game_renderer = SDL_CreateRenderer(game_window,-1,0);
}

//This function will use KEY_UP and KEY_DOWN to determine what the user inputted and change the corresponding State Machine
void GameEngine::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT) game_running = false;
        if (!collision)
        {
            //using delta Position control metaphor
            if (event.type == SDL_KEYDOWN) 
            {
                switch (event.key.keysym.sym) 
                {
                    case SDLK_UP:
                        //set state machine to MOVE_UP
                        astronaut->setPlayerState(Astronaut::StateMachine::UP);
                        break;

                    case SDLK_DOWN:
                        //set state machine to MOVE_Down  
                        astronaut->setPlayerState(Astronaut::StateMachine::DOWN);
                        break;

                    case SDLK_LEFT:
                        //set state machine to MOVE_Left 
                        astronaut->setPlayerState(Astronaut::StateMachine::LEFT);
                        break;

                    case SDLK_RIGHT:
                        //set state machine to MOVE_Right
                        astronaut->setPlayerState(Astronaut::StateMachine::RIGHT);
                        break;

                    default:
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) 
            {
                //set state machine to idle
                astronaut->setPlayerState(Astronaut::StateMachine::IDLE);
            }
        }
    }
}

//This function will call the update functions for the objects that need to be updated in the game.
void GameEngine::updateMechanics()
{
    if (!collision)
    {
        astronaut->updateAstronaut();
        asteroid->updateAsteroid();
        
        if (boxCollisionCheck(astronaut->getScreenRect(), asteroid->getScreenRect()))
        {
            //call collision response (I'm thinking a function for dead sprite)
            astronaut->setPlayerState(Astronaut::StateMachine::DEAD);

            //call particle emitter
            std::cout << "Collision! Game Over!\n";
            particle_emitter->emitter_init("./Images/asteroidPiece15x12.png", game_renderer, asteroid->getScreenRect().x, asteroid->getScreenRect().y, 15, 12);
            collision = true;
        }
    }
    else
    {
        particle_emitter->emitter_update();
    }
    
}

//This function will return a boolean on if the game is still playable and user hasn't exited the game window
bool GameEngine::get_is_game_running()
{
    return game_running;
}

//This function will call the appropriate render functions for respective objects
void GameEngine::render()
{
    //set background to black
    SDL_SetRenderDrawColor(game_renderer, 0, 0, 0, 255);

    //clear the screen
    SDL_RenderClear(game_renderer);

    //render the background image (a planet surface)
    background->renderBackground(game_renderer);

    if (!collision)
    {
        //render singular asteroid
        asteroid->renderAsteroid(game_renderer);

        //render main PC (astronaut)
        astronaut->renderAstronaut(game_renderer);
    }
    else
    {
        particle_emitter->emitter_render(game_renderer);
    }

    SDL_RenderPresent(game_renderer);
}

bool GameEngine::boxCollisionCheck(SDL_Rect left_rect, SDL_Rect right_rect)
{
    int leftSideLeftRect, rightSideLeftRect, topSideLeftRect, bottomSideLeftRect;
    int leftSideRightRect, rightSideRightRect, topSideRightRect, bottomSideRightRect;

    //left-sided rects values. top left coordinate of rect is "(0,0)" point
    leftSideLeftRect = left_rect.x;
    rightSideLeftRect = left_rect.x + left_rect.w;
    topSideLeftRect = left_rect.y;
    bottomSideLeftRect = left_rect.y + left_rect.h;

    //right-sided rects values. top left coordinate of rect is "(0,0)" point
    leftSideRightRect = right_rect.x;
    rightSideRightRect = right_rect.x + right_rect.w;
    topSideRightRect = right_rect.y;
    bottomSideRightRect = right_rect.y + right_rect.h;

    //checks and returns for collision
    if (rightSideLeftRect < leftSideRightRect) return false;
    if (leftSideLeftRect > rightSideRightRect) return false;
    if (bottomSideLeftRect < topSideRightRect) return false;
    if (topSideLeftRect > bottomSideRightRect) return false;

    return true;
}

Uint32 GameEngine::get_frame_duration()
{
    return frame_duration;
}