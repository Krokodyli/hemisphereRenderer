#pragma once

#include "controller.h"
#include "mesh.h"
#include "renderConfig.h"

class MeshVerticesMoveHandler {
 private:
  const Point<float> grabTolerance = Point<float>(3, 3);
  Point3D<float> *grabbedVertex;

  bool isMouseOverPoint(Point<float> point, Point<float> mousePos);
 public:
  MeshVerticesMoveHandler();
  void update(Controller *controller, RenderConfig *renderConfig);
};
