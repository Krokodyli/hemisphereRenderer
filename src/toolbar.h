#pragma once

#include "button.h"
#include "checkbox.h"
#include "color.h"
#include "controller.h"
#include "drawManager.h"
#include "point.h"
#include "renderConfig.h"
#include "slider.h"

class Toolbar {
 protected:
  Point<int> position;
  Point<int> size;

  Color backgroundColor;

  std::vector<ToolbarControl*> controls;

  void setUp();
public:
  Toolbar(Point<int> position, Point<int> size);
  virtual ~Toolbar();

  virtual void draw(DrawManager *drawManager);
  virtual void update(Controller *controller);

  virtual void setUpControls() = 0;
  virtual void setUpEventHandlers(RenderConfig *renderConfig) = 0;
};
