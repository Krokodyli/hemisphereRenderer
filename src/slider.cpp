#include "slider.h"
#include "color.h"

Slider::Slider(Point<float> pos, float currValue, float minValue,
               float maxValue, SliderType sliderType, std::string label)
  : pos(pos), value(currValue), minValue(minValue),
    maxValue(maxValue), sliderType(sliderType), label(label),
    indicatorPos(0, 0), eventHandler(nullptr), isIndicatorGrabbed(false) {
  setValue(currValue);
}

void Slider::setOnValueChangeHandler(std::function<void(float)> eventHandler) {
  this->eventHandler = eventHandler;
  if(eventHandler)
    eventHandler(value);
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
  drawManager->drawRectangle(pos, Point<float>(barSize.x, barSize.y), barColor);
  drawManager->drawRectangle(indicatorPos, indicatorSize, indicatorColor);
  drawManager->drawText(pos + labelOffset, label, fontSize, fontColor);
}

void Slider::setValue(float newValue) {
  value = newValue;
  value = std::max(minValue, value);
  value = std::min(maxValue, value);
  if(sliderType == SliderType::IntegerSlider)
    value = round(value);
  indicatorPos.x = pos.x - indicatorSize.x / 2 +
    (value - minValue) / (maxValue - minValue) * barSize.x;
  indicatorPos.y = pos.y - indicatorSize.y / 2;
}

void Slider::handleMouseMove(float mouseXPos) {
  mouseXPos = std::max(pos.x, mouseXPos);
  mouseXPos = std::min(pos.x + barSize.x, mouseXPos);
  auto newValue = minValue
    + (maxValue - minValue) * (mouseXPos - pos.x) / barSize.x;
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
