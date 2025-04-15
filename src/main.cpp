#include "graphics/graphics.hpp"
#include "models/cell.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Cell a = Cell{1, 1};
  Cell b = Cell{10, 10};
  Cell c = Cell{20, 20};
  c.update_status(DEAD);
  std::vector<Cell *> cells = {&a, &b, &c};
  Graphics g = Graphics();
  g.init();
  g.loop(cells, false);
}
