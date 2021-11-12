#include "app.h"
#include "mainView.h"
#include "view.h"
#include <chrono>

App::App(std::string title, Point<int> windowSize)
  : title(title), windowSize(windowSize),
    drawManager(nullptr), controller(nullptr),
    isAppRunning(false) { }

App::~App() {}

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
