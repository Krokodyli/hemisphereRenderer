#include "button.h"

Button::Button(Point<float> pos, Point<float> size, Color fillColor,
               Color textColor, int fontSize)
  : pos(pos), size(size), fillColor(fillColor), textColor(textColor),
    fontSize(fontSize) { }

void Button::setOnClickHandler(std::function<void(void)> eventHandler) {
  this->eventHandler = eventHandler;
}

void Button::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(pos, size, fillColor);
  drawManager->drawText(pos, "button", fontSize, Color(255, 255, 255));
}

void Button::update(Controller *controller) {
  auto mousePos = controller->getMousePos();
  if(controller->isLeftClicked() &&
     mousePos.insideRec(pos.x, pos.y, size.x, size.y)) {
    if(eventHandler)
      eventHandler();
  }
}
