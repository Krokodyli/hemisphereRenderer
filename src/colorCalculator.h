#pragma once

#include "Point3D.h"
#include "color.h"
#include "renderConfig.h"

class ColorCalculator {
 private:
  static Point3D<float> calculateVersorTo(Point3D<float> from,
                                          Point3D<float> to);

  static Point3D<float> colorToColorVector(Color col);
  static Color colorVectorToColor(Point3D<float> col);
  static Point3D<float> fixColorVector(Point3D<float> v);
  static float calculateCosineBetweenVectors(Point3D<float> v1,
                                             Point3D<float> v2);
 public:
  static Color calculate(RenderConfig *renderConfig, Point3D<float> p);
};
