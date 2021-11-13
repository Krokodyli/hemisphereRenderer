#include "checkbox.h"

Checkbox::Checkbox(Point<float> pos, bool initialState, std::string label,
                   const CheckboxTheme *theme)
  : theme(theme), pos(pos), isActivated(initialState), label(label) {}

Checkbox::~Checkbox() {}

void Checkbox::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(pos, Point<float>(theme->size, theme->size),
                             theme->boxColor);

  if(isActivated) {
    Point<float> v1 = pos, v2 = pos;
    v2.x += theme->size;
    v2.y += theme->size;
    drawManager->drawLine(v1, v2, theme->crossColor);
    v1.y += theme->size;
    v2.y -= theme->size;
    drawManager->drawLine(v1, v2, theme->crossColor);
  }

  if (label != "") {
    auto labelPos = pos + theme->labelOffset;
    drawManager->drawText(labelPos, label, 12, theme->fontColor);
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
    && controller->getMousePos().insideRec(pos.x, pos.y, theme->size,
                                           theme->size);
}
