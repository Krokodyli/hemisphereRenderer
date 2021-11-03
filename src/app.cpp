#include "app.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

App::App(std::string _title, sf::Vector2i _size)
  : title(_title), size(_size), window(nullptr) { }

App::~App() {
  delete window;
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
}

void App::draw() {
  window->clear(sf::Color::Black);
  sf::RectangleShape shape(sf::Vector2f(100, 200));
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(sf::Vector2f(100, 100));
  window->draw(shape);
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
