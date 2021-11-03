#include "view.h"

View::~View() { }

void View::setup(App *_app, Vector2i _windowSize) {
  app = _app;
  windowSize = _windowSize;
}
