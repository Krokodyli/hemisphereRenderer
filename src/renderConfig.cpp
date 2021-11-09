#include "renderConfig.h"
#include "mesh.h"

RenderConfig::RenderConfig(Mesh *mesh, Point3D<float> lightPosition,
                           Color lightColor, float kd)
  : mesh(mesh), lightPosition(lightPosition), lightColor(lightColor), kd(kd),
    renderMeshMode(true) { }

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

Point3D<float> RenderConfig::getLightPosition() {
  return lightPosition;
}

void RenderConfig::setLightPosition(Point3D<float> newPos) {
  lightPosition = newPos;
}

Color RenderConfig::getLightColor() {
  return lightColor;
}

void RenderConfig::setLightColor(Color newColor) {
  lightColor = newColor;
}

float RenderConfig::getKD() {
  return kd;
}

void RenderConfig::setKD(float newkd) {
  kd = newkd;
}

bool RenderConfig::getRenderMeshModeStatus() {
  return renderMeshMode;
}

void RenderConfig::setRenderMeshModeStatus(bool newStatus) {
  renderMeshMode = newStatus;
}

Mesh *RenderConfig::getMesh() {
  return mesh;
}
