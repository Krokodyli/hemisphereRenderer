#pragma once

#include <SFML/Graphics/Image.hpp>
#include "renderer.h"



class SFMLRenderer : public Renderer {
 private:
  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;

  virtual void putPixel(int x, int y, Color c);
  virtual void displayBitmap(RenderConfig *renderConfig,
                             DrawManager *drawManager);
public:
  SFMLRenderer(Point<int> canvasPosition, Point<int> canvasSize);
  virtual ~SFMLRenderer();

};
