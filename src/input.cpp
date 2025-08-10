#include "cmath"
#include "models/game_io.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_rect.h>
#include <iostream>

// Rounds both x and y to a multiple of 10
void normalize_coord(float *x, float *y) {
  int iX = std::round(*x);
  int iY = std::round(*y);
  std::string strX = std::to_string(iX);
  std::string strY = std::to_string(iY);
  int lenX = strX.length();
  int lenY = strY.length();
  strX[lenX - 1] = '0';
  strY[lenY - 1] = '0';
  *x = std::stof(strX);
  *y = std::stof(strY);
}

Cell createCell(float x, float y, SDL_Renderer *renderer, cell_status status) {
  std::cout << "original: " << x << "," << y << std::endl;
  normalize_coord(&x, &y);
  std::cout << "created at: " << x << "," << y << std::endl;

  Cell cell = Cell{x, y, status};
  return cell;
}

bool Game_IO::validate_mouse_input(float x, float y) {
  float scale_x;
  float scale_y;

  SDL_GetRenderScale(ren, &scale_x, &scale_y);

  if (status == EDITING) {
    if ((x / scale_x > squareOutline.w - squareOutline.x * -1) ||
        (x / scale_x < squareOutline.x))
      return false;
    else if ((y / scale_y > squareOutline.h - squareOutline.y * -1) ||
             (y / scale_y < squareOutline.y))
      return false;
    return true;
  }
  return false;
}

void Game_IO::handle_events(SDL_Event *event, Cell **cells) {
  while (SDL_PollEvent(event)) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
      std::cout << "closing" << std::endl;
      status = ENDED;
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      handle_mouse_events(event->button.x, event->button.y, cells);
      break;
    case SDL_EVENT_KEY_DOWN:
      handle_keyboard_events(event->key.key, cells);
      break;
    }
  }
}

void Game_IO::handle_keyboard_events(SDL_Keycode keycode, Cell **cells) {
  if (keycode == SDLK_Q)
    status = ENDED;
  else if (keycode == SDLK_P)
    status = PAUSED;
  else if (keycode == SDLK_E)
    status = EDITING;
  else if (keycode == SDLK_R)
    status = RUNNING;
  else if (keycode == SDLK_C)
    print_current_cells(cells);
}

void Game_IO::handle_mouse_events(float x, float y, Cell **cells) {
  std::cout << "mouse button down at position: " << x << "," << y << std::endl;

  bool valid_input = validate_mouse_input(x, y);
  if (valid_input) {
    normalize_coord(&x, &y);
    int int_x = static_cast<int>(x);
    int int_y = static_cast<int>(y);
    if (cells[int_x][int_y].get_status() == ALIVE)
      cells[int_x][int_y].update_status(DEAD);
    else
      cells[int_x][int_y].update_status(ALIVE);
    std::cout << "cell created at " << int_x << "," << int_y << std::endl;
  }
}
