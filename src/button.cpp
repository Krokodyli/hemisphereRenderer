#include "button.h"

Button::Button(Point<float> pos, Point<float> size, std::string label)
  : pos(pos), size(size), label(label) { }

void Button::setOnClickHandler(std::function<void(void)> eventHandler) {
  this->eventHandler = eventHandler;
}

void Button::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(pos, size, fillColor);
  drawManager->drawText(pos + textOffset, label, fontSize, fontColor);
}

void Button::update(Controller *controller) {
  auto mousePos = controller->getMousePos();
  if(controller->isLeftClicked() &&
     mousePos.insideRec(pos.x, pos.y, size.x, size.y)) {
    if(eventHandler)
      eventHandler();
  }
}
