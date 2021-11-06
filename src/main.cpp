#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

#include "sfmlApp.h"

int main(int argc, char **argv) {
  auto app = new SFMLApp("Triangular mesh hole filling", Point<int>(1200, 900),
                         std::string(argv[0]));
  app->execute();
  return 0;
}
