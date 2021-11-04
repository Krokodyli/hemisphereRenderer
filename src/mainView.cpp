#include "mainView.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

MainView::MainView() : isRunningFlag(false), toolbar(nullptr), mesh(nullptr) { }

MainView::~MainView() {
  destroy();
}

void MainView::setup(App *_app, Vector2i _windowSize) {
  View::setup(_app, _windowSize);
  toolbar = new Toolbar(sf::Vector2f(0, 0),
                        sf::Vector2f((float)windowSize.x/6.0, windowSize.y),
                        Color::White);

  float meshX = 7.0f / 12 * windowSize.x;
  float meshY = 0.5f * windowSize.y;
  float meshRadius = 0.48f * windowSize.y;
  mesh = new Mesh(sf::Vector3f(meshX, meshY, 0.0f), meshRadius, 3, 16);
  isRunningFlag = true;
}

void MainView::update(Controller *controller) {
  controller->update();
}

void MainView::draw(DrawManager *drawManager) {
  toolbar->draw(drawManager);
  drawMesh(drawManager);
}

bool MainView::isRunning() {
  return isRunningFlag;
}

void MainView::destroy() {
  if (toolbar)
    delete toolbar;

  toolbar = nullptr;
}

void MainView::drawMesh(DrawManager *drawManager) {
  for(auto edge : mesh->getEdges()) {
    auto v1 = sf::Vector2f(edge.a->x, edge.a->y);
    auto v2 = sf::Vector2f(edge.b->x, edge.b->y);
    drawManager->drawLine(v1, v2, Color::White);
  }
}
