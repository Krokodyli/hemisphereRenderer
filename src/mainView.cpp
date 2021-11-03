#include "mainView.h"
#include <SFML/System/Vector2.hpp>

MainView::~MainView() {
  destroy();
}

void MainView::setup(App *app, sf::Vector2i _windowSize) {
  View::setup(app, _windowSize);
  windowSize = _windowSize;
  toolbar = new Toolbar(sf::Vector2f(0, 0),
                        sf::Vector2f(windowSize.x/6.0, windowSize.y),
                        sf::Color::White);
}

void MainView::update() { }

void MainView::draw(DrawManager *drawManager) {
  toolbar->draw(drawManager);
}

void MainView::destroy() {
  if (toolbar)
    delete toolbar;

  toolbar = nullptr;
}
