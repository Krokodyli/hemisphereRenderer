#include "drawManager.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

DrawManager::DrawManager(sf::RenderWindow *_window, std::string _execPath)
  : window(_window), resourceManager(_execPath) { }

Vector2f DrawManager::getOffset() {
  return offset;
}

void DrawManager::setOffset(Vector2f newOffset) {
  offset = newOffset;
}

void DrawManager::drawRectangle(Vector2f position, Vector2f size,
                                Color fillColor) {
  sf::RectangleShape rect(size);
  rect.setPosition(position + offset);
  rect.setFillColor(fillColor);
  window->draw(rect);
}

void DrawManager::drawLine(Vector2f v1, Vector2f v2, Color color) {
  sf::Vertex line[] =
  {
    sf::Vertex(v1, color),
    sf::Vertex(v2, color)
  };
  window->draw(line, 2, sf::Lines);
}
