#include "sfmlApp.h"
#include "sfmlBitmap.h"
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

SFMLApp::SFMLApp(std::string execPath)
  : execPath(execPath) { }

SFMLApp::~SFMLApp() { }

void SFMLApp::setup() {
  window = new sf::RenderWindow(sf::VideoMode(appConsts.windowSize.x,
                                              appConsts.windowSize.y, 32),
                                appConsts.appTitle,
                                sf::Style::Titlebar | sf::Style::Close);
  window->setFramerateLimit(appConsts.framerateLimit);

  SFMLResourceManager *resManager = new SFMLResourceManager(execPath);
  resManager->loadResources(appConsts.textureExpectedSize);
  resourceManager = resManager;

  drawManager = new SFMLDrawManager(window, resManager);
  controller = new SFMLController(window);

  Toolbar *toolbar = new AppToolbar(&appConsts);

  auto bitmapTemplate = new SFMLBitmap(Point<int>(1, 1), Color(0, 0, 0));
  Renderer *renderer = new Renderer(bitmapTemplate, &appConsts);

  isAppRunning = true;

  views.push(new MainView(renderer, toolbar, resManager, &appConsts));
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
  currView->setup();

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
