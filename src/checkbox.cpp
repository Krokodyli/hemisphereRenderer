#include "checkbox.h"

Checkbox::Checkbox(Point<float> pos, bool initialState, std::string label)
  : pos(pos), isActivated(initialState), label(label) {}

Checkbox::~Checkbox() {}

void Checkbox::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(pos, Point<float>(size, size), boxColor);

  if(isActivated) {
    Point<float> v1 = pos, v2 = pos;
    v2.x += size;
    v2.y += size;
    drawManager->drawLine(v1, v2, crossColor);
    v1.y += size;
    v2.y -= size;
    drawManager->drawLine(v1, v2, crossColor);
  }

  if (label != "") {
    auto labelPos = pos + labelOffset;
    drawManager->drawText(labelPos, label, 12, fontColor);
  }
}

void Checkbox::setOnValueChangeHandler(std::function<void(bool)> eventHandler) {
  this->eventHandler = eventHandler;
  if(eventHandler)
    eventHandler(isActivated);
}

void Checkbox::update(Controller *controller) {
  if(isCheckboxClicked(controller)) {
    isActivated = !isActivated;
    if(eventHandler)
      eventHandler(isActivated);
  }
}

bool Checkbox::isCheckboxClicked(Controller *controller) {
  return controller->isLeftClicked()
    && controller->getMousePos().insideRec(pos.x, pos.y, size, size);
}
