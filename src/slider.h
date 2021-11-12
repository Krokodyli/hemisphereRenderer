#pragma once

#include <functional>

#include "point.h"
#include "drawManager.h"
#include "controller.h"
#include "toolbarControl.h"

enum class SliderType {
  FloatPointSlider,
  IntegerSlider
};

class Slider : public ToolbarControl {
  const Point<float> indicatorSize = Point<float>(10, 20);
  const Point<float> barSize = Point<float>(100, 5);
  const Color indicatorColor = Color(255, 255, 255);
  const Color barColor = Color(255, 255, 255);
  const Point<float> labelOffset = Point<float>(120, 0);
  const int fontSize = 12;
  const Color fontColor = Color(255, 255, 255);

  Point<float> pos;

  float value;
  float minValue, maxValue;
  SliderType sliderType;

  std::string label;

  Point<float> indicatorPos;

  std::function<void(float)> eventHandler;

  bool isIndicatorGrabbed;

  void setValue(float newValue);
  void handleMouseMove(float mouseXPos);
  bool isMouseOverIndicator(Point<float> mousePos);
public:
  Slider(Point<float> pos, float currValue, float minValue,
         float maxValue, SliderType sliderType, std::string label);

  void setOnValueChangeHandler(std::function<void(float)> eventHandler);

  virtual void update(Controller *controller);
  virtual void draw(DrawManager *drawManager);
};
