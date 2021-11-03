#include "app.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

App::App(std::string _title, sf::Vector2i _size)
  : title(_title), size(_size), window(nullptr), drawManager(nullptr) { }

App::~App() {
  if(window)
    delete window;
  if(drawManager)
    delete drawManager;
  if(toolbar)
    delete toolbar;
}

void App::execute() {
  setup();
  isRunning = true;
  while(isRunning) {
    handleEvents();
    update();
    draw();
  }
}

void App::setup() {
  window = new sf::RenderWindow(sf::VideoMode(size.x, size.y, 32), title,
                                sf::Style::Titlebar | sf::Style::Close);
  drawManager = new DrawManager(window);
  toolbar = new Toolbar(sf::Vector2f(0, 0), sf::Vector2f(size.x/6.0f, size.y),
                        sf::Color::White);
}

void App::draw() {
  toolbar->draw(drawManager);
  window->display();
}

void App::update() {

}

void App::handleEvents() {
  sf::Event event;
  while(window->pollEvent(event))
    if(event.type == sf::Event::Closed)
      isRunning = false;
}
