/***********************
 *Ramneek Chhatwal
 *rchhatw
 *Assignment 1
 **********************/

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

const int fps = 20;
const int frame_duration =  1000 / fps;

//Screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* my_window = NULL;
SDL_Renderer* my_renderer = NULL;
SDL_Event input;

void my_SDL_init(){

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
  }

  //Enable gpu_enhanced textures
  IMG_Init(IMG_INIT_PNG);

  my_window = SDL_CreateWindow("my_game",
			       SDL_WINDOWPOS_CENTERED,
			       SDL_WINDOWPOS_CENTERED,
			       SCREEN_WIDTH,
			       SCREEN_HEIGHT, 0);
  my_renderer = SDL_CreateRenderer(my_window,-1,0);

}

void updateMechanics(bool up, SDL_Rect &rect){
  rect.x -= 5;
  if (rect.x < 0) {
    rect.x = SCREEN_WIDTH;
  }
  if (up) rect.y += 20;
  else rect.y -= 20;
}


int main()
{
  bool jump = true;
  bool is_running = true;
  SDL_Event event;

  Uint32 start_time;

  double frame_time;

  my_SDL_init();

  SDL_Texture* my_text = NULL;
  SDL_Surface* temp_surface = IMG_Load("./Images/ImageSprite2DGameDesign.png");

  my_text = SDL_CreateTextureFromSurface(my_renderer, temp_surface);

  SDL_FreeSurface(temp_surface);

  //initializing initial sprite location
  SDL_Rect rect;
  rect.x = 450;
  rect.y = 200;
  rect.w = 150;
  rect.h = 200;

  SDL_Rect sky;
  sky.x = 0;
  sky.y = 0;
  sky.w = SCREEN_WIDTH;
  sky.h = SCREEN_HEIGHT/8;

  while (is_running) {
    start_time = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_running = false;
      }
    }

    //changing background color
    SDL_SetRenderDrawColor(my_renderer, 0, 30, 0 , 255);
    SDL_RenderClear(my_renderer);

    //putting a purple sky
    SDL_SetRenderDrawColor(my_renderer, 100, 23, 212, 255);

    SDL_RenderFillRect(my_renderer, &sky);
    //rendering image
    SDL_RenderCopy(my_renderer, my_text, NULL, &rect);
    updateMechanics(jump, rect);
    jump = !jump;
    SDL_RenderPresent(my_renderer);

    frame_time = SDL_GetTicks() - start_time;

    if (frame_time < frame_duration) {
      SDL_Delay(frame_duration - frame_time);
    }
  }

  SDL_DestroyTexture(my_text);
  SDL_DestroyRenderer(my_renderer);
  SDL_DestroyWindow(my_window);

  IMG_Quit();
  SDL_Quit();

  return 0;
}
