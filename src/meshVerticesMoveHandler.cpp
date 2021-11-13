#include "meshVerticesMoveHandler.h"

MeshVerticesMoveHandler::MeshVerticesMoveHandler()
  : grabbedVertex(nullptr) { }

void MeshVerticesMoveHandler::update(Controller *controller,
                                RenderConfig *renderConfig) {
  auto mesh = renderConfig->getMesh();
  auto mousePos = controller->getMousePos();
  if(controller->isLeftClicked()) {
    grabbedVertex = nullptr;
    for(auto meshPoint : mesh->getPoints()) {
      auto point = Point<float>(meshPoint->x, meshPoint->y);
      if(isMouseOverPoint(point, mousePos))
        grabbedVertex = meshPoint;
    }
  }

  if(!controller->isLeftPressed())
    grabbedVertex = nullptr;

  if(grabbedVertex != nullptr) {
    grabbedVertex->x = mousePos.x;
    grabbedVertex->y = mousePos.y;
  }
}

bool MeshVerticesMoveHandler::isMouseOverPoint(Point<float> point,
                                               Point<float> mousePos) {
  return mousePos.insideRec(point.x - grabTolerance.x,
                            point.y - grabTolerance.y,
                            grabTolerance.x * 2,
                            grabTolerance.y * 2);
}
