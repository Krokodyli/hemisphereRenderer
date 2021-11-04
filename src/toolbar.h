#pragma once

#include <SFML/Graphics/Color.hpp>
#include "controller.h"
#include "drawManager.h"

class Toolbar {
 private:
  Vector2f position;
  Vector2f size;
  sf::Color backgroundColor;

 public:
  Toolbar(Vector2f _position, Vector2f _size, sf::Color _backgroundColor);

  void draw(DrawManager *drawManager);
  void update(Controller *controller);
};
