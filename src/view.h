#pragma once

#include "drawManager.h"
#include "app.h"
#include <SFML/System/Vector2.hpp>

using sf::Vector2i;

class View {
 public:
  virtual ~View();

  virtual void setup(App *app, sf::Vector2i windowSize) = 0;

  virtual void update() = 0;

  virtual void draw(DrawManager *drawManager) = 0;

  virtual void destroy() = 0;
};
