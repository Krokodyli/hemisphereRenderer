#pragma once

#include <SFML/Graphics/Image.hpp>
#include "bitmap.h"
#include "color.h"
#include "point.h"

class SFMLBitmap : public Bitmap {
 private:
  sf::Image image;

 public:
  SFMLBitmap(Point<int> size, Color color);
  SFMLBitmap(sf::Image image);

  virtual int getWidth();
  virtual int getHeight();

  virtual Color getPixelColor(int x, int y);
  virtual void setPixelColor(int x, int y, Color color);

  virtual void fillWithColor(Color color);
  virtual void fillWithColor(Point<int> size, Color color);

  virtual void draw(Point<float> pos, SFMLDrawManager *drawManager);

  const sf::Image *getImage();
};
