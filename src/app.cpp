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

App::App(std::string _title, sf::Vector2i _size, std::string _execPath)
  : title(_title), size(_size), execPath(_execPath),
    window(nullptr), drawManager(nullptr) { }

App::~App() {
  while(!views.empty())
    popView();
}

void App::pushView(View *newView) {
  newView->setup(this, size);
  views.push(newView);
}

void App::popView() {
  if(!views.empty())
    views.pop();
}

void App::execute() {
  setup();
  isRunning = true;
  window->setFramerateLimit(framerateLimit);
  while(isRunning) {
    handleEvents();
    update();
    draw();
  }
}

void App::setup() {
  window = new sf::RenderWindow(sf::VideoMode(size.x, size.y, 32), title,
                                sf::Style::Titlebar | sf::Style::Close);
  drawManager = new DrawManager(window, execPath);
  pushView(new MainView());
}

void App::draw() {
  if(!views.empty())
    views.top()->draw(drawManager);
  window->display();
}

void App::update() {
  if (!views.empty())
    views.top()->update();
}

void App::handleEvents() {
  sf::Event event;
  while(window->pollEvent(event))
    if(event.type == sf::Event::Closed)
      isRunning = false;
}
