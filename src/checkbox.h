#pragma once

#include "toolbarControl.h"
#include "appConsts.h"
#include <functional>

class Checkbox : public ToolbarControl {
 private:
  const CheckboxTheme *theme;

  Point<float> pos;
  bool isActivated;

  std::string label;

  std::function<void(bool)> eventHandler;

  bool isCheckboxClicked(Controller *controller);

 public:
  Checkbox(Point<float> pos, bool initialState, std::string label,
           const CheckboxTheme *theme);
  virtual ~Checkbox();

  void setOnValueChangeHandler(std::function<void(bool)> eventHandler);

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);
};
