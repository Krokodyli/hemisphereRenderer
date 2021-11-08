#include "sfmlDrawManager.h"
#include "resourceManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

SFMLDrawManager::SFMLDrawManager(sf::RenderWindow *window,
                                 std::string execPath)
  : window(window), resourceManager(execPath) {
  resourceManager.loadResources();
}

SFMLDrawManager::~SFMLDrawManager() { }

void SFMLDrawManager::drawRectangle(Point<float> pos, Point<float> size,
                                    Color color) {
  sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
  auto offsetPos = Point<float>(pos.x + offset.x, pos.y + offset.y);
  rect.setPosition(sf::Vector2f(offsetPos.x, offsetPos.y));
  rect.setFillColor(colorToSFMLColor(color));
  window->draw(rect);
}

void SFMLDrawManager::drawLine(Point<float> v1, Point<float> v2, Color color) {
  sf::Vertex line[] = {
    sf::Vertex(sf::Vector2f(v1.x + offset.x, v1.y + offset.y),
               colorToSFMLColor(color)),
    sf::Vertex(sf::Vector2f(v2.x + offset.x, v2.y + offset.y),
               colorToSFMLColor(color))
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

void SFMLDrawManager::drawSprite(sf::Sprite *sprite) {
  auto oldPos = sprite->getPosition();
  sprite->setPosition(sf::Vector2f(oldPos.x + offset.x, oldPos.y + offset.y));
  window->draw(*sprite);
  sprite->setPosition(oldPos);
}

sf::Color SFMLDrawManager::colorToSFMLColor(Color c) {
  return sf::Color(c.getR(), c.getG(), c.getB(), c.getA());
}
