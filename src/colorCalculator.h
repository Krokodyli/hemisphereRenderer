#pragma once

#include "Point3D.h"
#include "color.h"
#include "mesh.h"
#include "renderConfig.h"
#include <math.h>

class ColorCalculator {
 private:
  MeshTriangle currTriangle;
  Point3D<float> vertexAColor, vertexBColor, vertexCColor;

  Color calculateExactColor(RenderConfig *renderConfig, Point3D<float> p);
  Color calculateApproxColor(RenderConfig *renderConfig, Point3D<float> p);

  Point3D<float> calculateVersorTo(Point3D<float> from,
                                   Point3D<float> to);

  Point3D<float> colorToColorVector(Color col);
  Point3D<float> normalMapColorToNormalVector(Color col);
  Color colorVectorToColor(Point3D<float> col);
  Point3D<float> fixColorVector(Point3D<float> v);

  float calculateCosineBetweenVectors(Point3D<float> v1,
                                      Point3D<float> v2);
  Point<float> calculateTexturePos(Point3D<float> p, Mesh *mesh);

  Point3D<float> joinNormalVectors(Point3D<float> sphereNormalVect,
                                   Point3D<float> normalMapVect);

  float fastExp(float base, int power);
 public:
  ColorCalculator();

  void setCurrentTriangle(RenderConfig *renderConfig,
                          MeshTriangle currTriangle);

  Color calculate(RenderConfig *renderConfig, Point3D<float> p,
                  bool approxColoringMode);
};
