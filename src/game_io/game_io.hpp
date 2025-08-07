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
  Cell **cells;
  SDL_FRect squareOutline;

public:
  Game_IO();
  void handle_button_events(SDL_Event *event,
                            bool *mouse_wheel_pressed); // Requires cells
  void handle_mousegrab(SDL_MouseMotionEvent coord);    // Requires cells

  // output
  void init();
  void init_cells();
  void zoom_in();
  void zoom_out();
  void loop(bool quit); // Requires cells
  void change_refresh_rate(int refresh_rate);
  void set_cells(Cell **_cells);
  void set_canvas_size(float h, float w);

private:
  void render_cells(); // Requires cells
  void print_current_cells();
  bool is_coord_occupied(float x, float y);
  bool validate_mouse_input(float x, float y, GameIO_Status status,
                            SDL_Renderer *ren, SDL_FRect squareOutline);
};
