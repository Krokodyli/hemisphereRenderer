#pragma once

#include "view.h"
#include "mesh.h"
#include "toolbar.h"
#include <SFML/System/Vector2.hpp>

using sf::Vector2i;
using sf::Color;

class MainView : public View {
 private:
  bool isRunningFlag;

  Toolbar *toolbar;
  Mesh *mesh;

  void drawMesh(DrawManager *drawManager);
public:
  MainView();
  virtual ~MainView();

  virtual void setup(App *app, Vector2i _windowSize);
  virtual void update();
  virtual void draw(DrawManager *drawManager);
  virtual bool isRunning();
  virtual void destroy();
};
