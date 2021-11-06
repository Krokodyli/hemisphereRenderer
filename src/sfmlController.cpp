#include "sfmlController.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

SFMLController::SFMLController(sf::RenderWindow *window)
  : window(window), offset(0, 0), mousePos(0, 0), oldMousePos(0, 0) {
  prevLeftClickTime = -1000000;
  leftClickTime = 0;
}

SFMLController::~SFMLController() { }

void SFMLController::update() {
  _wasLeftPressed = _isLeftPressed;
  _wasRightPressed = _isRightPressed;
  oldMousePos = mousePos;

  _isLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
  if(isLeftClicked()) {
    prevLeftClickTime = leftClickTime;
    leftClickTime = getMilisecondsFromEpoch();
  }

  _isRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);

  auto sfmlMousePos = sf::Mouse::getPosition(*window);
  mousePos.x = sfmlMousePos.x;
  mousePos.y = sfmlMousePos.y;
}

bool SFMLController::isLeftPressed() { return _isLeftPressed; }
bool SFMLController::isRightPressed() { return _isRightPressed; }
bool SFMLController::wasLeftPressed() { return _wasLeftPressed; }
bool SFMLController::wasRightPressed() { return _wasRightPressed; }

bool SFMLController::isLeftClicked() {
  return _isLeftPressed && !_wasLeftPressed;
}

bool SFMLController::isRightClicked() {
  return _isRightPressed && !_wasRightPressed;
}

bool SFMLController::wasLeftClickDouble(int gapInMiliseconds) {
  return leftClickTime - prevLeftClickTime <= gapInMiliseconds;
}

Point<float> SFMLController::getMousePos() { return mousePos - offset; }

Point<float> SFMLController::getPrevMousePos() { return oldMousePos - offset; }

Point<float> SFMLController::getOffset() {
  return offset;
}

void SFMLController::setOffset(Point<float> _offset) {
  offset = _offset;
}

int SFMLController::getMilisecondsFromEpoch() {
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}
