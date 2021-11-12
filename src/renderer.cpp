#include "renderer.h"
#include "color.h"

Renderer::Renderer::Renderer(Point<int> canvasPosition, Point<int> canvasSize,
                             Bitmap *canvas)
  : canvasPosition(canvasPosition), canvasSize(canvasSize), canvas(canvas) {
  canvas->fillWithColor(canvasSize, Color(0, 0, 0));
}

Renderer::~Renderer() {}

void Renderer::drawOnBitmap(RenderConfig *renderConfig) {
  fillTriangles(renderConfig);
}

void Renderer::display(RenderConfig *renderConfig, DrawManager *drawManager) {
  auto oldOffset = drawManager->getOffset();
  drawManager->setOffset(canvasPosition);

  drawManager->drawBitmap(Point<float>(0, 0), canvas);
  canvas->fillWithColor(Color(0, 0, 0));

  if(renderConfig->getRenderMeshModeStatus())
    drawMesh(renderConfig, drawManager);

  drawManager->setOffset(oldOffset);
}

void Renderer::drawMesh(RenderConfig *renderConfig, DrawManager *drawManager) {
  auto edges = renderConfig->getMesh()->getEdges();
  for(const auto &edge : edges) {
    Point<float> v1 = { edge.a->x, edge.a->y };
    Point<float> v2 = { edge.b->x, edge.b->y};
    drawManager->drawLine(v1, v2, Color(255, 255, 255));
  }
}

void Renderer::fillTriangles(RenderConfig *renderConfig) {
  auto triangles = renderConfig->getMesh()->getTriangles();
  for(unsigned int i  = 0; i < triangles.size(); i += RENDERTHREADCOUNT) {
    int e = std::min((unsigned int)triangles.size(), i + RENDERTHREADCOUNT) - 1;
    for(int j = i; j <= e; j++) {
      threads[j - i] = std::thread(&Renderer::fillTriangle, this,
                                   renderConfig, triangles[j]);
    }
    for (int j = i; j <= e; j++)
      threads[j - i].join();
  }
}

void Renderer::fillTriangle(RenderConfig *renderConfig,
                                MeshTriangle triangle) {
  vector<Point3D<float>*> vertices;
  vertices.push_back(triangle.a);
  vertices.push_back(triangle.b);
  vertices.push_back(triangle.c);
  fillPolygon(renderConfig, vertices);
}

void Renderer::fillPolygon(RenderConfig *renderConfig,
                               vector<Point3D<float>*> &vertices) {
  int ymin, ymax;
  findBoundaries(vertices, &ymin, &ymax);
  AETVector aet;
  vector<int> scanlinePoints;
  float radius = renderConfig->getMesh()->getRadius();
  for(int y = ymin; y <= ymax; y++) {
    updateAET(y, aet, vertices);
    calculateScanline(aet, y, scanlinePoints);
    drawScanline(renderConfig, scanlinePoints, y, radius);
  }
}

void Renderer::findBoundaries(vector<Point3D<float> *> &vertices,
                                  int *ymin, int *ymax) {
  *ymin = vertices[0]->y;
  *ymax = vertices[0]->y;
  for(auto vertex : vertices) {
    *ymin = std::min((int)vertex->y, *ymin);
    *ymax = std::max((int)vertex->y, *ymax);
  }
}

void Renderer::updateAET(int y, AETVector &aet,
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

void Renderer::calculateScanline(AETVector &aet, float y,
                                     std::vector<int> &scanlinePoints) {
  scanlinePoints.clear();

  for(auto edge : aet) {
    auto v1 = edge.first;
    auto v2 = edge.second;
    int dy = std::abs((int)v1->y - (int)v2->y);
    if(dy >= 1) {
      auto x = (y-v1->y) / (v2->y - v1->y) * (v2->x - v1->x) + v1->x;
      scanlinePoints.push_back(x);
    }
  }

  std::sort(scanlinePoints.begin(), scanlinePoints.end());
}

void Renderer::drawScanline(RenderConfig *renderConfig,
                                vector<int> &scanlinePoints, int y, float r) {
  auto mesh = renderConfig->getMesh();
  for (int i = 0; i < (int)scanlinePoints.size() - 1; i += 2) {
    int x1 = scanlinePoints[i];
    int x2 = scanlinePoints[i+1];
    for(int x = x1; x <= x2; x++) {
      float z = mesh->calculateZ(x, y);
      auto point = Point3D<float>(x, y, z);
      auto color = ColorCalculator::calculate(renderConfig, point);
      canvas->setPixelColor(x, y, color);
    }
  }
}

void Renderer::deleteEdgeFromAET(AETVector &aet, Point3D<float> *v1,
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
