#include "renderConfig.h"
#include "mesh.h"

RenderConfig::RenderConfig(Mesh *mesh) : mesh(mesh) { }

RenderConfig::~RenderConfig() {
  delete mesh;
}

int RenderConfig::getMeridianCount() {
  return mesh->getMeridianCount();
}
void RenderConfig::setMeridianCount(int newMeridianCount) {
  mesh->setMeridianCount(newMeridianCount);
}

int RenderConfig::getParallelCount() {
  return mesh->getParallelCount();
}

void RenderConfig::setParallelCount(int newParallelCount) {
  mesh->setParallelCount(newParallelCount);
}

Mesh *RenderConfig::getMesh() {
  return mesh;
}
