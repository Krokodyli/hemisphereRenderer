#pragma once

#include <functional>

#include "point.h"
#include "drawManager.h"
#include "appConsts.h"
#include "controller.h"
#include "toolbarControl.h"

enum class SliderType {
  FloatPointSlider,
  IntegerSlider
};

class Slider : public ToolbarControl {
 private:
  const SliderTheme *sliderTheme;
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
         float maxValue, SliderType sliderType, std::string label,
         const SliderTheme *sliderTheme);

  void setOnValueChangeHandler(std::function<void(float)> eventHandler);

  virtual void update(Controller *controller);
  virtual void draw(DrawManager *drawManager);
};
