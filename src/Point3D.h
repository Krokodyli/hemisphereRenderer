#pragma once

#include <math.h>

template <typename T>
struct Point3D {
  T x, y, z;
  Point3D(T x, T y, T z);

  Point3D operator+(const Point3D &r);
  Point3D operator-(const Point3D &r);
  Point3D operator*(const T &r);
  Point3D operator*(const Point3D &r);
  Point3D operator/(const T &r);
  bool operator==(const Point3D &r);
  bool operator!=(const Point3D &r);

  double dis(const Point3D &r);
  T dissq(const Point3D &r);

  float dot(const Point3D &r);
};


template <typename T>
Point3D<T>::Point3D(T x, T y, T z) : x(x), y(y), z(z) { }

template <typename T>
Point3D<T> Point3D<T>::operator+(const Point3D &r) {
  return Point3D(x + r.x, y + r.y, z + r.z);
}

template <typename T>
Point3D<T> Point3D<T>::operator-(const Point3D &r) {
  return Point3D(x - r.x, y - r.y, z - r.z);
}

template <typename T>
Point3D<T> Point3D<T>::operator*(const T &r) {
  return Point3D(x * r, y * r, z * r);
}

template <typename T> Point3D<T> Point3D<T>::operator*(const Point3D<T> &r) {
  return Point3D(x * r.x, y * r.z, z * r.z);
}

template <typename T>
Point3D<T> Point3D<T>::operator/(const T &r) {
  return Point3D(x / r, y / r, z / r);
}

template <typename T>
bool Point3D<T>::operator==(const Point3D &r) {
  return x == r.x && y == r.y && z == r.z;
}

template <typename T>
bool Point3D<T>::operator!=(const Point3D &r) {
  return !operator==(r);
}

template <typename T>
double Point3D<T>::dis(const Point3D &r) {
  return sqrt(dissq(r));
}

template <typename T>
T Point3D<T>::dissq(const Point3D &r) {
  return (x-r.x)*(x-r.x) + (y-r.y)*(y-r.y) + (z-r.z)*(z-r.z);
}

template <typename T>
float Point3D<T>::dot(const Point3D<T> &r) {
  return x*r.x + y * r.y + z * r.z;
}
