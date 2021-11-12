#include "sfmlApp.h"
#include "sfmlDrawManager.h"
#include "sfmlController.h"
#include "view.h"
#include "mainView.h"
#include "appToolbar.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

const std::string SFMLApp::appTitle = "Triangular mesh hole filling";

SFMLApp::SFMLApp(std::string execPath)
  : App(appTitle, Point<int>(windowWidth, windowHeight)),
    execPath(execPath) { }

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

  SFMLResourceManager *resManager = new SFMLResourceManager(execPath);
  resManager->loadResources(Point<int>(3.15f * meshRadius, 3.15f * meshRadius));

  drawManager = new SFMLDrawManager(window, resManager);
  controller = new SFMLController(window);

  isAppRunning = true;

  Toolbar *toolbar = new AppToolbar(Point<int>(0, 0), Point<int>(toolbarWidth,
                                                                 windowSize.y));

  Renderer *renderer = new Renderer(Point<int>(toolbarWidth, 0),
                                    Point(windowWidth - toolbarWidth,
                                          windowHeight),
                                    new SFMLBitmap(Point<int>(1, 1),
                                                   Color(0, 0, 0)));

  views.push(new MainView(renderer, toolbar, resManager,
                          meshRadius, toolbarWidth));
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

  startClock();
  while (isAppRunning && currView->isRunning()) {
    float dt = getDeltaTime();
    startClock();

    handleEvents();
    controller->update();
    currView->update(controller, dt);
    currView->draw(drawManager);
    window->display();
  }
}
