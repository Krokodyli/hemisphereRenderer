#include "colorCalculator.h"
#include "mesh.h"

ColorCalculator::ColorCalculator()
  : currTriangle(nullptr, nullptr, nullptr),
    vertexAColor(0, 0, 0), vertexBColor(0, 0, 0), vertexCColor(0, 0, 0) { }

void ColorCalculator::setCurrentTriangle(RenderConfig *renderConfig,
                                         MeshTriangle currTriangle) {
  this->currTriangle = currTriangle;
  vertexAColor = colorToColorVector(calculateExactColor(renderConfig,
                                                        *currTriangle.a));
  vertexBColor = colorToColorVector(calculateExactColor(renderConfig,
                                                        *currTriangle.b));
  vertexCColor = colorToColorVector(calculateExactColor(renderConfig,
                                                        *currTriangle.c));
}

Color ColorCalculator::calculate(RenderConfig *renderConfig, Point3D<float> p,
                                 bool approxColoringMode) {
  if(!approxColoringMode)
    return calculateExactColor(renderConfig, p);
  else
    return calculateApproxColor(renderConfig, p);
}

Color ColorCalculator::calculateExactColor(RenderConfig *renderConfig,
                                           Point3D<float> p) {
  float kd = renderConfig->kd;
  float ks = renderConfig->ks;
  float k = renderConfig->k;
  int m = renderConfig->m;

  auto texturePos =
      calculateTexturePos(p, renderConfig->mesh);

  auto I0 = colorToColorVector(renderConfig->getTextureColor(texturePos));
  auto IL = colorToColorVector(renderConfig->lightColor);
  auto L = calculateVersorTo(p, renderConfig->lightPosition);

  auto normalColor = renderConfig->getNormalMapColor(texturePos);

  auto N = calculateVersorTo(renderConfig->mesh->getCenter(), p);
  if(normalColor.r > 0 || normalColor.b > 0 ||
     normalColor.g > 0) {
    auto normalMapVect = normalMapColorToNormalVector(normalColor);
    normalMapVect = joinNormalVectors(N, normalMapVect);
    N = (N * k + normalMapVect * (1-k));
  }

  auto cosNL = calculateCosineBetweenVectors(L, N);

  auto V = Point3D<float>(0, 0, 1);

  auto R = N * 2.0 * L.dot(N) - L;

  auto cosVR = calculateCosineBetweenVectors(V, R);
  cosVR = fastExp(cosVR, m);

  auto I = fixColorVector(IL * kd * I0 * cosNL) +
    fixColorVector(IL * ks * I0 * cosVR);

  return colorVectorToColor(fixColorVector(I));
}

Color ColorCalculator::calculateApproxColor(RenderConfig *renderConfig,
                                            Point3D<float> p) {
  float aDis = p.dis(*currTriangle.a);
  float bDis = p.dis(*currTriangle.b);
  float cDis = p.dis(*currTriangle.c);
  float disSum = aDis + bDis + cDis;
  auto color = ((vertexAColor * aDis) + (vertexBColor * bDis)
                + (vertexCColor * cDis)) / disSum;
  return colorVectorToColor(color);
}

Point3D<float> ColorCalculator::calculateVersorTo(Point3D<float> from,
                                                  Point3D<float> to) {
  auto v = (to - from);
  auto len = v.dis(Point3D<float>(0, 0, 0));
  return v / len;
}

Point3D<float> ColorCalculator::colorToColorVector(Color col) {
  return Point3D<float>((float)col.r/255, (float)col.g/255,
                        (float)col.b/255);
}

Point3D<float> ColorCalculator::normalMapColorToNormalVector(Color col) {
  float x = ((float)col.r/255.0) * 2.0 - 1.0;
  float y = ((float)col.g / 255.0) * 2.0 - 1.0;
  float z = ((float)col.b / 255.0);
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

  return Point<float>(vector.x + radius * 3.15f / 2,
                      vector.y + radius * 3.15 / 2);
}

Point3D<float>
ColorCalculator::joinNormalVectors(Point3D<float> sphereNormalVect,
                                   Point3D<float> normalMapVect) {
  Point3D<float> n(sphereNormalVect);
  Point3D<float> p(normalMapVect);

  Point3D<float> b(0, 1, 0);
  if(sphereNormalVect != Point3D<float>(0, 0, 1))
    b = sphereNormalVect.cross(Point3D<float>(0, 0, 1));

  auto t = b.cross(sphereNormalVect);

  return Point3D<float>(t.x*p.x + b.x*p.x + n.x*p.x,
                        t.y*p.y + b.y*p.y + n.y*p.y,
                        t.z*p.z + b.z*p.z + n.z*p.z);
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
