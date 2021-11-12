#include "colorCalculator.h"
#include "mesh.h"

Color ColorCalculator::calculate(RenderConfig *renderConfig, Point3D<float> p) {
  float kd = renderConfig->getKD();
  float ks = renderConfig->getKS();
  float k = renderConfig->getK();
  int m = renderConfig->getM();

  auto texturePos =
      calculateTexturePos(p, renderConfig->getMesh());

  auto I0 = colorToColorVector(renderConfig->getTextureColor(texturePos));
  auto IL = colorToColorVector(renderConfig->getLightColor());
  auto L = calculateVersorTo(p, renderConfig->getLightPosition());

  auto normalColor = renderConfig->getNormalMapColor(texturePos);

  auto N = calculateVersorTo(renderConfig->getMesh()->getCenter(), p);
  if(normalColor.getR() > 0 || normalColor.getB() > 0 ||
     normalColor.getG() > 0)
    N = (N * k + normalMapColorToNormalVector(normalColor) * (1-k));

  auto cosNL = calculateCosineBetweenVectors(L, N);

  auto V = Point3D<float>(0, 0, 1);

  auto R = N * 2.0 * L.dot(N) - L;

  auto cosRV = calculateCosineBetweenVectors(V, R);
  cosRV = fastExp(cosRV, m);

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

Point3D<float> ColorCalculator::normalMapColorToNormalVector(Color col) {
  float x = ((float)col.getR()/255.0) * 2.0 - 1.0;
  float y = ((float)col.getG() / 255.0) * 2.0 - 1.0;
  float z = ((float)col.getB() / 255.0);
  return Point3D<float>(x, y, z);
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

Point<float> ColorCalculator::calculateTexturePos(Point3D<float> p,
                                                  Mesh *mesh) {
  float radius = mesh->getRadius();
  Point3D<float> center = mesh->getCenter();
  p.x -= center.x;
  p.y -= center.y;

  float alpha = acos(calculateCosineBetweenVectors(Point3D<float>(0, 0, radius),
                                                   p-Point3D<float>(0, 0, 0)));
  float dis = alpha * radius;

  float dis2 = sqrt(p.x * p.x + p.y * p.y);
  Point<float> p2 = Point<float>(p.x/dis2, p.y/dis2);

  auto vector = p2 * dis;

  return Point<float>(vector.x + 504, vector.y + 504);
}

float ColorCalculator::fastExp(float base, int power) {
  float res = 1;
  while(power > 0) {
    if(power % 2 == 0) {
      power /= 2;
      base *= base;
    }
    else {
      power--;
      res *= base;
      power /= 2;
      base *= base;
    }
  }
  return res;
}
