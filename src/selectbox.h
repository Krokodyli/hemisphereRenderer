#pragma once

#include "toolbarControl.h"
#include "button.h"

class Selectbox : public ToolbarControl {
 private:
  const Color fontColor = Color(255, 255, 255);
  const int fontSize = 12;
  const Point<float> buttonSize = Point<float>(15, 15);
  const float buttonGap = 10;
  const float textWidth = 150;
  const unsigned int maxStringSize = 21;

  Point<float> pos;
  std::string label;

  Button previous, next;

  std::vector<std::string> elements;
  int currElement;

  std::function<void(std::string val)> eventHandler;

  void tryToInvokeEventHandler();
 public:
  Selectbox(Point<float> pos, std::string label);

  void setOnChangeHandler(std::function<void(std::string val)> eventHandler);
  void setElements(std::vector<std::string> newElements);

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);
};
