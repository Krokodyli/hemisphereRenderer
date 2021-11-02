#include "mesh.h"
#include <SFML/System/Vector3.hpp>
#include <cmath>

MeshEdge::MeshEdge(Vector3f *_a, Vector3f *_b) : a(_a), b(_b) { }

MeshTriangle::MeshTriangle(Vector3f *_a, Vector3f *_b, Vector3f *_c)
    : a(_a), b(_b), c(_c) { }

Mesh::Mesh(Vector3f _center, float _radius, int _precision)
  : center(_center), radius(_radius), precision(_precision) {
  generateMesh();
}

int Mesh::getPrecision() {
  return precision;
}

void Mesh::setPrecision(int _newPrecision) {
  if(_newPrecision == precision)
    return;
  if(_newPrecision < precision) {
    precision = _newPrecision;
    generateMesh();
  }
  else {
    for(int i = precision; i < _newPrecision; i++)
      subdivideMesh();
    precision = _newPrecision;
  }
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
  generateInitialMesh();
  for(int i = 1; i < precision; i++)
    subdivideMesh();
}

void Mesh::generateInitialMesh() {
  addPoint(center.x, center.y, center.z + radius);
  addPoint(center.x, center.y - radius, center.z);
  addPoint(center.x + radius, center.y, center.z);
  addPoint(center.x, center.y + radius, center.z);
  addPoint(center.x - radius, center.y, center.z);

  for(int i = 1; i <= 4; i++)
    edges.emplace_back(points[0], points[i]);
  for(int i = 0; i < 4; i++)
    edges.emplace_back(points[1 + i], points[1 + (i+1)%4]);

  for(int i = 0; i < 4; i++)
    triangles.emplace_back(points[1 + i], points[0], points[1+(i+1)%4]);
}

void Mesh::subdivideMesh() {
  vector<MeshTriangle> oldTriangles = triangles;
  triangles.clear();
  edges.clear();

  for(auto triangle : oldTriangles)
    subdivideTriangle(triangle);

  generateNewEdges();
}

void Mesh::subdivideTriangle(MeshTriangle triangle) {
  auto ap = triangle.a;
  auto bp = triangle.b;
  auto cp = triangle.c;
  addPoint(getMiddlePoint(*ap, *bp));
  auto abp = points[points.size()-1];
  addPoint(getMiddlePoint(*bp, *cp));
  auto bcp = points[points.size() - 1];
  addPoint(getMiddlePoint(*cp, *ap));
  auto cap = points[points.size() - 1];

  triangles.emplace_back(ap, abp, cap);
  triangles.emplace_back(cap, bcp, cp);
  triangles.emplace_back(cap, abp, bcp);
  triangles.emplace_back(abp, bp, bcp);
}

void Mesh::generateNewEdges() {
  set<pair<Vector3f*, Vector3f*>> newEdges;
  for(const auto &triangle : triangles) {
    if(triangle.a >= triangle.b)
      newEdges.insert({triangle.a, triangle.b});
    else
      newEdges.insert({triangle.b, triangle.a});

    if (triangle.b >= triangle.c)
      newEdges.insert({triangle.b, triangle.c});
    else
      newEdges.insert({triangle.c, triangle.b});

    if (triangle.c >= triangle.a)
      newEdges.insert({triangle.c, triangle.a});
    else
      newEdges.insert({triangle.a, triangle.c});
  }
  for(const auto &edge : newEdges)
    edges.emplace_back(MeshEdge(edge.first, edge.second));
}

Vector3f Mesh::getMiddlePoint(Vector3f a, Vector3f b) {
  Vector3f c = (a+b);
  c.x /= 2;
  c.y /= 2;
  c.z /= 2;
  return c;
}

void Mesh::addPoint(float x, float y, float z) {
  points.push_back(new sf::Vector3f(x, y, z));
}

void Mesh::addPoint(sf::Vector3f v) {
  points.push_back(new sf::Vector3f(v));
}
