#include <SDL3/SDL_rect.h>
#pragma once
enum cell_status { ALIVE, DEAD };

class Cell {
private:
  cell_status status;
  SDL_FRect *cell_graphic;
  int x;
  int y;

public:
  Cell();
  Cell(float x, float y);
  void update_status(cell_status _status);
  cell_status get_status();
  SDL_FRect *get_cell_graphic();
  void update_position(float x, float y);
};
