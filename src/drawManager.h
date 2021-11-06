#pragma once

#include "resourceManager.h"
#include "point.h"
#include "color.h"

class DrawManager {
 protected:
  Point<float> offset;

 public:
  DrawManager();
  virtual ~DrawManager();

  Point<float> getOffset();
  void setOffset(Point<float> newOffset);

  virtual void drawRectangle(Point<float> position, Point<float> size,
                             Color color) = 0;
  virtual void drawLine(Point<float> v1, Point<float> v2,
                        Color color) = 0;
};
