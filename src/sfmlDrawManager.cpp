#include "sfmlDrawManager.h"
#include "resourceManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

SFMLDrawManager::SFMLDrawManager(sf::RenderWindow *window,
                                 std::string execPath)
  : window(window), resourceManager(execPath) {
  resourceManager.loadResources();
}

SFMLDrawManager::~SFMLDrawManager() { }

void SFMLDrawManager::drawRectangle(Point<float> position, Point<float> size,
                                    Color color) {
  sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
  Point<float> pos = position + offset;
  rect.setPosition(sf::Vector2f(pos.x, pos.y));
  rect.setFillColor(colorToSFMLColor(color));
  window->draw(rect);
}

void SFMLDrawManager::drawLine(Point<float> v1, Point<float> v2, Color color) {
  sf::Vertex line[] = {
    sf::Vertex(sf::Vector2f(v1.x, v1.y), colorToSFMLColor(color)),
    sf::Vertex(sf::Vector2f(v2.x, v2.y), colorToSFMLColor(color))
  };
  window->draw(line, 2, sf::Lines);
}

void SFMLDrawManager::drawText(Point<float> pos, std::string text, int fontSize,
                               Color color) {
  auto font = resourceManager.getFont();
  sf::Text drawableText(text, font, fontSize);
  drawableText.setPosition(sf::Vector2f(pos.x-offset.x, pos.y-offset.y));
  window->draw(drawableText);
}

sf::Color SFMLDrawManager::colorToSFMLColor(Color c) {
  return sf::Color(c.getR(), c.getG(), c.getB(), c.getA());
}
