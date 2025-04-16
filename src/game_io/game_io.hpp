#include "../models/cell.hpp"
#include <SDL3/SDL.h>
#include <vector>

#pragma once
enum GameIO_Status {
  RUNNING,
  PAUSED,
  ENDED,
  EDITING,
};

class Game_IO {
private:
  SDL_Window *win;
  SDL_Renderer *ren;
  int refresh_rate = 60;
  GameIO_Status status = ENDED;
  std::vector<Cell *> cells;
  SDL_FRect squareOutline;

public:
  Game_IO();
  void handle_button_events(SDL_Event *event,
                            bool *mouse_wheel_pressed); // Requires cells
  void handle_mousegrab(SDL_MouseMotionEvent coord);    // Requires cells

  // output
  void init();
  void zoom_in();
  void zoom_out();
  void loop(bool quit); // Requires cells
  void change_refresh_rate(int refresh_rate);
  void set_cells(std::vector<Cell *> _cells);

private:
  void render_cells(); // Requires cells
};
