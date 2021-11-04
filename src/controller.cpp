#include "controller.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

Controller::Controller(sf::Window *_window) : window(_window) {
  prevLeftClickTime = -1000000;
  leftClickTime = 0;
}

Controller::~Controller() { }

void Controller::update() {
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

bool Controller::isLeftPressed() { return _isLeftPressed; }
bool Controller::isRightPressed() { return _isRightPressed; }
bool Controller::wasLeftPressed() { return _wasLeftPressed; }
bool Controller::wasRightPressed() { return _wasRightPressed; }

bool Controller::isLeftClicked() {
  return _isLeftPressed && !_wasLeftPressed;
}

bool Controller::isRightClicked() {
  return _isRightPressed && !_wasRightPressed;
}

bool Controller::wasLeftClickDouble(int gapInMiliseconds) {
  return leftClickTime - prevLeftClickTime <= gapInMiliseconds;
}

Vector2f Controller::getMousePos() { return mousePos - offset; }

Vector2f Controller::getPrevMousePos() { return oldMousePos - offset; }

Vector2f Controller::getOffset() {
  return offset;
}

void Controller::setOffset(Vector2f _offset) {
  offset = _offset;
}

int Controller::getMilisecondsFromEpoch() {
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}
