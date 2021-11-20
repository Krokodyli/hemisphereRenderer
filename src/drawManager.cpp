#include "drawManager.h"

DrawManager::DrawManager() : offset(0, 0) { }

DrawManager::~DrawManager() { }

Point<int> DrawManager::getOffset() {
  return offset;
}

void DrawManager::setOffset(Point<int> newOffset) {
  offset = newOffset;
}
