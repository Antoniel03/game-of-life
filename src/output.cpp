#include "models/cell.hpp"
#include "models/game_io.hpp"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <iostream>

Game_IO::Game_IO(int height, int width) {
  win = SDL_CreateWindow("Game of life", width, height, 0);
  ren = SDL_CreateRenderer(win, NULL);
  set_canvas_size(static_cast<float>(height), static_cast<float>(width));
}
void Game_IO::init() {
  SDL_Init(SDL_INIT_VIDEO);
  status = PAUSED;
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

void Game_IO::render_cells(Cell **cells) {
  for (int i = 0; i < this->squareOutline.w; i += 10) {
    for (int j = 0; j < this->squareOutline.h; j += 10) {
      if (cells[i][j].get_status() == ALIVE)
        SDL_SetRenderDrawColor(ren, 100, 200, 150, 255);
      else
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
      SDL_RenderFillRect(ren, cells[i][j].get_cell_graphic());
    }
  }
}

void Game_IO::print_current_cells(Cell **cells) {
  for (int i = 0; i < this->squareOutline.w; i += 10) {
    for (int j = 0; j < this->squareOutline.h; j += 10) {
      SDL_FRect *graphic = cells[i][j].get_cell_graphic();
      std::cout << "cell: " << graphic->x << "," << graphic->y
                << ": " + cells[i][j].get_status_name() << std::endl;
    }
  }
}

void Game_IO::set_canvas_size(float h, float w) {
  squareOutline = SDL_FRect{0, 0, w, h};
}

SDL_Renderer *Game_IO::get_renderer() { return ren; }
SDL_FRect *Game_IO::get_squareoutline() { return &squareOutline; }
GameIO_Status Game_IO::get_state() { return status; }
