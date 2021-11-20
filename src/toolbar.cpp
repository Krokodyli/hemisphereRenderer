#include "toolbar.h"
#include "renderConfig.h"

Toolbar::Toolbar(Point<int> position, Point<int> size)
  : position(position), size(size), backgroundColor(0, 0, 0) { }

Toolbar::~Toolbar() {
  for(auto control : controls)
    delete control;
}

void Toolbar::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(Point<float>(position.x, position.y),
                             Point<float>(size.x, size.y), backgroundColor);

  for (auto control : controls)
    control->draw(drawManager);
}

void Toolbar::update(Controller *controller) {
  for(auto control : controls)
    control->update(controller);
}
