#include "mesh.h"
#include <SFML/System/Vector3.hpp>
#include <cmath>

MeshEdge::MeshEdge(Point3D<float> *_a, Point3D<float> *_b) : a(_a), b(_b) { }

MeshTriangle::MeshTriangle(Point3D<float> *_a, Point3D<float> *_b,
                           Point3D<float> *_c)
    : a(_a), b(_b), c(_c) { }

Mesh::Mesh(Point3D<float> _center, float _radius, int _parallelCount,
           int _meridianCount)
  : center(_center), radius(_radius), parallelCount(_parallelCount),
    meridianCount(_meridianCount) {
  generateMesh();
}

int Mesh::getMeridianCount() {
  return meridianCount;
}

int Mesh::getParallelCount() {
  return parallelCount;
}

void Mesh::setMeridianCount(int newCount) {
  if(newCount >= 4 && newCount != meridianCount) {
    meridianCount = newCount;
    generateMesh();
  }
}
void Mesh::setParallelCount(int newCount) {
  if(newCount >= 1 && newCount != parallelCount) {
    parallelCount = newCount;
    generateMesh();
  }
}

float Mesh::getRadius() {
  return radius;
}

Point3D<float> Mesh::getCenter() {
  return center;
}

float Mesh::calculateZ(float x, float y) {
  // Sometimes errors in floating point arithmetics cause
  // zsqr to be negative
  float zsqr = radius * radius - (x-center.x) * (x-center.x)
    - (y-center.y) * (y-center.y);
  if (zsqr < 0)
    zsqr = 0;
  return std::sqrt(zsqr) + center.z;
}

Point3D<float> *Mesh::getPoint(int p, int m) {
  if(p == 0 || m == 0)
    return points[0];
  else
    return points[(p-1) * meridianCount + m];
}

const vector<Point3D<float> *> &Mesh::getPoints() {
  return points;
}

const vector<MeshTriangle> &Mesh::getTriangles() {
  return triangles;
}

const vector<MeshEdge> &Mesh::getEdges() {
  return edges;
}

void Mesh::clearMesh() {
  for(auto point : points)
    delete point;
  points.clear();
  edges.clear();
  triangles.clear();
}

void Mesh::generateMesh() {
  clearMesh();
  generatePoints();
  generateEdges();
  generateTriangles();
}

void Mesh::generatePoints() {
  addPoint(center.x, center.y, center.z + radius);
  for (int i = 1; i <= parallelCount; i++) {
    float r = (float)i / parallelCount * radius;
    for (int j = 0; j < meridianCount; j++) {
      float phi = 2.0f * M_PI * j / (float)meridianCount;
      float x = r * cos(phi) + center.x;
      float y = r * sin(phi) + center.y;
      float z = calculateZ(x, y);
      addPoint(x, y, z);
    }
  }
}

void Mesh::generateEdges() {
  Point3D<float> *center = getPoint(0, 0);
  for(int m = 1; m <= meridianCount; m++)
    edges.emplace_back(center, getPoint(1, m));

  for(int p = 1; p < parallelCount; p++) {
    for(int m = 1; m <= meridianCount; m++) {
      int nextMeridian = 1 + m % meridianCount;
      edges.emplace_back(getPoint(p, m), getPoint(p+1, m));
      edges.emplace_back(getPoint(p, m), getPoint(p, nextMeridian));
      edges.emplace_back(getPoint(p, m), getPoint(p+1, nextMeridian));
    }
  }
  for(int m = 1; m <= meridianCount; m++) {
    int nextMeridian = 1 + m % meridianCount;
    edges.emplace_back(getPoint(parallelCount, m),
                       getPoint(parallelCount, nextMeridian));
  }
}

void Mesh::generateTriangles() {
  Point3D<float> *center = getPoint(0, 0);
  for(int m = 1; m <= meridianCount; m++) {
    int nextMerdian = 1 + m % meridianCount;
    triangles.emplace_back(getPoint(1, m), center, getPoint(1, nextMerdian));
  }

  for(int p = 1; p < parallelCount; p++) {
    for(int m = 1; m <= meridianCount; m++) {
      int nextMeridian = 1 + m % meridianCount;
      triangles.emplace_back(getPoint(p, m), getPoint(p + 1, nextMeridian),
                             getPoint(p + 1, m));
      triangles.emplace_back(getPoint(p, m), getPoint(p, nextMeridian),
                             getPoint(p + 1, nextMeridian));
    }
  }
}

void Mesh::addPoint(float x, float y, float z) {
  points.push_back(new Point3D<float>(x, y, z));
}

void Mesh::addPoint(Point3D<float> v) {
  points.push_back(new Point3D<float>(v));
}
