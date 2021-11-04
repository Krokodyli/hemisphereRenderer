#pragma once

#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <SFML/Window.hpp>

using sf::Vector2f;
using sf::Window;

class Controller {
private:
  Window *window;
  Vector2f offset;

  bool _isLeftPressed, _wasLeftPressed;
  bool _isRightPressed, _wasRightPressed;
  Vector2f mousePos, oldMousePos;

  int prevLeftClickTime, leftClickTime;

  int getMilisecondsFromEpoch();

public:
  Controller(Window *_window);
  virtual ~Controller();

  virtual void update();

  virtual bool isLeftPressed();
  virtual bool isRightPressed();
  virtual bool wasLeftPressed();
  virtual bool wasRightPressed();
  virtual bool isLeftClicked();
  virtual bool isRightClicked();

  virtual bool wasLeftClickDouble(int gapInMiliseconds);

  virtual Vector2f getMousePos();
  virtual Vector2f getPrevMousePos();

  virtual Vector2f getOffset();
  virtual void setOffset(Vector2f _offset);
};
