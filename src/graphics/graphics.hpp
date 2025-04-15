#include <SDL3/SDL.h>
#include <iostream>
#pragma once

class Graphics {
private:
  SDL_Window *win;
  SDL_Renderer *ren;
  int refresh_rate = 60;

public:
  Graphics();
  void init();
  void render_cell();
  void zoom_in();
  void zoom_out();
  void loop(bool quit);
  void change_refresh_rate(int refresh_rate);
};
