#pragma once

#include "drawManager.h"
#include "app.h"
#include "controller.h"

class View {
 public:
  View();
  virtual ~View();

  virtual void setup();
  virtual void update(Controller *controller, float dt) = 0;
  virtual void draw(DrawManager *drawManager) = 0;
  virtual bool isRunning() = 0;
  virtual void destroy() = 0;
};
