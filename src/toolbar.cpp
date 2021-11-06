#include "toolbar.h"
#include <iostream>

Toolbar::Toolbar(Point<float> position, Point<float> size)
  : position(position), size(size), backgroundColor(180, 180, 180),
    testSlider(Point<float>(20, 20), 200, 50, 0, 100,
               SliderType::FloatPointSlider) {
  testSlider.setOnValueChangeHandler([](float val) {
    std::cout << val << std::endl;
  });
}

void Toolbar::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(position, size, backgroundColor);
  testSlider.draw(drawManager);
}

void Toolbar::update(Controller *controller) {
  testSlider.update(controller);
}
