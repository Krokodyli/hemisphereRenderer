#pragma once

#include "point.h"
#include "controller.h"
#include "drawManager.h"
#include "toolbarControl.h"
#include <functional>

class Button : public ToolbarControl {
 private:
  const Color fillColor = Color(255, 255, 255);
  const Color fontColor = Color(0, 0, 0);
  const int fontSize = 12;
  const Point<float> textOffset = Point<float>(4, 1);

  Point<float> pos, size;
  std::string label;

  std::function<void(void)> eventHandler;

 public:
  Button(Point<float> pos, Point<float> size, std::string label);

  void setOnClickHandler(std::function<void(void)> eventHandler);

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);
};
