#include "toolbar.h"

Toolbar::Toolbar(Point<float> position, Point<float> size)
  : position(position), size(size), backgroundColor(180, 180, 180) { }

void Toolbar::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(position, size, backgroundColor);
}

void Toolbar::update(Controller *controller) { }
