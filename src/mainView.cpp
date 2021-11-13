#include "mainView.h"

MainView::MainView(Renderer *renderer, Toolbar *toolbar,
                   ResourceManager *resourceManager, int meshRadius,
                   int toolbarWidth)
    : meshRadius(meshRadius), toolbarWidth(toolbarWidth), isRunningFlag(false),
      toolbar(toolbar), renderConfig(nullptr), renderer(renderer),
      resourceManager(resourceManager),
      lightMoveHandler(1.0, 100, 800) { }

MainView::~MainView() {
  destroy();
}

void MainView::setup(App *_app, Point<int> _windowSize) {
  View::setup(_app, _windowSize);

  float meshX = (float)(windowSize.x - toolbarWidth) / 2;
  float meshY = 0.5f * windowSize.y;
  auto mesh = new Mesh(Point3D<float>(meshX, meshY, 0.0f), meshRadius, 3, 16);

  renderConfig = new RenderConfig(mesh);
  renderConfig->loadResources(resourceManager);

  toolbar->setUpEventHandlers(renderConfig);

  isRunningFlag = true;
}

void MainView::update(Controller *controller, float dt) {
  toolbar->update(controller);
  this->dt = dt;

  if(renderConfig->getSpiralMoveModeStatus()) {
    Point3D<float> lightPos = renderConfig->getLightPosition();
    Point3D<float> centerPos = renderConfig->getMesh()->getCenter();
    auto newPos = lightMoveHandler.getLightPosition(dt, lightPos, centerPos);
    renderConfig->setLightPosition(newPos);
  }

  controller->setOffset(Point<float>(300, 0)); // TODO
  verticesMover.update(controller, renderConfig);
  controller->setOffset(Point<float>(0, 0));
}

void MainView::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(Point<float>(0, 0),
                             Point<float>(windowSize.x, windowSize.y),
                             Color(0, 0, 0));
  renderer->drawOnBitmap(renderConfig);
  renderer->display(renderConfig, drawManager);
  toolbar->draw(drawManager);
  drawManager->drawText(Point<float>(1000, 100), std::to_string((int)(1 / dt)),
                        20, Color(255, 0, 0));
}

bool MainView::isRunning() {
  return isRunningFlag;
}

void MainView::destroy() {
  if (toolbar)
    delete toolbar;
  toolbar = nullptr;

  if(renderConfig)
    delete renderConfig;
  renderConfig = nullptr;
}
