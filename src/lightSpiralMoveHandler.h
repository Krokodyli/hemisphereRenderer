#pragma once

#include "Point3D.h"

class LightSpiralMoveHandler {
 private:
  float currTime;
  float periodTime, periodDistance, range;
  float wholeMoveTime;
 public:
  LightSpiralMoveHandler(float periodTime, float periodDistance, float range);
  Point3D<float> getLightPosition(float dt, Point3D<float> currPos,
                                  Point3D<float> meshCenterPos);
};
