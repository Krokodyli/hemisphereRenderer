#pragma once

#include <functional>

#include "point.h"
#include "drawManager.h"
#include "controller.h"

enum class SliderType {
  FloatPointSlider,
  IntegerSlider
};

class Slider {
  const Point<float> indicatorSize = Point<float>(10, 20);

  Point<float> pos;
  float width;

  float value;
  float minValue, maxValue;
  SliderType sliderType;

  Point<float> indicatorPos;

  std::function<void(float)> eventHandler;

  bool isIndicatorGrabbed;

  void setValue(float newValue);
  void handleMouseMove(float mouseXPos);
  bool isMouseOverIndicator(Point<float> mousePos);
public:
  Slider(Point<float> pos, float width, float currValue, float minValue,
         float maxValue, SliderType sliderType);

  void setOnValueChangeHandler(std::function<void(float)> eventHandler);

  void update(Controller *controller);
  void draw(DrawManager *drawManager);
};
