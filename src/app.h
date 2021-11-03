#pragma once

#include <stack>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "drawManager.h"

using std::stack;

class View;

class App {
 private:
  static const int framerateLimit;

  std::string title;
  sf::Vector2i size;
  std::string execPath;

  sf::RenderWindow *window;
  DrawManager *drawManager;

  stack<View *> views;

  bool isRunning;

  void setup();
  void draw();
  void update();
  void handleEvents();
 public:
  App(std::string title, sf::Vector2i _size, std::string _execPath);
  ~App();

  void pushView(View *newView);
  void popView();

  void execute();
};
