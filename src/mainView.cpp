#include "mainView.h"

MainView::MainView(Renderer *renderer)
  : isRunningFlag(false), toolbar(nullptr),
    renderConfig(nullptr), renderer(renderer) { }

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
  auto mesh = new Mesh(Point3D<float>(meshX, meshY, 0.0f), meshRadius, 3, 16);

  renderConfig = new RenderConfig(mesh);
  toolbar->setUpEventHandlers(renderConfig);

  isRunningFlag = true;
}

void MainView::update(Controller *controller) {
  toolbar->update(controller);
}

void MainView::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(Point<float>(0, 0),
                             Point<float>(windowSize.x, windowSize.y),
                             Color(0, 0, 0));
  renderer->drawOnBitmap(renderConfig);
  renderer->displayBitmap(renderConfig, drawManager);
  toolbar->draw(drawManager);
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
