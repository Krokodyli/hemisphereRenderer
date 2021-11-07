#pragma once

#include "mesh.h"
#include "renderer.h"
#include <SFML/Graphics/Image.hpp>
#include <algorithm>

typedef std::vector<pair<Point3D<float>*, Point3D<float>*>> AETVector;

class SFMLRenderer : public Renderer {
 private:
  Point<int> canvasPosition;
  Point<int> canvasSize;
  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;

  void drawMesh(RenderConfig *renderConfig, DrawManager *drawManager);
  void fillTriangles(RenderConfig *renderConfig);
  void fillTriangle(RenderConfig *renderConfig, MeshTriangle triangle);

  void fillPolygon(RenderConfig *renderConfig,
                   std::vector<Point3D<float> *> &vertices);
  void findBoundaries(std::vector<Point3D<float> *> &vertices, int *ymin,
                      int *ymax);
  void updateAET(int y, AETVector &aet, vector<Point3D<float> *> &vertices);
  void calculateScanline(AETVector &aet, float y, vector<int> &points);
  void drawScanline(vector<int> &scanlinePoints, int y, float r);
  void deleteEdgeFromAET(AETVector &aet, Point3D<float> *v1,
                         Point3D<float> *v2);

  sf::Color getColorForPixel(Point3D<float> pixel);

 public:
  SFMLRenderer(Point<int> canvasPosition, Point<int> canvasSize);
  virtual ~SFMLRenderer();

  virtual void drawOnBitmap(RenderConfig *renderConfig);
  virtual void displayBitmap(RenderConfig *renderConfig,
                             DrawManager *drawManager);
};
