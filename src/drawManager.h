#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include "resourceManager.h"

using sf::Color;
using sf::Vector2f;
using sf::Vector2i;

class DrawManager {
 private:
  Vector2f offset;
  sf::RenderWindow *window;

  ResourceManager resourceManager;

 public:
  DrawManager(sf::RenderWindow *_window, std::string _execPath);

  Vector2f getOffset();
  void setOffset(Vector2f newOffset);

  void drawRectangle(Vector2f position, Vector2f size, Color fillColor);
  void drawLine(Vector2f v1, Vector2f v2, Color color);
};
