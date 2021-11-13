#include "renderConfig.h"
#include "mesh.h"

RenderConfig::RenderConfig(Mesh *mesh)
  : mesh(mesh), lightPosition(0, 0, 0) { }

RenderConfig::~RenderConfig() {
  delete mesh;
}

void RenderConfig::loadResources(ResourceManager *resourceManager) {
  textures = resourceManager->getTextures();
  normalMaps = resourceManager->getNormalMaps();
  currTexture = nullptr;
  currNormalMap = nullptr;
  currNormalMap = normalMaps["test0.png"];
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

Color RenderConfig::getTextureColor(Point<float> p) {
  if(currTexture == nullptr)
    return Color(255, 255, 255);

  return currTexture->getPixelColor(p.x, p.y);
}

Color RenderConfig::getNormalMapColor(Point<float> p) {
  if (currNormalMap == nullptr)
    return Color(0, 0, 0);

  return currNormalMap->getPixelColor(p.x, p.y);
}

float RenderConfig::getKD() {
  return kd;
}

void RenderConfig::setKD(float newkd) {
  kd = newkd;
}

float RenderConfig::getKS() {
  return ks;
}

void RenderConfig::setKS(float newks) {
  ks = newks;
}

float RenderConfig::getM() {
  return m;
}

void RenderConfig::setM(float newm) {
  m = newm;
}

float RenderConfig::getK() {
  return k;
}

void RenderConfig::setK(float newk) {
  k = newk;
}

float RenderConfig::getLightZ() {
  return lightPosition.z;
}

void RenderConfig::setLightZ(float newZ) {
  lightPosition.z = newZ;
}

bool RenderConfig::getRenderMeshModeStatus() {
  return renderMeshMode;
}

void RenderConfig::setRenderMeshModeStatus(bool newStatus) {
  renderMeshMode = newStatus;
}

bool RenderConfig::getSpiralMoveModeStatus() {
  return spiralMoveMode;
}

void RenderConfig::setSpiralMoveModeStatus(bool newStatus) {
  spiralMoveMode = newStatus;
}

Bitmap *RenderConfig::getTexture() {
  return currTexture;
}

void RenderConfig::setTexture(Bitmap *bitmap) {
  currTexture = bitmap;
}

Bitmap *RenderConfig::getNormalMap() {
  return currNormalMap;
}

void RenderConfig::setNormalMap(Bitmap *bitmap) {
  currNormalMap = bitmap;
}

std::vector<std::string> RenderConfig::getTexturesNames() {
  std::vector<std::string> names;
  for(auto entry : textures)
    names.push_back(entry.first);
  return names;
}

std::vector<std::string> RenderConfig::getNormalMapsNames() {
  std::vector<std::string> names;
  for (auto entry : normalMaps)
    names.push_back(entry.first);
  return names;
}

void RenderConfig::setTexture(std::string name) {
  auto element = textures.find(name);
  if(element != textures.end())
    currTexture = element->second;
  else
    currTexture = nullptr;
}

void RenderConfig::setNormalMap(std::string name) {
  auto element = normalMaps.find(name);
  if (element != normalMaps.end())
    currNormalMap = element->second;
  else
    currNormalMap = nullptr;
}

bool RenderConfig::getApproximateColoringMode() {
  return approximateColoringMode;
}

void RenderConfig::setApproximateColoringMode(bool val) {
  approximateColoringMode = val;
}

Mesh *RenderConfig::getMesh() {
  return mesh;
}
