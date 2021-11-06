#include "drawManager.h"

DrawManager::DrawManager() : offset(0, 0) { }

DrawManager::~DrawManager() { }

Point<float> DrawManager::getOffset() {
  return offset;
}

void DrawManager::setOffset(Point<float> newOffset) {
  offset = newOffset;
}
