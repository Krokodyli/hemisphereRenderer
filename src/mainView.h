#pragma once

#include "view.h"
#include "toolbar.h"
#include <SFML/System/Vector2.hpp>

using sf::Vector2i;

class MainView : public View {
 private:
  Vector2i windowSize;

  Toolbar *toolbar;

public:
  virtual ~MainView();

  virtual void setup(App *app, Vector2i _windowSize);

  virtual void update();

  virtual void draw(DrawManager *drawManager);

  virtual void destroy();
};
