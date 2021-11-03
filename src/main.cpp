#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

#include "app.h"

int main(int argc, char **argv) {
  App app("Triangular mesh hole filling", sf::Vector2i(1200, 900),
          std::string(argv[0]));
  app.execute();
  return 0;
}
