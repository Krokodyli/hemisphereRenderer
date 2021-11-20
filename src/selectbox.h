#pragma once

#include "toolbarControl.h"
#include "button.h"

class Selectbox : public ToolbarControl {
 private:
  const SelectboxTheme *theme;

  Point<float> pos;
  std::string label;

  Button previous, next;

  std::vector<std::string> elements;
  int currElement;

  std::function<void(std::string val)> eventHandler;

  void tryToInvokeEventHandler();
 public:
  Selectbox(Point<float> pos, std::string label, const SelectboxTheme *theme);

  void setOnChangeHandler(std::function<void(std::string val)> eventHandler);
  void setElements(std::vector<std::string> newElements);

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);
};
