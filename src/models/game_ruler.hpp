#include "cell.hpp"
#pragma once

class Game_Ruler {
private:
  int current_cells = 0;
  int current_cells_alive = 0;
  Cell **cells;
  int width = 0;
  int height = 0;

public:
  Game_Ruler();
  Game_Ruler(int _width, int _height);
  bool validate_coord(float x, float y);
  bool add(float x, float y, cell_status status);
  void kill(int x, int y);
  void delete_cell(float x, float y);
  int count_alive();
  int count();
  Cell **getMatrix();
};
