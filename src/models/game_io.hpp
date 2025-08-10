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
  SDL_FRect squareOutline;

public:
  Game_IO(int height, int width);
  void handle_events(SDL_Event *event, Cell **cells);
  void init();
  void change_refresh_rate(int refresh_rate);
  void set_canvas_size(float h, float w);
  void render_cells(Cell **cells);
  SDL_Renderer *get_renderer();
  SDL_FRect *get_squareoutline();
  GameIO_Status get_state();

private:
  void handle_keyboard_events(SDL_Keycode keycode, Cell **cells);
  void handle_mouse_events(float x, float y, Cell **cells);
  void print_current_cells(Cell **cells);
  bool is_coord_occupied(float x, float y);
  bool validate_mouse_input(float x, float y);
};
