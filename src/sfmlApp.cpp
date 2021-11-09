#include "sfmlApp.h"
#include "sfmlDrawManager.h"
#include "sfmlController.h"
#include "view.h"
#include "mainView.h"
#include "sfmlRenderer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

const int SFMLApp::framerateLimit = 30;

SFMLApp::SFMLApp(std::string title, Point<int> windowSize, std::string execPath)
  : App(title, windowSize), execPath(execPath) { }

SFMLApp::~SFMLApp() {
  while(!views.empty()) {
    View *view = views.top();
    views.pop();
    delete view;
  }
  delete drawManager;
  delete controller;
}

void SFMLApp::setup() {
  window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y, 32),
                                title,
                                sf::Style::Titlebar | sf::Style::Close);
  window->setFramerateLimit(framerateLimit);

  drawManager = new SFMLDrawManager(window, execPath);
  controller = new SFMLController(window);

  isAppRunning = true;

  views.push(new MainView(new SFMLRenderer(Point<int>(windowSize.x/6.0, 0),
                                           Point<int>(windowSize.x*5.0/6.0,
                                                      windowSize.y))));
}

void SFMLApp::handleEvents() {
  sf::Event event;
  while(window->pollEvent(event))
    if(event.type == sf::Event::Closed)
      isAppRunning = false;
}

void SFMLApp::executeView(View *view) {
  if (views.empty())
    return;

  View *currView = views.top();
  currView->setup(this, windowSize);

  while (isAppRunning && currView->isRunning()) {
    handleEvents();
    controller->update();
    currView->update(controller);
    currView->draw(drawManager);
    window->display();
  }
}
