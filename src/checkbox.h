#pragma once

#include "toolbarControl.h"
#include <functional>

class Checkbox : public ToolbarControl {
 private:
  const float size = 20;
  const Point<float> labelOffset = Point<float>(30, 4);
  const Color boxColor = Color(255, 255, 255);
  const Color crossColor = Color(0, 0, 0);
  const int fontSize = 12;
  const Color fontColor = Color(255, 255, 255);

  Point<float> pos;
  bool isActivated;

  std::string label;

  std::function<void(bool)> eventHandler;

  bool isCheckboxClicked(Controller *controller);

 public:
  Checkbox(Point<float> pos, bool initialState, std::string label);
  virtual ~Checkbox();

  void setOnValueChangeHandler(std::function<void(bool)> eventHandler);

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);
};
