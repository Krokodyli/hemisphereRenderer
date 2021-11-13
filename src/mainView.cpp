#include "mainView.h"

MainView::MainView(Renderer *renderer, Toolbar *toolbar,
                   ResourceManager *resourceManager, AppConsts *appConsts)
  : appConsts(appConsts), isRunningFlag(false),
    toolbar(toolbar), renderConfig(nullptr), renderer(renderer),
    resourceManager(resourceManager),
    lightMoveHandler(appConsts->spiralMovePeriodTime,
                     appConsts->spiralMovePeriodDistance,
                     appConsts->spiralMoveRange),
    verticesMover(appConsts) { }

MainView::~MainView() {
  destroy();
}

void MainView::setup() {
  auto mesh = new Mesh(Point3D<float>(appConsts->relativeMeshPos.x,
                                      appConsts->relativeMeshPos.y,
                                      appConsts->meshZPos),
                       appConsts->meshRadius,
                       appConsts->defaultParallelCount,
                       appConsts->defaultMeridianCount);

  renderConfig = new RenderConfig(mesh, appConsts);
  renderConfig->loadResources(resourceManager);

  toolbar->setUpEventHandlers(renderConfig);

  isRunningFlag = true;
}

void MainView::update(Controller *controller, float dt) {
  auto oldOffset = controller->getOffset();
  fps = 1/dt;

  controller->setOffset(appConsts->toolbarPos);
  toolbar->update(controller);

  controller->setOffset(appConsts->canvasPos);
  verticesMover.update(controller, renderConfig);

  controller->setOffset(oldOffset);

  moveLightSource(dt);
}

void MainView::draw(DrawManager *drawManager) {
  drawBackground(drawManager);

  renderer->drawOnBitmap(renderConfig);
  renderer->display(renderConfig, drawManager);
  toolbar->draw(drawManager);

  drawFPSLabel(drawManager);
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

void MainView::drawBackground(DrawManager *drawManager) {
  drawManager->drawRectangle(
      Point<float>(0, 0),
      Point<float>(appConsts->windowSize.x, appConsts->windowSize.y),
      appConsts->canvasColor);
}

void MainView::drawFPSLabel(DrawManager *drawManager) {
  if (appConsts->showFPS) {
    drawManager->drawText(appConsts->fpsLabelPosition, std::to_string(fps),
                          appConsts->fpsLabelFontSize,
                          appConsts->fpsLabelColor);
  }
}

void MainView::moveLightSource(float dt) {
  if (renderConfig->spiralMoveMode) {
    Point3D<float> lightPos = renderConfig->lightPosition;
    Point3D<float> centerPos = renderConfig->mesh->getCenter();
    auto newPos = lightMoveHandler.getLightPosition(dt, lightPos, centerPos);
    renderConfig->lightPosition = newPos;
  }
}
