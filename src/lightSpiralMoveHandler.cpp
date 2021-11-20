#include "lightSpiralMoveHandler.h"
#include <cmath>

LightSpiralMoveHandler::LightSpiralMoveHandler(float periodTime,
                                               float periodDistance,
                                               float range)
  : currTime(0), periodTime(periodTime),
    periodDistance(periodDistance), range(range) {
  wholeMoveTime = 2 * range * periodTime / periodDistance;
}

Point3D<float>
LightSpiralMoveHandler::getLightPosition(float dt,
                                         Point3D<float> currPos,
                                         Point3D<float> meshCenterPos) {
  currTime = fmodf(currTime + dt, wholeMoveTime);

  float phi = currTime/periodTime * 2 * M_PI;
  float radius = periodDistance / (2 * M_PI) * phi;

  if(radius > range)
    radius = range - fmodf(radius, range);

  float x = meshCenterPos.x + radius * cos(phi);
  float y = meshCenterPos.y + radius * sin(phi);

  return Point3D<float>(x, y, currPos.z);
}
