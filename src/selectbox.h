#pragma once

#include "toolbarControl.h"
#include "button.h"

class Selectbox {
 private:
  Button next, previous;

  std::function<void(std::string val)> eventHandler;
 public:
  Selectbox(Point<float> pos, std::string label);

  void setOnChangeHandler(std::function<void(std::string val)> eventHandler);

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);
};
