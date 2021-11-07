#include "sfmlRenderer.h"
#include "Point3D.h"
#include <algorithm>

SFMLRenderer::SFMLRenderer(Point<int> canvasPosition, Point<int> canvasSize)
  : canvasPosition(canvasPosition), canvasSize(canvasSize) {
  image.create(canvasSize.x, canvasSize.y, sf::Color::Black);
}

SFMLRenderer::~SFMLRenderer() {}

void SFMLRenderer::drawOnBitmap(RenderConfig *renderConfig) {
  fillTriangles(renderConfig);
}

void SFMLRenderer::displayBitmap(RenderConfig *renderConfig,
                                 DrawManager *drawManager) {
  auto oldOffset = drawManager->getOffset();
  drawManager->setOffset(canvasPosition);

  texture.loadFromImage(image);
  sprite.setTexture(texture);
  drawManager->drawSprite(&sprite);
  image.create(canvasSize.x, canvasSize.y, sf::Color::Black);
  drawMesh(renderConfig, drawManager);

  drawManager->setOffset(oldOffset);
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

void SFMLRenderer::fillTriangles(RenderConfig *renderConfig) {
  auto triangles = renderConfig->getMesh()->getTriangles();
  for(auto triangle : triangles)
    fillTriangle(renderConfig, triangle);
  fillTriangle(renderConfig, triangles[triangles.size()/2]);
}

void SFMLRenderer::fillTriangle(RenderConfig *renderConfig,
                                MeshTriangle triangle) {
  vector<Point3D<float>*> vertices;
  vertices.push_back(triangle.a);
  vertices.push_back(triangle.b);
  vertices.push_back(triangle.c);
  fillPolygon(renderConfig, vertices);
}

void SFMLRenderer::fillPolygon(RenderConfig *renderConfig,
                               vector<Point3D<float>*> &vertices) {
  int ymin, ymax;
  findBoundaries(vertices, &ymin, &ymax);
  AETVector aet;
  vector<int> scanlinePoints;
  float radius = renderConfig->getMesh()->getRadius();
  for(int y = ymin; y <= ymax; y++) {
    updateAET(y, aet, vertices);
    calculateScanline(aet, y, scanlinePoints);
    drawScanline(scanlinePoints, y, radius);
  }
}

void SFMLRenderer::findBoundaries(vector<Point3D<float> *> &vertices,
                                  int *ymin, int *ymax) {
  *ymin = vertices[0]->y;
  *ymax = vertices[0]->y;
  for(auto vertex : vertices) {
    *ymin = std::min((int)vertex->y, *ymin);
    *ymax = std::max((int)vertex->y, *ymax);
  }
}

void SFMLRenderer::updateAET(int y, AETVector &aet,
                             vector<Point3D<float>*> &vertices) {
  for (unsigned int i = 0; i < vertices.size(); i++) {
    if ((int)vertices[i]->y == y - 1) {
      int pv = (i + vertices.size() - 1) % vertices.size();
      int pn = (i + 1) % vertices.size();

      if(vertices[pv]->y >= vertices[i]->y)
        aet.push_back({vertices[pv], vertices[i]});
      else
        deleteEdgeFromAET(aet, vertices[pv], vertices[i]);

      if(vertices[pn]->y >= vertices[i]->y)
        aet.push_back({vertices[i], vertices[pn]});
      else
        deleteEdgeFromAET(aet, vertices[i], vertices[pn]);
    }
  }
}

void SFMLRenderer::calculateScanline(AETVector &aet, float y,
                                     std::vector<int> &points) {
  points.clear();

  for(auto edge : aet) {
    auto v1 = edge.first;
    auto v2 = edge.second;
    if(v1->y != v2->y) {
      auto x = (y-v1->y) / (v2->y - v1->y) * (v2->x - v1->x) + v1->x;
      points.push_back(x);
    }
  }

  std::sort(points.begin(), points.end());
}

void SFMLRenderer::drawScanline(vector<int> &scanlinePoints, int y,
                                float r) {
  for(int i = 0; i < (int)scanlinePoints.size() - 1; i+=2) {
    int x1 = scanlinePoints[i];
    int x2 = scanlinePoints[i+1];
    for(int x = x1; x <= x2; x++) {
      float z = std::sqrt(r * r - x * x - y * y);
      image.setPixel(x, y, getColorForPixel(Point3D<float>(x, y, z)));
    }
  }
}

void SFMLRenderer::deleteEdgeFromAET(AETVector &aet, Point3D<float> *v1,
                                     Point3D<float> *v2) {
  int deleted = 0;
  for(unsigned int i = 0; i < aet.size(); i++) {
    if((aet[i].first == v1 && aet[i].second == v2)
       || (aet[i].first == v2 && aet[i].second == v1))
      deleted++;
    aet[i] = aet[i+deleted];
  }
  aet.erase(aet.begin() + (aet.size() - deleted), aet.end());
}

sf::Color SFMLRenderer::getColorForPixel(Point3D<float> pixel) {
  return sf::Color(255 * pixel.x/canvasSize.x,
                   255 * pixel.y/canvasSize.y,
                   255 * pixel.x * pixel.y / canvasSize.x / canvasSize.y);
}
