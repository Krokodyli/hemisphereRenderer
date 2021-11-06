#pragma once

#include "view.h"
#include "mesh.h"
#include "toolbar.h"
#include "color.h"

class MainView : public View {
 private:
  bool isRunningFlag;

  Toolbar *toolbar;
  Mesh *mesh;

  void drawMesh(DrawManager *drawManager);
public:
  MainView();
  virtual ~MainView();

  virtual void setup(App *app, Point<int> _windowSize);
  virtual void update(Controller *controller);
  virtual void draw(DrawManager *drawManager);
  virtual bool isRunning();
  virtual void destroy();
};
