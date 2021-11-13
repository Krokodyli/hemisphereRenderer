#pragma once

#include "controller.h"
#include "mesh.h"
#include "renderConfig.h"

class MeshVerticesMoveHandler {
 private:
  Point<float> grabTolerance;
  Point3D<float> *grabbedVertex;

  bool isMouseOverPoint(Point<float> point, Point<float> mousePos);
 public:
  MeshVerticesMoveHandler(AppConsts *appConsts);
  void update(Controller *controller, RenderConfig *renderConfig);
};
