#include "game_ruler.hpp"
#include <iostream>

Game_Ruler::Game_Ruler() {
  height = 690;
  width = 1270;
  cells = new Cell *[height];

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      cells[i] = new Cell[height];
    }
  }
}

Game_Ruler::Game_Ruler(int _width, int _height) {
  height = _height;
  width = _width;
  cells = new Cell *[_height];

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      cells[i][j] = Cell(i + 3, j + 3);
      cells[i][j].update_status(DEAD);
    }
  }
}
void Game_Ruler::kill(int x, int y) {
  cells[x][y].update_status(DEAD);
  current_cells_alive--;
}
int Game_Ruler::count_alive() { return current_cells_alive; }
int Game_Ruler::count() { return current_cells; }
Cell **Game_Ruler::getMatrix() { return cells; }

void Game_Ruler::set_matrix(Cell **_cells) { cells = _cells; }

void Game_Ruler::process_next_generation() {
  for (int i = 0; i < height; i += 10) {
    for (int j = 0; j < width; j += 10) {
      int neighbors = count_neighbors(i, j);
      if ((i != height) && (j != width)) {

        // Birth
        if ((cells[i][j].get_status() == DEAD) && (neighbors == 3))
          cells[i][j].update_status(ALIVE);

        if ((cells[i][j].get_status() == ALIVE)) {

          // Underpopulation
          if (neighbors < 2)
            cells[i][j].update_status(DEAD);

          // Overpopulation
          else if (neighbors > 3)
            cells[i][j].update_status(DEAD);

          // Survival
          // else if ((neighbors == 3) || (neighbors == 2))
          //   cells[i][j].update_status(ALIVE);
        }
      }
    }
  }
}

bool Game_Ruler::is_neighbor_alive(int x, int y) {
  if (!valid_coord(x, y))
    return false;
  if (cells[x][y].get_status() == ALIVE)
    return true;
  return false;
}

int Game_Ruler::count_neighbors(int x, int y) {
  int neighbors_alive = 0;
  for (int i = x - 10; i < x + 20; i += 10) {
    for (int j = y - 10; j < y + 20; j += 10) {
      if ((i != x) && (j != y) && (cells[i][j].get_status() == ALIVE))
        neighbors_alive++;
    }
  }
  return neighbors_alive;
}

bool Game_Ruler::valid_coord(int x, int y) {
  if ((x < height) && (y < width))
    return true;
  return false;
}
