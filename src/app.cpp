#include "app.h"
#include "drawManager.h"
#include "view.h"
#include "mainView.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

const int App::framerateLimit = 60;

App::App(std::string _title, sf::Vector2i _windowSize, std::string _execPath)
  : title(_title), windowSize(_windowSize), execPath(_execPath),
    window(nullptr), drawManager(nullptr), isAppRunning(false) { }

App::~App() {
  while(!views.empty()) {
    View *view = views.top();
    views.pop();
    delete view;
  }
}

void App::pushView(View *newView) {
  newView->setup(this, windowSize);
  views.push(newView);
  executeView(views.top());
}

void App::execute() {
  setup();
  window->setFramerateLimit(framerateLimit);
  pushView(new MainView());
}

void App::setup() {
  window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y, 32),
                                title,
                                sf::Style::Titlebar | sf::Style::Close);

  drawManager = new DrawManager(window, execPath);

  isAppRunning = true;
}

void App::handleEvents() {
  sf::Event event;
  while(window->pollEvent(event))
    if(event.type == sf::Event::Closed)
      isAppRunning = false;
}

void App::executeView(View *view) {
  if(views.empty())
    return;
  View *currView = views.top();
  currView->setup(this, windowSize);
  while(isAppRunning && currView->isRunning()) {
    handleEvents();
    currView->update();
    currView->draw(drawManager);
    window->display();
  }
}
