#include "models/game_io.hpp"
#include "models/game_rules.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  Game_IO g = Game_IO(700, 1000);
  g.init();
  SDL_FRect *squareOutline = g.get_squareoutline();

  Game_Rules gr = Game_Rules(squareOutline->h, squareOutline->w);

  SDL_Event event;
  SDL_Renderer *ren = g.get_renderer();
  int refresh_rate = 20;

  while (g.get_state() != ENDED) {
    g.handle_events(&event, gr.getMatrix());
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    g.render_cells(gr.getMatrix());
    SDL_SetRenderDrawColor(ren, 100, 200, 150, 255);
    SDL_RenderRect(ren, squareOutline);
    SDL_RenderPresent(ren);
    SDL_Delay(refresh_rate);
    if (g.get_state() == RUNNING)
      gr.process_next_generation();
  }
  gr.free_cells();
}
