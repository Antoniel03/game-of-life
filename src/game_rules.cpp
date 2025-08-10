#include "models/game_rules.hpp"
#include "models/cell.hpp"
#include <iostream>

Game_Rules::Game_Rules() {
  height = 690;
  width = 1270;
  cells = new Cell *[height];

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      cells[i] = new Cell[height];
    }
  }
}

Cell **Game_Rules::init_cells() {
  Cell **_cells = new Cell *[height];

  for (int i = 0; i < height; i += 10) {
    _cells[i] = new Cell[width];
    for (int j = 0; j < width; j += 10) {
      float x = static_cast<float>(i);
      float y = static_cast<float>(j);
      _cells[i][j] = Cell{x, y, DEAD};
      SDL_FRect *graphic = _cells[i][j].get_cell_graphic();
    }
  }
  return _cells;
}

Game_Rules::Game_Rules(int _width, int _height) {
  height = _height;
  width = _width;
  cells = init_cells();
}
void Game_Rules::kill(int x, int y) {
  cells[x][y].update_status(DEAD);
  current_cells_alive--;
}
Cell **Game_Rules::getMatrix() { return cells; }

void Game_Rules::set_matrix(Cell **_cells) { cells = _cells; }

void Game_Rules::process_next_generation() {
  Cell **next_gen = init_cells();

  for (int i = 0; i < width; i += 10) {
    for (int j = 0; j < height; j += 10) {
      int neighbors = count_neighbors(i, j);
      if ((i != width) || (j != height)) {

        // Birth
        if ((cells[i][j].get_status() == DEAD) && (neighbors == 3)) {
          next_gen[i][j].update_status(ALIVE);
        }

        if ((cells[i][j].get_status() == ALIVE)) {

          // Underpopulation
          if (neighbors < 2) {
            next_gen[i][j].update_status(DEAD);

          }
          // Overpopulation
          else if (neighbors > 3) {
            next_gen[i][j].update_status(DEAD);
          }

          // Survival
          else if ((neighbors == 3) || (neighbors == 2)) {
            next_gen[i][j].update_status(ALIVE);
          }
        }
      }
    }
  }
  // TODO: free cells
  cells = next_gen;
  std::cout << "generation: " << generation << std::endl;
  generation++;
}

bool Game_Rules::is_neighbor_alive(int x, int y) {
  if (!valid_coord(x, y))
    return false;
  if (cells[x][y].get_status() == ALIVE)
    return true;
  return false;
}

int Game_Rules::count_neighbors(int x, int y) {
  int neighbors_alive = 0;
  for (int i = x - 10; i < x + 20; i += 10) {
    for (int j = y - 10; j < y + 20; j += 10) {
      if ((i > 0) && (j > 0) && (i < height) && (j < width)) {
        if (((i != x) || (j != y)) && (cells[i][j].get_status() == ALIVE))
          neighbors_alive++;
      }
    }
  }
  return neighbors_alive;
}

bool Game_Rules::valid_coord(int x, int y) {
  if ((x < height) && (y < width))
    return true;
  return false;
}
