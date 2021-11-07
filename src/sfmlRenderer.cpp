#include "sfmlRenderer.h"
#include "mesh.h"

SFMLRenderer::~SFMLRenderer() {}

void SFMLRenderer::drawOnBitmap(RenderConfig *renderConfig) {
}

void SFMLRenderer::displayBitmap(RenderConfig *renderConfig,
                                 DrawManager *drawManager) {
  drawMesh(renderConfig, drawManager);
}

void SFMLRenderer::drawMesh(RenderConfig *renderConfig,
                            DrawManager *drawManager) {
  auto edges = renderConfig->getMesh()->getEdges();
  for(auto edge : edges) {
    auto v1 = Point<float>(edge.a->x, edge.a->y);
    auto v2 = Point<float>(edge.b->x, edge.b->y);
    drawManager->drawLine(v1, v2, Color(255, 255, 255));
  }
}
