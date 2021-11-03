#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

using sf::Color;
using sf::Vector2f;
using sf::Vector2i;

class DrawManager {
 private:
  Vector2f offset;
  sf::RenderWindow *window;

 public:
  DrawManager(sf::RenderWindow *_window);

  Vector2f getOffset();
  void setOffset(Vector2f newOffset);

  void drawRectangle(Vector2f position, Vector2f size, Color fillColor);
};
