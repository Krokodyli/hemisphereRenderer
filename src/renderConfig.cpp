#include "renderConfig.h"
#include "mesh.h"

RenderConfig::RenderConfig(Mesh *mesh, AppConsts *appConsts)
  : mesh(mesh), appConsts(appConsts), lightPosition(0, 0, 0) {
  lightPosition = Point3D<float>(appConsts->relativeMeshPos.x,
                                 appConsts->relativeMeshPos.y,
                                 appConsts->defaultLightZPos);
  lightColor = appConsts->defaultLightColor;
  kd = appConsts->defaultKD;
  ks = appConsts->defaultKS;
  m = appConsts->defaultM;
  k = appConsts->defaultK;

  approximateColoringMode = appConsts->defaultApproximateColoringMode;
  renderMeshMode = appConsts->defaultRenderMeshMode;
  spiralMoveMode = appConsts->defaultSpiralMoveMode;

  currTexture = nullptr;
  currNormalMap = nullptr;
}

void RenderConfig::loadResources(ResourceManager *resourceManager) {
  textures = resourceManager->getTextures();
  normalMaps = resourceManager->getNormalMaps();
}

Color RenderConfig::getTextureColor(Point<float> p) {
  if(currTexture == nullptr)
    return appConsts->defaultTextureColor;

  return currTexture->getPixelColor(p.x, p.y);
}

Color RenderConfig::getNormalMapColor(Point<float> p) {
  if (currNormalMap == nullptr)
    return appConsts->defaultNormalMapColor;

  return currNormalMap->getPixelColor(p.x, p.y);
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
