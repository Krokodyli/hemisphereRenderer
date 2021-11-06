#include "toolbar.h"
#include <iostream>

Toolbar::Toolbar(Point<float> position, Point<float> size)
  : position(position), size(size), backgroundColor(180, 180, 180),
    testSlider(Point<float>(20, 20), 200, 50, 0, 100,
               SliderType::FloatPointSlider),
    testButton(Point<float>(20, 120), Point<float>(110, 40),
               Color(255, 0, 0), Color(255, 255, 255), 30) {
  testSlider.setOnValueChangeHandler([](float val) {
    std::cout << val << std::endl;
  });
  testButton.setOnClickHandler([]() {
    std::cout << "Button clicked\n";
  });
}

void Toolbar::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(position, size, backgroundColor);
  testSlider.draw(drawManager);
  testButton.draw(drawManager);
}

void Toolbar::update(Controller *controller) {
  testSlider.update(controller);
  testButton.update(controller);
}
