#pragma once

#include "app.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class View;

class SFMLApp : public App {
 private:
  static const int framerateLimit = 60;
  static const int windowWidth = 1200;
  static const int windowHeight = 900;
  static const int meshRadius = 320;
  static const int toolbarWidth = 300;
  static const std::string appTitle;

  std::string execPath;
  sf::RenderWindow *window;

  virtual void setup();
  virtual void handleEvents();
  virtual void executeView(View *view);
public:
  SFMLApp(std::string _execPath);
  virtual ~SFMLApp();
};
