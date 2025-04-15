#include "graphics/graphics.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  Graphics g = Graphics();
  g.init();
  g.loop(false);
}
