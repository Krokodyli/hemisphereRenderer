#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "drawManager.h"
#include "toolbar.h"

class App {
 private:
  std::string title;
  sf::Vector2i size;

  sf::RenderWindow *window;
  DrawManager *drawManager;

  Toolbar *toolbar;


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
