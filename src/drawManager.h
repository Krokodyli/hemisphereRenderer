#pragma once

#include "resourceManager.h"
#include "point.h"
#include "color.h"

class DrawManager {
 protected:
  Point<int> offset;

 public:
  DrawManager();
  virtual ~DrawManager();

  Point<int> getOffset();
  void setOffset(Point<int> newOffset);

  virtual void drawRectangle(Point<float> position, Point<float> size,
                             Color color) = 0;
  virtual void drawLine(Point<float> v1, Point<float> v2,
                        Color color) = 0;
  virtual void drawText(Point<float> pos, std::string text, int fontSize,
                        Color color) = 0;
  virtual void drawSprite(sf::Sprite *sprite) = 0;
};
