#pragma once

#include "view.h"
#include "mesh.h"
#include "toolbar.h"
#include "color.h"
#include "renderer.h"
#include "lightSpiralMoveHandler.h"
#include "meshVerticesMoveHandler.h"

class MainView : public View {
 private:
  int meshRadius, toolbarWidth;

  bool isRunningFlag;

  Toolbar *toolbar;
  RenderConfig *renderConfig;
  Renderer *renderer;
  ResourceManager *resourceManager;
  float dt;


  LightSpiralMoveHandler lightMoveHandler;
  MeshVerticesMoveHandler verticesMover;

public:
  MainView(Renderer *renderer, Toolbar *toolbar,
           ResourceManager *resourceManager, int meshRadius, int toolbarWidth);
  virtual ~MainView();

  virtual void setup(App *app, Point<int> _windowSize);
  virtual void update(Controller *controller, float dt);
  virtual void draw(DrawManager *drawManager);
  virtual bool isRunning();
  virtual void destroy();
};
