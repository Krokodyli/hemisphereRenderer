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

  float meshX = (windowSize.x - (float)windowSize.x/6) / 2;
  float meshY = 0.5f * windowSize.y;
  float meshRadius = 0.48f * windowSize.y;
  auto mesh = new Mesh(Point3D<float>(meshX, meshY, 0.0f), meshRadius, 3, 16);


  auto initialLightPosition = Point3D<float>(meshX * 1.5, meshY,
                                             meshRadius * 5);
  renderConfig = new RenderConfig(mesh, initialLightPosition,
                                  Color(255, 255, 255), 0.5f);
  toolbar->setUpEventHandlers(renderConfig);

  isRunningFlag = true;
}

void MainView::update(Controller *controller) {
  toolbar->update(controller);

  Point3D<float> lp = renderConfig->getLightPosition();
  float dt = 100;
  if(goingUp) {
    lp.y -= dt;
    if(lp.y < - 200)
      goingUp = false;
  }
  else {
    lp.y += dt;
    if (lp.y > windowSize.y + 200)
      goingUp = true;
  }
  if(goingLeft) {
    lp.x -= dt * 0.5;
    if(lp.x < -200)
      goingLeft = false;
  }
  else {
    lp.x += dt * 0.5;
    if (lp.x > windowSize.x + 200)
      goingLeft = true;
  }
  renderConfig->setLightPosition(lp);
}

void MainView::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(Point<float>(0, 0),
                             Point<float>(windowSize.x, windowSize.y),
                             Color(0, 0, 0));
  renderer->drawOnBitmap(renderConfig);
  renderer->display(renderConfig, drawManager);
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
