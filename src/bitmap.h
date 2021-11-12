#pragma once

#include "color.h"
#include "point.h"

class SFMLDrawManager;

class Bitmap {
 public:
  virtual int getWidth() = 0;
  virtual int getHeight() = 0;

  virtual Color getPixelColor(int x, int y) = 0;
  virtual void setPixelColor(int x, int y, Color color) = 0;

  virtual void fillWithColor(Color color) = 0;
  virtual void fillWithColor(Point<int> size, Color color) = 0;

  // necessarily coupled function
  // it is still pretty easy to change framework
  virtual void draw(Point<float> pos, SFMLDrawManager *drawManager) = 0;
};
