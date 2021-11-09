#pragma once

#include "point.h"
#include "color.h"
#include "drawManager.h"
#include "controller.h"
#include "slider.h"
#include "button.h"
#include "renderConfig.h"

class Toolbar {
 private:
  Point<float> position;
  Point<float> size;

  Color backgroundColor;

  Slider *meridianCountSlider;
  Slider *parallelsCountSlider;

  Slider *lightColorRSlider;
  Slider *lightColorGSlider;
  Slider *lightColorBSlider;

  Slider *kdSlider;

  void setUp();
public:
  Toolbar(Point<float> position, Point<float> size);
  ~Toolbar();

  void draw(DrawManager *drawManager);
  void update(Controller *controller);

  void setUpEventHandlers(RenderConfig *renderConfig);
};
