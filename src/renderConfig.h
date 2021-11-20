#pragma once

#include "Point3D.h"
#include <vector>
#include "appConsts.h"
#include "color.h"
#include "resourceManager.h"
#include "bitmap.h"
#include <string>
#include <unordered_map>

class Mesh;

struct RenderConfig {
  Mesh *mesh;
  AppConsts *appConsts;

  Point3D<float> lightPosition;
  Color lightColor;

  float kd;
  float ks;
  int m;
  float k;

  bool approximateColoringMode;

  bool renderMeshMode;
  bool spiralMoveMode;

  Bitmap *currTexture;
  Bitmap *currNormalMap;

  std::unordered_map<std::string, Bitmap*> textures;
  std::unordered_map<std::string, Bitmap *> normalMaps;

  RenderConfig(Mesh *mesh, AppConsts *appConsts);

  void loadResources(ResourceManager *resourceManager);

  Color getTextureColor(Point<float> p);
  Color getNormalMapColor(Point<float> p);

  Bitmap *getNormalMap();
  void setNormalMap(Bitmap *bitmap);

  std::vector<std::string> getTexturesNames();
  std::vector<std::string> getNormalMapsNames();

  void setTexture(std::string name);
  void setNormalMap(std::string name);
};
