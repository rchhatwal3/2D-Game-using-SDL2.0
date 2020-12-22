/**********************************
 *Ramneek Chhatwal
 *rchhatw
 *Moontian - Escape from the Planet
 *********************************/

#include "../Includes/GameEngine.h"
#include <iostream>

GameEngine::GameEngine(std::string windowName, int user_FPS)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }

    //Enable gpu_enhanced textures
    IMG_Init(IMG_INIT_PNG);

    //Enable ttf text features
    TTF_Init();
    if (!TTF_WasInit())
    {
        std::cout << "TTF Init Failed" << TTF_GetError() << std::endl;
    }

    game_window = SDL_CreateWindow(windowName.c_str(),
			       SDL_WINDOWPOS_CENTERED,
			       SDL_WINDOWPOS_CENTERED,
			       SCREEN_WIDTH,
			       SCREEN_HEIGHT, 0);
    game_renderer = SDL_CreateRenderer(game_window,-1,0);

    windowName = this->windowName;
    FPS = user_FPS;
    frame_duration = 1000 / FPS;
}

GameEngine::~GameEngine()
{
    SDL_DestroyRenderer(game_renderer);
    SDL_DestroyWindow(game_window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

//This function will initialize the Game Screen as well as create the renderer to be used in the rest of the program
void GameEngine::init()
{
    game_running = true;
    winStatus = false;
    asteroidCollision = false;
    renderedParticleFrames = 0;

    //height x width of frame is 93 X 70 giving a scale of 1.33.
    astronaut = new Astronaut("./Images/AstronautSpriteSheet210by93.png", 0, 200, 70, 93, 210);

    //height x width of frame is 50 x 50 giving a scale of 1.
    asteroid = new Asteroid("./Images/asteroid800by50.png", 400, 300, 50, 50, 800);

    background = new Background("./Images/moon_surface.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    particle_emitter = new ParticleEmitter();

    //each part is 64x64 total image is 192x256
    rocket = new Rocket("./Images/turret_medium_64x64.png", 64, 64, 192, 256);

    //initialize start screen
    startscreen = new StartScreen("./Images/startScreen.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    text_manager = new TextManager("./TTF_Fonts/rocketCountFont.ttf", 25, 0, 0, {255, 255, 255});   

    //setting initial TTF string
    std::ostringstream oss;
    oss << "Rocket Pieces Retrieved: " << rocket->getNumRockets() << " / " << MAX_LEVEL_ROCKETS;
    std::string tempString = oss.str();
    text_manager->updateText(tempString.c_str());//concat "Rocket Pieces Retrieved: " + getRocketAmt + "/" + MAX_ROCKET_PIECES
}

void GameEngine::destroyEngine()
{
    astronaut->quitObj();
    asteroid->quitObj();
    particle_emitter->emitter_quit();
    text_manager->text_destroy();
    rocket->destroy();
    startscreen->quitObj();
    endscreen->quitObj();
    background->quitObj();
}

void GameEngine::startScreen()
{
    while (startscreen->getInStartScreen())
    {
        startscreen->handleInput();
        startscreen->renderBackground(game_renderer);
    }
    
}

void GameEngine::endScreen()
{
    if (winStatus)
    {
        endscreen = new EndScreen("./Images/winningEndScreen.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else 
    {
        endscreen = new EndScreen("./Images/LosingEndScreen.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    while (endscreen->getInEndScreen())
    {
        endscreen->handleInput();
        endscreen->renderBackground(game_renderer);
    }
}

//This function will use KEY_UP and KEY_DOWN to determine what the user inputted and change the corresponding State Machine
void GameEngine::handleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_QUIT) game_running = false;
        if (!asteroidCollision)
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
        else
        {
            game_running = false;
        }
        
    }
}

//This function will call the update functions for the objects that need to be updated in the game.
void GameEngine::updateMechanics()
{
    //checking if user came in contact with rocket piece
    if (boxCollisionCheck(astronaut->getScreenRect(), rocket->getScreenRect()))
    {
        winStatus = rocket->update();
        std::ostringstream oss;
        oss << "Rocket Pieces Retrieved: " << rocket->getNumRockets() << " / " << MAX_LEVEL_ROCKETS;
        std::string tempString = oss.str();
        text_manager->updateText(tempString);//concat "Rocket Pieces Retrieved: " + getRocketAmt + "/" + MAX_ROCKET_PIECES
    }

    if (winStatus) 
    {
        std::cout << "Congrats you Won!" << std::endl;
        game_running = false;
    }

    //checking if user came in contact with asteroid 
    if (!asteroidCollision)
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
            asteroidCollision = true;
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

    //render rocket ship piece
    rocket->render(game_renderer);

    if (!asteroidCollision)
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

    text_manager->text_render(game_renderer);

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

bool GameEngine::getWinStatus()
{
    return winStatus;
}