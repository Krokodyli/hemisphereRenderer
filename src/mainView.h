#pragma once

#include "view.h"
#include "mesh.h"
#include "toolbar.h"
#include "color.h"
#include "renderer.h"
#include "lightSpiralMoveHandler.h"
#include "meshVerticesMoveHandler.h"
#include "appConsts.h"

class MainView : public View {
 private:
  AppConsts *appConsts;

  bool isRunningFlag;

  Toolbar *toolbar;
  RenderConfig *renderConfig;
  Renderer *renderer;
  ResourceManager *resourceManager;

  int fps;

  LightSpiralMoveHandler lightMoveHandler;
  MeshVerticesMoveHandler verticesMover;

  void drawBackground(DrawManager *drawManager);
  void drawFPSLabel(DrawManager *drawManager);
  void moveLightSource(float dt);
public:
  MainView(Renderer *renderer, Toolbar *toolbar,
           ResourceManager *resourceManager, AppConsts *appConsts);
  virtual ~MainView();

  virtual void setup();
  virtual void update(Controller *controller, float dt);
  virtual void draw(DrawManager *drawManager);
  virtual bool isRunning();
  virtual void destroy();
};
