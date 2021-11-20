#pragma once

#include "point.h"

class Controller {
public:
  virtual ~Controller();

  virtual void update() = 0;

  virtual bool isLeftPressed() = 0;
  virtual bool isRightPressed() = 0;
  virtual bool wasLeftPressed() = 0;
  virtual bool wasRightPressed() = 0;
  virtual bool isLeftClicked() = 0;
  virtual bool isRightClicked() = 0;

  virtual bool wasLeftClickDouble(int doubleClickThreshold) = 0;

  virtual Point<float> getMousePos() = 0;
  virtual Point<float> getPrevMousePos() = 0;

  virtual Point<int> getOffset() = 0;
  virtual void setOffset(Point<int> _offset) = 0;
};
