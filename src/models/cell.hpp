#include <SDL3/SDL_rect.h>
#include <string>
#pragma once
enum cell_status { ALIVE, DEAD };
using std::string;

class Cell {
private:
  cell_status status;
  SDL_FRect *cell_graphic;

public:
  Cell();
  Cell(float x, float y);
  Cell(float x, float y, cell_status _cell_status);
  void update_status(cell_status _status);
  cell_status get_status();
  SDL_FRect *get_cell_graphic();
  void update_position(float x, float y);
  string get_status_name();
};
