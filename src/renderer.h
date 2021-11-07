#pragma once

#include "drawManager.h"
#include "renderConfig.h"

class Renderer {
 public:
  virtual ~Renderer();
  virtual void drawOnBitmap(RenderConfig *renderConfig) = 0;
  virtual void displayBitmap(RenderConfig *renderConfig,
                             DrawManager *drawManager) = 0;
};
