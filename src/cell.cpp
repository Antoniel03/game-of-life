#include "models/cell.hpp"
#include <SDL3/SDL_rect.h>
#include <iostream>

Cell::Cell() { status = ALIVE; }

Cell::Cell(float x, float y) {
  status = ALIVE;
  cell_graphic = new SDL_FRect{x, y, 10, 10};
}

Cell::Cell(float x, float y, cell_status _cell_status) {
  status = _cell_status;
  cell_graphic = new SDL_FRect{x, y, 10, 10};
}

void Cell::update_status(cell_status _status) { status = _status; }

cell_status Cell::get_status() { return status; }

SDL_FRect *Cell::get_cell_graphic() { return cell_graphic; }

void Cell::update_position(float x, float y) {
  cell_graphic->x = x;
  cell_graphic->y = y;
}

string Cell::get_status_name() {
  if (status == 0)
    return "ALIVE";
  return "DEAD";
}
