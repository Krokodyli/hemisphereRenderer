#include "view.h"

View::View() : windowSize(0, 0) { }

View::~View() { }

void View::setup(App *_app, Point<int> _windowSize) {
  app = _app;
  windowSize = _windowSize;
}
