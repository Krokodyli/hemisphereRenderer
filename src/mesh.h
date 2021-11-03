#pragma once

#include <math.h>
#include <set>
#include <vector>
#include <iostream>

#include <SFML/System/Vector3.hpp>

using std::vector;
using std::set;
using std::pair;
using sf::Vector3f;

struct MeshEdge {
  Vector3f *a, *b;

  MeshEdge(Vector3f *_a, Vector3f *_b);
};

struct MeshTriangle {
  Vector3f *a, *b, *c;

  MeshTriangle(Vector3f *_a, Vector3f *_b, Vector3f *_c);
};

class Mesh {
 private:
  Vector3f center;
  float radius;
  int parallelCount, meridianCount;

  vector<Vector3f*> points;

  vector<MeshEdge> edges;
  vector<MeshTriangle> triangles;

  void clearMesh();
  void generateMesh();
  void generatePoints();
  void generateEdges();
  void generateTriangles();

  void addPoint(float x, float y, float z);
  void addPoint(sf::Vector3f v);
 public:
  Mesh(Vector3f _center, float _radius, int _parallelCount, int _meridianCount);

  int getMeridianCount();
  int getParallelCount();
  void setMeridianCount(int newCount);
  void setParallelCount(int newCount);

  Vector3f *getPoint(int p, int m);
  const vector<Vector3f*> &getPoints();
  const vector<MeshTriangle> &getTriangles();
  const vector<MeshEdge> &getEdges();
};
