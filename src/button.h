#pragma once

#include "point.h"
#include "controller.h"
#include "drawManager.h"
#include "toolbarControl.h"
#include <functional>
#include "appConsts.h"

class Button : public ToolbarControl {
 private:
  const ButtonTheme *buttonTheme;

  Point<float> pos, size;
  std::string label;

  std::function<void(void)> eventHandler;

 public:
  Button(Point<float> pos, Point<float> size, std::string label,
         const ButtonTheme *buttonTheme);

  void setOnClickHandler(std::function<void(void)> eventHandler);

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);
};
