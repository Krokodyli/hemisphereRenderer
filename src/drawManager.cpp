#include "drawManager.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
