#include "slider.h"
#include "color.h"

Slider::Slider(Point<float> pos, float width, float currValue,
               float minValue, float maxValue,
               SliderType sliderType)
  : pos(pos), width(width), value(currValue), minValue(minValue),
    maxValue(maxValue), sliderType(sliderType), indicatorPos(0, 0),
    eventHandler(nullptr), isIndicatorGrabbed(false) {
  setValue(currValue);
}

void Slider::setOnValueChangeHandler(std::function<void(float)> eventHandler) {
  this->eventHandler = eventHandler;
}

void Slider::update(Controller *controller) {
  auto mousePos = controller->getMousePos();

  if(!isIndicatorGrabbed) {
    if(controller->isLeftPressed() && isMouseOverIndicator(mousePos))
      isIndicatorGrabbed = true;
  }
  else {
    if(!controller->isLeftPressed())
      isIndicatorGrabbed = false;
    else
      handleMouseMove(mousePos.x);
  }
}

void Slider::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(pos, Point<float>(width, 5), Color(255, 0, 0));
  drawManager->drawRectangle(indicatorPos, indicatorSize, Color(0, 255, 0));
}

void Slider::setValue(float newValue) {
  value = newValue;
  value = std::max(minValue, value);
  value = std::min(maxValue, value);
  if(sliderType == SliderType::IntegerSlider)
    value = round(value);
  indicatorPos.x = pos.x - indicatorSize.x / 2 +
    (value - minValue) / (maxValue - minValue) * width;
  indicatorPos.y = pos.y - indicatorSize.y / 2;
}

void Slider::handleMouseMove(float mouseXPos) {
  mouseXPos = std::max(pos.x, mouseXPos);
  mouseXPos = std::min(pos.x + width, mouseXPos);
  auto newValue = minValue + (maxValue - minValue) * (mouseXPos - pos.x) / width;
  if (newValue != value) {
    setValue(newValue);
    if (eventHandler)
      eventHandler(value);
  }
}

bool Slider::isMouseOverIndicator(Point<float> mousePos) {
  return mousePos.insideRec(indicatorPos.x, indicatorPos.y,
                            indicatorSize.x, indicatorSize.y);
}
