#pragma once

#include "renderer.h"
#include <SFML/Graphics/Image.hpp>

class SFMLRenderer : public Renderer {
 private:
  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;

  void drawMesh(RenderConfig *renderConfig, DrawManager *drawManager);

 public:
  virtual ~SFMLRenderer();

  virtual void drawOnBitmap(RenderConfig *renderConfig);
  virtual void displayBitmap(RenderConfig *renderConfig,
                             DrawManager *drawManager);
};
