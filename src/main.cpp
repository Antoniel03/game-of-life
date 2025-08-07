#include "game_io/game_io.hpp"
#include "models/cell.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  // Cell a = Cell{4, 4};
  // Cell b = Cell{10, 10};
  // Cell c = Cell{20, 20};
  // c.update_status(DEAD);
  // std::vector<Cell *> cells = {&a, &b, &c};
  Game_IO g = Game_IO();
  // g.set_cells(cells);
  g.init();
  g.set_canvas_size(100, 100);
  g.init_cells();
  g.loop(false);
}
