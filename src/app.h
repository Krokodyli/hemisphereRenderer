#pragma once

#include <string>
#include <stack>
#include <chrono>

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

  std::chrono::time_point<std::chrono::system_clock> clock;

  virtual void setup() = 0;
  virtual void handleEvents() = 0;
  virtual void executeView(View *view) = 0;

  void startClock();
  float getDeltaTime();
public:
  App(std::string title, Point<int> windowSize);
  virtual ~App();

  virtual void pushView(View *newView);

  virtual void execute();
};
