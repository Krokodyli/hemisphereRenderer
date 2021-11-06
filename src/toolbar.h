#pragma once

#include "point.h"
#include "color.h"
#include "drawManager.h"
#include "controller.h"

class Toolbar {
 private:
  Point<float> position;
  Point<float> size;

  Color backgroundColor;

 public:
  Toolbar(Point<float> position, Point<float> size);

  void draw(DrawManager *drawManager);
  void update(Controller *controller);
};
