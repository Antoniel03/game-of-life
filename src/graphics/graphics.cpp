#include "graphics.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <iostream>

Graphics::Graphics() {
  win = SDL_CreateWindow("Game of life", 640, 480, 0);
  ren = SDL_CreateRenderer(win, NULL);
}
void Graphics::init() {
  SDL_Init(SDL_INIT_VIDEO);
  if (win == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
  }

  if (ren == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(win);
    SDL_Quit();
  }
}

void Graphics::loop(bool quit) {
  while (!quit) {
    SDL_RenderPresent(ren);
    SDL_Delay(refresh_rate);
  }
}
