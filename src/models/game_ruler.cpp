#include "game_ruler.hpp"
#include "cell.hpp"
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

Cell **init_cells(int h, int w) {
  Cell **_cells = new Cell *[w];

  for (int i = 0; i < w; i += 10) {
    _cells[i] = new Cell[h];
    for (int j = 0; j < h; j += 10) {
      float x = static_cast<float>(i);
      float y = static_cast<float>(j);
      _cells[i][j] = Cell{x, y, DEAD};
      SDL_FRect *graphic = _cells[i][j].get_cell_graphic();
    }
  }
  return _cells;
}

Game_Ruler::Game_Ruler(int _width, int _height) {
  height = _height;
  width = _width;
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
  Cell **next_gen = init_cells(width, height);

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

          else if ((neighbors == 3) || (neighbors == 2)) {
            next_gen[i][j].update_status(ALIVE);
          }
        }
      }
    }
  }
  cells = next_gen;
  std::cout << "generation: " << generation << std::endl;
  generation++;
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
      if ((i > 0) && (j > 0) && (i < height) && (j < width)) {
        if (((i != x) || (j != y)) && (cells[i][j].get_status() == ALIVE))
          neighbors_alive++;
      }
    }
  }
  // if (neighbors_alive != 0) {
  //   std::cout << "cell " << x << "," << y << " has " << neighbors_alive
  //             << " neighbors alive" << std::endl;
  // }
  return neighbors_alive;
}

bool Game_Ruler::valid_coord(int x, int y) {
  if ((x < height) && (y < width))
    return true;
  return false;
}
