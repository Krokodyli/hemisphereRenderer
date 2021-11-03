#include "toolbar.h"

Toolbar::Toolbar(Vector2f _position, Vector2f _size,
                 sf::Color _backgroundColor)
  : position(_position), size(_size), backgroundColor(_backgroundColor) { }

void Toolbar::draw(DrawManager *drawManager) {
  drawManager->drawRectangle(position, size, backgroundColor);
}
