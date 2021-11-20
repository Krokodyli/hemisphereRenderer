#pragma once

#include "app.h"
#include "appConsts.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class View;

class SFMLApp : public App {
 private:
  AppConsts appConsts;

  std::string execPath;
  sf::RenderWindow *window;

  virtual void setup();
  virtual void handleEvents();
  virtual void executeView(View *view);
public:
  SFMLApp(std::string _execPath);
  virtual ~SFMLApp();
};
