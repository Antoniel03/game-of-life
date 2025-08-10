#include "cell.hpp"
#pragma once

class Game_Rules {
private:
  int current_cells = 0;
  int current_cells_alive = 0;
  int generation = 0;
  Cell **cells;
  int width = 0;
  int height = 0;

public:
  Game_Rules();
  Game_Rules(int _width, int _height);
  Cell **getMatrix();
  void set_matrix(Cell **_cells);
  void process_next_generation();

private:
  void kill(int x, int y);
  bool is_neighbor_alive(int x, int y);
  int count_neighbors(int x, int y);
  bool valid_coord(int x, int y);
  Cell **init_cells();
  void free_cells();
};
