#pragma once

#include <stack>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "drawManager.h"
#include "controller.h"

using std::stack;

class View;

class App {
 private:
  static const int framerateLimit;

  std::string title;
  sf::Vector2i windowSize;
  std::string execPath;

  sf::RenderWindow *window;
  DrawManager *drawManager;
  Controller *controller;


  stack<View *> views;
  bool isAppRunning;

  void setup();
  void handleEvents();
  void executeView(View *view);
 public:
  App(std::string title, sf::Vector2i _windowSize, std::string _execPath);
  ~App();

  void pushView(View *newView);

  void execute();
};
