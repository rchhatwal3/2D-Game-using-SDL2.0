/***********************
 *Ramneek Chhatwal
 *rchhatw
 *Assignment 3
 **********************/

#include "../Includes/GameEngine.h"

GameEngine::GameEngine(std::string windowName, int user_FPS)
{
    windowName = this->windowName;
    FPS = user_FPS;
    frame_duration = 1000 / FPS;
    game_running = true;

    //height x width of frame is 93 X 70 giving a scale of 1.33.
    astronaut = new Astronaut("./Images/AstronautSpriteSheet210by93.png", 0, 200, 70, 93, 210);

    //height x width of frame is 50 x 50 giving a scale of 1.
    asteroid = new Asteroid("./Images/asteroid800by50.png", 400, 300, 50, 50, 800);

    background = new Background("./Images/moon_surface.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

GameEngine::~GameEngine()
{
    astronaut->quitObj();
    asteroid->quitObj();

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

    game_window = SDL_CreateWindow("my_game",
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
        
        //using delta Position control metaphor
        if (event.type == SDL_KEYDOWN) 
        {
            switch (event.key.keysym.sym) 
            {
                case SDLK_UP:
                    //set state machine to MOVE_UP
                    astronaut->setPlayerState(1);
                    break;

                case SDLK_DOWN:
                    //set state machine to MOVE_Down  
                    astronaut->setPlayerState(2);
                    break;

                case SDLK_LEFT:
                    //set state machine to MOVE_Left 
                    astronaut->setPlayerState(3);
                    break;

                case SDLK_RIGHT:
                    //set state machine to MOVE_Right
                    astronaut->setPlayerState(4);
                    break;

                default:
                    break;
            }
        }
        else if (event.type == SDL_KEYUP) 
        {
            //set state machine to idle
            astronaut->setPlayerState(5);
        }
    }
}

//This function will call the update functions for the objects that need to be updated in the game.
void GameEngine::updateMechanics()
{
    astronaut->updateAstronaut();
    asteroid->updateAsteroid();
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

    //render singular asteroid
    asteroid->renderAsteroid(game_renderer);

    //render main PC (astronaut)
    astronaut->renderAstronaut(game_renderer);

    SDL_RenderPresent(game_renderer);
}

Uint32 GameEngine::get_frame_duration()
{
    return frame_duration;
}