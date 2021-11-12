#include "sfmlBitmap.h"
#include "sfmlDrawManager.h"

SFMLBitmap::SFMLBitmap(Point<int> size, Color color) {
  fillWithColor(size, color);
}

SFMLBitmap::SFMLBitmap(sf::Image image) : image(image) { }

int SFMLBitmap::getWidth() {
  return image.getSize().x;
}

int SFMLBitmap::getHeight() {
  return image.getSize().y;
}

Color SFMLBitmap::getPixelColor(int x, int y) {
  auto color = image.getPixel(x, y);
  return Color(color.r, color.g, color.b);
}

void SFMLBitmap::setPixelColor(int x, int y, Color color) {
  auto sfColor = sf::Color(color.getR(), color.getG(), color.getB());
  image.setPixel(x, y, sfColor);
}

void SFMLBitmap::fillWithColor(Color color) {
  auto size = image.getSize();
  image.create(size.x, size.y, sf::Color(color.getR(), color.getG(),
                                         color.getB()));
}

void SFMLBitmap::fillWithColor(Point<int> size, Color color) {
  image.create(size.x, size.y,
               sf::Color(color.getR(), color.getG(), color.getB()));
}

void SFMLBitmap::draw(Point<float> pos, SFMLDrawManager *drawManager) {
  drawManager->drawSFMLImage(pos, &image);
}

const sf::Image *SFMLBitmap::getImage() {
  return &image;
}
