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
  status = RUNNING;
  if (win == nullptr) {
    status = ENDED;
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
  }

  if (ren == nullptr) {
    status = ENDED;
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(win);
    SDL_Quit();
  }
}

void Game_IO::loop(bool quit) {
  SDL_Event event;
  bool mouse_wheel_pressed = false;
  while (status != ENDED) {
    handle_button_events(&event, &mouse_wheel_pressed);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    render_cells();
    SDL_RenderPresent(ren);
    SDL_Delay(refresh_rate);
  }
}

void Game_IO::render_cells() {
  int size = cells.size();
  for (int i = 0; i < size; i++) {
    if (cells[i]->get_status() == ALIVE)
      SDL_SetRenderDrawColor(ren, 100, 200, 150, 255);
    else
      SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

    SDL_RenderFillRect(ren, cells[i]->get_cell_graphic());
  }
};

void Game_IO::zoom_in() {
  float scale_x;
  float scale_y;
  SDL_GetRenderScale(ren, &scale_x, &scale_y);
  std::cout << "x: " << scale_y << ", y:" << scale_y << std::endl;
  SDL_SetRenderScale(ren, scale_x + 0.1, scale_y + 0.1);
}
void Game_IO::zoom_out() {
  float scale_x;
  float scale_y;
  SDL_GetRenderScale(ren, &scale_x, &scale_y);
  std::cout << "x: " << scale_y << ", y:" << scale_y << std::endl;
  SDL_SetRenderScale(ren, scale_x - 0.1, scale_y - 0.1);
}

void Game_IO::set_cells(std::vector<Cell *> _cells) { cells = _cells; }
