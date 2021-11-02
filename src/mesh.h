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
  int precision;

  vector<Vector3f*> points;

  vector<MeshEdge> edges;
  vector<MeshTriangle> triangles;

  void clearMesh();
  void generateMesh();
  void generateInitialMesh();
  void subdivideMesh();

  void subdivideTriangle(MeshTriangle triangle);
  void generateNewEdges();

  Vector3f getMiddlePoint(Vector3f a, Vector3f b);
  void addPoint(float x, float y, float z);
  void addPoint(sf::Vector3f v);
public:
  Mesh(Vector3f _center, float _radius, int _precision = 1);

  int getPrecision();
  void setPrecision(int _newPrecision);

  const vector<MeshTriangle> &getTriangles();
  const vector<MeshEdge> &getEdges();
};
