#pragma once

#include <string>
#include "point.h"
#include "color.h"
#include "bitmap.h"

class DrawManager {
 protected:
  Point<int> offset;

 public:
  DrawManager();
  virtual ~DrawManager();

  Point<int> getOffset();
  void setOffset(Point<int> newOffset);

  virtual void drawRectangle(Point<float> pos, Point<float> size,
                             Color color) = 0;
  virtual void drawLine(Point<float> v1, Point<float> v2,
                        Color color) = 0;
  virtual void drawText(Point<float> pos, std::string text, int fontSize,
                        Color color) = 0;
  virtual void drawBitmap(Point<float> pos, Bitmap *bitmap) = 0;
};
