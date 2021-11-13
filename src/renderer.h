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
  AppConsts *appConsts;

  Bitmap *canvas;

  std::thread threads[RENDERTHREADCOUNT];
  ColorCalculator colorCalculators[RENDERTHREADCOUNT];

  void fillTriangles(RenderConfig *renderConfig);
  void fillTrianglesParallel(RenderConfig *renderConfig);
  void fillTrianglesSequential(RenderConfig *renderConfig);
  void fillTriangle(RenderConfig *renderConfig, ColorCalculator *colorCalc,
                    MeshTriangle triangle);

  void fillPolygon(RenderConfig *renderConfig, ColorCalculator *colorCalc,
                   std::vector<Point3D<float> *> &vertices);
  void findBoundaries(std::vector<Point3D<float> *> &vertices, int *ymin,
                      int *ymax);
  void updateAET(int y, AETVector &aet, vector<Point3D<float> *> &vertices);
  void calculateScanline(AETVector &aet, float y, vector<int> &scanlinePoints);
  void drawScanline(RenderConfig *renderConfig, ColorCalculator *colorCalc,
                    vector<int> &scanlinePoints, int y, float r);
  void deleteEdgeFromAET(AETVector &aet, Point3D<float> *v1,
                         Point3D<float> *v2);

public:
  Renderer(Bitmap *bitmap, AppConsts *appConsts);
  virtual ~Renderer();
  virtual void drawOnBitmap(RenderConfig *renderConfig);
  virtual void display(RenderConfig *renderConfig,
                       DrawManager *drawManager);
  virtual void drawMesh(RenderConfig *renderConfig, DrawManager *drawManager);
};
