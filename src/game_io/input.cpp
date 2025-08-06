#include "cmath"
#include "game_io.hpp"
#include <SDL3/SDL_rect.h>
#include <iostream>

Cell *createCell(float x, float y, SDL_Renderer *renderer) {
  std::cout << "original: " << x << "," << y << std::endl;
  int iX = std::round(x);
  int iY = std::round(y);
  std::string strX = std::to_string(iX);
  std::string strY = std::to_string(iY);
  int lenX = strX.length();
  int lenY = strY.length();
  strX[lenX - 1] = '0';
  strY[lenY - 1] = '0';
  x = std::stof(strX);
  y = std::stof(strY);
  std::cout << "created at: " << x << "," << y << std::endl;

  Cell *cell = new Cell{x, y};
  return cell;
}

bool validate_mouse_input(float x, float y, GameIO_Status status,
                          SDL_Renderer *ren, SDL_FRect squareOutline) {
  float scale_x;
  float scale_y;

  SDL_GetRenderScale(ren, &scale_x, &scale_y);

  if (status == EDITING) {
    if ((x / scale_x > squareOutline.w - squareOutline.x * -1) ||
        (x / scale_x < squareOutline.x))
      // std::cout << "Outside x" << std::endl;
      return false;
    else if ((y / scale_y > squareOutline.h - squareOutline.y * -1) ||
             (y / scale_y < squareOutline.y))
      return false;
    // std::cout << "Outside y" << std::endl;
    return true;
  }
  return false;
}

void Game_IO::handle_button_events(SDL_Event *event,
                                   bool *mouse_wheel_pressed) {
  while (SDL_PollEvent(event)) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
      std::cout << "closing" << std::endl;
      status = ENDED;
      break;

    case SDL_EVENT_MOUSE_MOTION:
      if (*mouse_wheel_pressed) {
        std::cout << "grabbing, current position: " << event->button.x << ","
                  << event->button.y << std::endl;
        std::cout << "motion: " << event->motion.xrel << ","
                  << event->motion.yrel << std::endl;

        handle_mousegrab(event->motion);
      }
      break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
      if (+event->button.button == 2) {
        *mouse_wheel_pressed = true;
      } else {
        std::cout << "mouse button down at position: " << event->button.x << ","
                  << event->button.y << std::endl;
        bool valid_input = validate_mouse_input(
            event->button.x, event->button.y, status, ren, this->squareOutline);
        if (valid_input) {
          float scale_x;
          float scale_y;
          SDL_GetRenderScale(ren, &scale_x, &scale_y);
          Cell *c = createCell(event->button.x / scale_x,
                               event->button.y / scale_y, ren);
          cells.push_back(c);
        }
      }
      break;
    case SDL_EVENT_KEY_DOWN:
      if (event->key.key == SDLK_Q)
        status = ENDED;
      if (event->key.key == SDLK_P)
        status = PAUSED;
      if (event->key.key == SDLK_E)
        status = EDITING;
      if (event->key.key == SDLK_R)
        status = RUNNING;

      break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
      *mouse_wheel_pressed = false;
      std::cout << "Mouse button lifted" << std::endl;
      break;

    case SDL_EVENT_MOUSE_WHEEL:
      if (event->wheel.y == 1) {
        zoom_in();
      } else {
        zoom_out();
      }
      std::cout << "mouse scroll data: " << event->wheel.y << std::endl;
      break;
    }
  }
}
void Game_IO::handle_mousegrab(SDL_MouseMotionEvent coord) {

  int size = cells.size();
  for (int i = 0; i < size; i++) {
    SDL_FRect *rect = cells[i]->get_cell_graphic();
    rect->x += 10 * coord.xrel;
    rect->y += 10 * coord.yrel;
  }
  squareOutline.x += 10 * coord.xrel;
  squareOutline.y += 10 * coord.yrel;
}
