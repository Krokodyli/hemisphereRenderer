#pragma once

#include "drawManager.h"
#include "app.h"
#include "controller.h"

class View {
 protected:
  App *app;

  Point<int> windowSize;

 public:
  View();
  virtual ~View();

  virtual void setup(App *_app, Point<int> _windowSize);
  virtual void update(Controller *controller) = 0;
  virtual void draw(DrawManager *drawManager) = 0;
  virtual bool isRunning() = 0;
  virtual void destroy() = 0;
};
