#pragma once

#include "point.h"
#include "controller.h"
#include "drawManager.h"
#include <functional>

class Button {
 private:
  Point<float> pos, size;
  Color fillColor, textColor;
  int fontSize;

  std::function<void(void)> eventHandler;

 public:
  Button(Point<float> pos, Point<float> size, Color fillColor,
         Color textColor, int fontSize);

  void setOnClickHandler(std::function<void(void)> eventHandler);

  void draw(DrawManager *drawManager);
  void update(Controller *controller);
};
