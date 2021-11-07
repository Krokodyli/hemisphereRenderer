#pragma once


class Mesh;

class RenderConfig {
 private:
  Mesh *mesh;

 public:
  RenderConfig(Mesh *mesh);
  ~RenderConfig();

  int getMeridianCount();
  void setMeridianCount(int newMeridianCount);

  int getParallelCount();
  void setParallelCount(int newParallelCount);

  Mesh *getMesh();
};
