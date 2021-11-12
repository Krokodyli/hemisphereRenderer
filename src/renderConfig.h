#pragma once

#include "Point3D.h"
#include "color.h"
#include "resourceManager.h"
#include "bitmap.h"
#include <string>
#include <unordered_map>

class Mesh;

class RenderConfig {
 private:
  Mesh *mesh;
  Point3D<float> lightPosition;
  Color lightColor;

  float kd;
  float ks;
  int m;
  float k;

  bool renderMeshMode;
  bool spiralMoveMode;

  Bitmap *currTexture;
  Bitmap *currNormalMap;

  std::unordered_map<std::string, Bitmap*> textures;
  std::unordered_map<std::string, Bitmap *> normalMaps;

public:
  RenderConfig(Mesh *mesh);
  ~RenderConfig();

  void loadResources(ResourceManager *resourceManager);

  int getMeridianCount();
  void setMeridianCount(int newMeridianCount);

  int getParallelCount();
  void setParallelCount(int newParallelCount);

  Point3D<float> getLightPosition();
  void setLightPosition(Point3D<float> newPos);

  Color getLightColor();
  void setLightColor(Color newColor);

  Color getTextureColor(Point<float> p);
  Color getNormalMapColor(Point<float> p);

  float getKD();
  void setKD(float newkd);

  float getKS();
  void setKS(float newks);

  float getM();
  void setM(float newm);

  float getK();
  void setK(float newk);

  float getLightZ();
  void setLightZ(float newZ);

  bool getRenderMeshModeStatus();
  void setRenderMeshModeStatus(bool newStatus);

  bool getSpiralMoveModeStatus();
  void setSpiralMoveModeStatus(bool newStatus);

  Bitmap *getTexture();
  void setTexture(Bitmap *bitmap);

  Bitmap *getNormalMap();
  void setNormalMap(Bitmap *bitmap);

  Mesh *getMesh();
};
