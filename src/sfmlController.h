#pragma once

#include "controller.h"
#include <chrono>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SFMLController : public Controller {
private:
  sf::RenderWindow *window;
  Point<int> offset;

  bool _isLeftPressed, _wasLeftPressed;
  bool _isRightPressed, _wasRightPressed;
  Point<int> mousePos, oldMousePos;

  int prevLeftClickTime, leftClickTime;

  int getMilisecondsFromEpoch();

public:
  SFMLController(sf::RenderWindow *window);
  virtual ~SFMLController();

  virtual void update();

  virtual bool isLeftPressed();
  virtual bool isRightPressed();
  virtual bool wasLeftPressed();
  virtual bool wasRightPressed();
  virtual bool isLeftClicked();
  virtual bool isRightClicked();

  virtual bool wasLeftClickDouble(int gapInMiliseconds);

  virtual Point<float> getMousePos();
  virtual Point<float> getPrevMousePos();

  virtual Point<int> getOffset();
  virtual void setOffset(Point<int> _offset);
};
