#pragma once

#include "drawManager.h"
#include "app.h"
#include "controller.h"
#include <SFML/System/Vector2.hpp>

using sf::Vector2i;

class View {
 protected:
  App *app;

  Vector2i windowSize;

 public:
  virtual ~View();

  virtual void setup(App *_app, Vector2i _windowSize);
  virtual void update(Controller *controller) = 0;
  virtual void draw(DrawManager *drawManager) = 0;
  virtual bool isRunning() = 0;
  virtual void destroy() = 0;
};
