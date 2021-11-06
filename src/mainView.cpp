#include "mainView.h"

MainView::MainView() : isRunningFlag(false), toolbar(nullptr), mesh(nullptr) { }

MainView::~MainView() {
  destroy();
}

void MainView::setup(App *_app, Point<int> _windowSize) {
  View::setup(_app, _windowSize);
  toolbar = new Toolbar(Point<float>(0.0f, 0.0f),
                        Point<float>((float)windowSize.x/6.0,
                                     (float)windowSize.y));

  float meshX = 7.0f / 12 * windowSize.x;
  float meshY = 0.5f * windowSize.y;
  float meshRadius = 0.48f * windowSize.y;
  mesh = new Mesh(Point3D<float>(meshX, meshY, 0.0f), meshRadius, 3, 16);
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
    auto v1 = Point<float>(edge.a->x, edge.a->y);
    auto v2 = Point<float>(edge.b->x, edge.b->y);
    drawManager->drawLine(v1, v2, Color(255, 255, 255));
  }
}
