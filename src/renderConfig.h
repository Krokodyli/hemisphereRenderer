#pragma once

#include "Point3D.h"
#include "color.h"

class Mesh;

class RenderConfig {
 private:
  Mesh *mesh;
  Point3D<float> lightPosition;
  Color lightColor;
  float kd;
  bool renderMeshMode;

 public:
  RenderConfig(Mesh *mesh, Point3D<float> lightPosition, Color lightColor,
               float kd);
  ~RenderConfig();

  int getMeridianCount();
  void setMeridianCount(int newMeridianCount);

  int getParallelCount();
  void setParallelCount(int newParallelCount);

  Point3D<float> getLightPosition();
  void setLightPosition(Point3D<float> newPos);

  Color getLightColor();
  void setLightColor(Color newColor);

  float getKD();
  void setKD(float newkd);

  bool getRenderMeshModeStatus();
  void setRenderMeshModeStatus(bool newStatus);

  Mesh *getMesh();
};
