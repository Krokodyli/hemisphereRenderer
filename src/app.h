#pragma once

#include <string>
#include <stack>

#include "point.h"
#include "drawManager.h"
#include "controller.h"

class View;

class App {
 protected:
  std::string title;
  Point<int> windowSize;

  DrawManager *drawManager;
  Controller *controller;

  std::stack<View*> views;
  bool isAppRunning;

  virtual void setup() = 0;
  virtual void handleEvents() = 0;
  virtual void executeView(View *view) = 0;
 public:
  App(std::string title, Point<int> windowSize);
  virtual ~App();

  virtual void pushView(View *newView);

  virtual void execute();
};
