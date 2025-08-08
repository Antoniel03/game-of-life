#include "../models/cell.hpp"
#include "game_io.hpp"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <iostream>

Game_IO::Game_IO() {
  win = SDL_CreateWindow("Game of life", 1280, 700, 0);
  ren = SDL_CreateRenderer(win, NULL);
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

void Game_IO::loop(bool quit) {
  SDL_Event event;
  bool mouse_wheel_pressed = false;
  while (status != ENDED) {
    handle_button_events(&event, &mouse_wheel_pressed);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    render_cells();
    SDL_SetRenderDrawColor(ren, 100, 200, 150, 255);
    SDL_RenderRect(ren, &squareOutline);
    SDL_RenderPresent(ren);
    SDL_Delay(refresh_rate);
  }
}

void Game_IO::render_cells() {
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

void Game_IO::set_cells(Cell **_cells) { cells = _cells; }

void Game_IO::print_current_cells() {
  for (int i = 0; i < this->squareOutline.w; i += 10) {
    for (int j = 0; j < this->squareOutline.h; j += 10) {
      SDL_FRect *graphic = cells[i][j].get_cell_graphic();
      std::cout << "cell: " << graphic->x << "," << graphic->y
                << ": " + cells[i][j].get_status_name() << std::endl;
    }
  }
}

void Game_IO::init_cells() {
  int rows = static_cast<int>(squareOutline.w);
  int columns = static_cast<int>(squareOutline.h);
  cells = new Cell *[rows];
  std::cout << "initialized cell rows: " << rows << std::endl;

  for (int i = 0; i < rows; i += 10) {
    cells[i] = new Cell[columns];
    std::cout << "created new column at " << i << std::endl;
    for (int j = 0; j < columns; j += 10) {
      float x = static_cast<float>(i);
      float y = static_cast<float>(j);
      cells[i][j] = Cell{x, y, DEAD};
      SDL_FRect *graphic = cells[i][j].get_cell_graphic();
    }
  }
  std::cout << "out" << std::endl;
}

void Game_IO::set_canvas_size(float h, float w) {
  squareOutline = SDL_FRect{0, 0, w, h};
}

SDL_Renderer *Game_IO::get_renderer() { return ren; }
SDL_FRect *Game_IO::get_squareoutline() { return &squareOutline; }
GameIO_Status Game_IO::get_state() { return status; }
Cell **Game_IO::get_cells() { return cells; }
