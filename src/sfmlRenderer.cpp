#include "sfmlRenderer.h"
#include "Point3D.h"
#include "renderConfig.h"
#include <algorithm>
#include "colorCalculator.h"

SFMLRenderer::SFMLRenderer(Point<int> canvasPosition, Point<int> canvasSize)
  : Renderer(canvasPosition, canvasSize) {
  image.create(canvasSize.x, canvasSize.y, sf::Color::Black);
}

SFMLRenderer::~SFMLRenderer() {}

void SFMLRenderer::displayBitmap(RenderConfig *renderConfig,
                                 DrawManager *drawManager) {
  texture.loadFromImage(image);
  sprite.setTexture(texture);
  drawManager->drawSprite(&sprite);
  image.create(canvasSize.x, canvasSize.y, sf::Color::Black);
}

void SFMLRenderer::putPixel(int x, int y, Color c) {
  image.setPixel(x, y, sf::Color(c.getR(), c.getG(), c.getB()));
}
