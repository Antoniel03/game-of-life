#include "graphics/graphics.hpp"
#include "models/cell.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Cell a = Cell{1, 1};
  Cell b = Cell{2, 2};
  std::vector<Cell *> cells = {&a, &b};
  Graphics g = Graphics();
  g.init();
  g.loop(cells, false);
}
