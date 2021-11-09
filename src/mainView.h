#pragma once

#include "view.h"
#include "mesh.h"
#include "toolbar.h"
#include "color.h"
#include "renderer.h"

class MainView : public View {
 private:
  bool isRunningFlag;

  Toolbar *toolbar;
  RenderConfig *renderConfig;
  Renderer *renderer;

  bool goingUp = false;
  bool goingLeft = false;

public:
  MainView(Renderer *renderer);
  virtual ~MainView();

  virtual void setup(App *app, Point<int> _windowSize);
  virtual void update(Controller *controller);
  virtual void draw(DrawManager *drawManager);
  virtual bool isRunning();
  virtual void destroy();
};
