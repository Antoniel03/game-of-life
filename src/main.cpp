#include "game_io/game_io.hpp"
#include "models/cell.hpp"
#include "models/game_ruler.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Game_IO g = Game_IO();
  // g.set_cells(cells);
  g.init();
  g.set_canvas_size(600, 800);
  SDL_FRect *squareOutline = g.get_squareoutline();

  g.init_cells();

  Game_Ruler gr = Game_Ruler(squareOutline->h, squareOutline->w);
  gr.set_matrix(g.get_cells());

  SDL_Event event;
  bool mouse_wheel_pressed = false;
  SDL_Renderer *ren = g.get_renderer();
  int refresh_rate = 20;

  while (g.get_state() != ENDED) {
    g.handle_button_events(&event, &mouse_wheel_pressed);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    g.render_cells();
    SDL_SetRenderDrawColor(ren, 100, 200, 150, 255);
    SDL_RenderRect(ren, squareOutline);
    SDL_RenderPresent(ren);
    SDL_Delay(refresh_rate);
    if (g.get_state() == RUNNING)
      gr.process_next_generation();
    g.set_cells(gr.getMatrix());
  }
  // g.loop(false);
}
