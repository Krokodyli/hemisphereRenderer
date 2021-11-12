#pragma once

#include "drawManager.h"
#include "mesh.h"
#include "renderConfig.h"
#include <algorithm>
#include "colorCalculator.h"
#include <thread>

#define RENDERTHREADCOUNT 8

typedef std::vector<pair<Point3D<float> *, Point3D<float> *>> AETVector;

class Renderer {
 protected:
  Point<int> canvasPosition;
  Point<int> canvasSize;

  Bitmap *canvas;

  std::thread threads[RENDERTHREADCOUNT];

  void fillTriangles(RenderConfig *renderConfig);
  void fillTriangle(RenderConfig *renderConfig, MeshTriangle triangle);

  void fillPolygon(RenderConfig *renderConfig,
                   std::vector<Point3D<float> *> &vertices);
  void findBoundaries(std::vector<Point3D<float> *> &vertices, int *ymin,
                      int *ymax);
  void updateAET(int y, AETVector &aet, vector<Point3D<float> *> &vertices);
  void calculateScanline(AETVector &aet, float y, vector<int> &scanlinePoints);
  void drawScanline(RenderConfig *renderConfig, vector<int> &scanlinePoints,
                    int y, float r);
  void deleteEdgeFromAET(AETVector &aet, Point3D<float> *v1,
                         Point3D<float> *v2);

public:
  Renderer(Point<int> canvasPosition, Point<int> canvasSize,
           Bitmap *bitmap);
  virtual ~Renderer();
  virtual void drawOnBitmap(RenderConfig *renderConfig);
  virtual void display(RenderConfig *renderConfig,
                       DrawManager *drawManager);
  virtual void drawMesh(RenderConfig *renderConfig, DrawManager *drawManager);
};
