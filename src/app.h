#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class App {
 protected:
  std::string title;
  sf::Vector2i size;

  sf::RenderWindow *window;

  bool isRunning;

  void setup();
  void draw();
  void update();
  void handleEvents();
 public:
  App(std::string title, sf::Vector2i _size);
  ~App();

  void execute();
};
