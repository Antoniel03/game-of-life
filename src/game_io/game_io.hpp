#include "../models/cell.hpp"
#include <SDL3/SDL.h>
#include <vector>

#pragma once

class Game_IO {
private:
  SDL_Window *win;
  SDL_Renderer *ren;
  int refresh_rate = 60;

public:
  Game_IO();
  // input

  // output
  void init();
  void zoom_in();
  void zoom_out();
  void loop(std::vector<Cell *> cells, bool quit);
  void change_refresh_rate(int refresh_rate);

private:
  void render_cells(std::vector<Cell *> cells);
};
