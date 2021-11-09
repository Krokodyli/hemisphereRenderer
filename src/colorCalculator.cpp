#include "colorCalculator.h"
#include "mesh.h"

Color ColorCalculator::calculate(RenderConfig *renderConfig, Point3D<float> p) {
  float kd = renderConfig->getKD();
  float ks = 0.3;
  auto I0 = colorToColorVector(Color(255, 255, 255));
  auto IL = colorToColorVector(renderConfig->getLightColor());
  auto L = calculateVersorTo(p, renderConfig->getLightPosition());
  auto N = calculateVersorTo(renderConfig->getMesh()->getCenter(), p);
  auto cosNL = calculateCosineBetweenVectors(L, N);

  auto V = Point3D<float>(0, 0, 1);

  auto R = N * 2.0 * L.dot(N) - L;

  auto cosRV = calculateCosineBetweenVectors(V, R);
  cosRV = cosRV * cosRV;
  cosRV = cosRV * cosRV;
  cosRV = cosRV * cosRV;
  cosRV = cosRV * cosRV;
  cosRV = cosRV * cosRV;

  auto I = fixColorVector(IL * kd * I0 * cosNL) +
    fixColorVector(IL * ks * I0 * cosRV);
  return colorVectorToColor(fixColorVector(I));
}

Point3D<float> ColorCalculator::calculateVersorTo(Point3D<float> from,
                                                  Point3D<float> to) {
  auto v = (to - from);
  auto len = v.dis(Point3D<float>(0, 0, 0));
  return v / len;
}

Point3D<float> ColorCalculator::colorToColorVector(Color col) {
  return Point3D<float>((float)col.getR()/255, (float)col.getG()/255,
                        (float)col.getB()/255);
}

Color ColorCalculator::colorVectorToColor(Point3D<float> col) {
  return Color(col.x*255, col.y*255, col.z*255);
}

Point3D<float> ColorCalculator::fixColorVector(Point3D<float> v) {
  if(v.x < 0)
    v.x = 0;
  else if(v.x > 1)
    v.x = 1;

  if (v.y < 0)
    v.y = 0;
  else if (v.y > 1)
    v.y = 1;

  if (v.z < 0)
    v.z = 0;
  else if (v.z > 1)
    v.z = 1;

  return v;
}

float ColorCalculator::calculateCosineBetweenVectors(Point3D<float> v1,
                                                     Point3D<float> v2) {
  auto l1 = v1.dis(Point3D<float>(0, 0, 0));
  auto l2 = v2.dis(Point3D<float>(0, 0, 0));
  return v1.dot(v2) / l1 / l2;
}
