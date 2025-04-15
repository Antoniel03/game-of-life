#include "game_io.hpp"
// #include "../models/cell.hpp"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <iostream>

Game_IO::Game_IO() {
  win = SDL_CreateWindow("Game of life", 640, 480, 0);
  ren = SDL_CreateRenderer(win, NULL);
}
void Game_IO::init() {
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

void Game_IO::loop(std::vector<Cell *> cells, bool quit) {
  while (!quit) {

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    render_cells(cells);
    SDL_RenderPresent(ren);
    SDL_Delay(refresh_rate);
  }
}

void Game_IO::render_cells(std::vector<Cell *> cells) {
  int size = cells.size();
  for (int i = 0; i < size; i++) {
    if (cells[i]->get_status() == ALIVE)
      SDL_SetRenderDrawColor(ren, 100, 200, 150, 255);
    else
      SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

    SDL_RenderFillRect(ren, cells[i]->get_cell_graphic());
  }
};
