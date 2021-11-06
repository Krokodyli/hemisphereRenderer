#pragma once

#include <math.h>
#include <set>
#include <vector>
#include <iostream>

#include "Point3D.h"

using std::vector;
using std::set;
using std::pair;

struct MeshEdge {
  Point3D<float> *a, *b;

  MeshEdge(Point3D<float> *_a, Point3D<float> *_b);
};

struct MeshTriangle {
  Point3D<float> *a, *b, *c;

  MeshTriangle(Point3D<float> *_a, Point3D<float> *_b, Point3D<float> *_c);
};

class Mesh {
 private:
  Point3D<float> center;
  float radius;
  int parallelCount, meridianCount;

  vector<Point3D<float>*> points;

  vector<MeshEdge> edges;
  vector<MeshTriangle> triangles;

  void clearMesh();
  void generateMesh();
  void generatePoints();
  void generateEdges();
  void generateTriangles();

  void addPoint(float x, float y, float z);
  void addPoint(Point3D<float> v);
 public:
  Mesh(Point3D<float> _center, float _radius, int _parallelCount,
       int _meridianCount);

  int getMeridianCount();
  int getParallelCount();
  void setMeridianCount(int newCount);
  void setParallelCount(int newCount);

  Point3D<float> *getPoint(int p, int m);
  const vector<Point3D<float>*> &getPoints();
  const vector<MeshTriangle> &getTriangles();
  const vector<MeshEdge> &getEdges();
};
