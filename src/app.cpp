#include "app.h"
#include "mainView.h"
#include "view.h"
#include <chrono>

App::App()
  : drawManager(nullptr), controller(nullptr), resourceManager(nullptr),
    isAppRunning(false) { }

App::~App() {
  while (!views.empty()) {
    View *view = views.top();
    views.pop();
    delete view;
  }
  if (drawManager != nullptr)
    delete drawManager;
  if (controller != nullptr)
    delete controller;
  if(resourceManager != nullptr)
    delete resourceManager;
}

void App::pushView(View *newView) {
  views.push(newView);
  executeView(views.top());
}

void App::execute() {
  setup();
  executeView(views.top());
}

void App::startClock() {
  clock = std::chrono::system_clock::now();
}

float App::getDeltaTime() {
  std::chrono::duration<float> timeDiff
    = std::chrono::system_clock::now() - clock;
  return timeDiff.count();
}
