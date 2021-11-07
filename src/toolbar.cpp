#include "toolbar.h"
#include "renderConfig.h"

Toolbar::Toolbar(Point<float> position, Point<float> size)
  : position(position), size(size), backgroundColor(180, 180, 180),
    meridianCountSlider(nullptr), parallelsCountSlider(nullptr) {
  setUp();
}

Toolbar::~Toolbar() {
  if(meridianCountSlider)
    delete meridianCountSlider;
  if (parallelsCountSlider)
    delete parallelsCountSlider;
}

void Toolbar::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(position, size, backgroundColor);
  meridianCountSlider->draw(drawManager);
  parallelsCountSlider->draw(drawManager);
}

void Toolbar::update(Controller *controller) {
  meridianCountSlider->update(controller);
  parallelsCountSlider->update(controller);
}

void Toolbar::setUpEventHandlers(RenderConfig *renderConfig) {
  meridianCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setMeridianCount(val);
  });
  parallelsCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setParallelCount(val);
  });
}

void Toolbar::setUp() {
  meridianCountSlider = new Slider(Point<float>(20, 20), 100,
                                   16, 4, 30, SliderType::IntegerSlider);
  parallelsCountSlider = new Slider(Point<float>(20, 120), 100, 3, 1, 8,
                                   SliderType::IntegerSlider);
}
