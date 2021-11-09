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
  lightColorRSlider->draw(drawManager);
  lightColorGSlider->draw(drawManager);
  lightColorBSlider->draw(drawManager);
}

void Toolbar::update(Controller *controller) {
  meridianCountSlider->update(controller);
  parallelsCountSlider->update(controller);
  lightColorRSlider->update(controller);
  lightColorGSlider->update(controller);
  lightColorBSlider->update(controller);
}

void Toolbar::setUpEventHandlers(RenderConfig *renderConfig) {
  meridianCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setMeridianCount(val);
  });
  parallelsCountSlider->setOnValueChangeHandler([renderConfig](float val) {
    renderConfig->setParallelCount(val);
  });
  lightColorRSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->getLightColor();
    renderConfig->setLightColor(Color(val, lightColor.getG(),
                                      lightColor.getB()));
  });
  lightColorGSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->getLightColor();
    renderConfig->setLightColor(Color(lightColor.getR(), val,
                                      lightColor.getB()));
  });

  lightColorBSlider->setOnValueChangeHandler([renderConfig](float val) {
    auto lightColor = renderConfig->getLightColor();
    renderConfig->setLightColor(Color(lightColor.getR(), lightColor.getG(),
                                      val));
  });
}

void Toolbar::setUp() {
  meridianCountSlider = new Slider(Point<float>(20, 20), 100,
                                   16, 4, 30, SliderType::IntegerSlider);
  parallelsCountSlider = new Slider(Point<float>(20, 70), 100, 3, 1, 8,
                                   SliderType::IntegerSlider);
  lightColorRSlider = new Slider(Point<float>(20, 120), 100, 255, 0, 255,
                                 SliderType::IntegerSlider);
  lightColorGSlider = new Slider(Point<float>(20, 170), 100, 255, 0, 255,
                                 SliderType::IntegerSlider);
  lightColorBSlider = new Slider(Point<float>(20, 220), 100, 255, 0, 255,
                                 SliderType::IntegerSlider);
}
