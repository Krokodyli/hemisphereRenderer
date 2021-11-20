#pragma once

#include "controller.h"
#include "drawManager.h"

class ToolbarControl {
 public:
  virtual ~ToolbarControl();
  virtual void draw(DrawManager *drawManager) = 0;
  virtual void update(Controller *controller) = 0;
};
