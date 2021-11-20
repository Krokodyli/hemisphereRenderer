#pragma once

#include <math.h>

template <typename T>
struct Point {
  T x, y;

  Point(T x, T y);

  Point operator+(const Point &r) const;
  Point operator-(const Point &r) const;
  Point operator*(const T &r) const;
  Point operator/(const T &r) const;
  bool operator==(const Point &r) const;
  bool operator!=(const Point &r) const;

  double dis(const Point &r) const;
  T dissq(const Point &r) const;

  bool insideRec(T _x, T _y, T width, T height) const;
  Point fix2Rec(Point min, Point max) const;
};

template <typename T>
Point<T>::Point(T x, T y) : x(x), y(y) { }

template <typename T>
Point<T> Point<T>::operator+(const Point &r) const {
  return Point(x + r.x, y + r.y);
}

template <typename T>
Point<T> Point<T>::operator-(const Point &r) const {
  return Point(x - r.x, y - r.y);
}

template <typename T>
Point<T> Point<T>::operator*(const T &r) const {
  return Point(x * r, y * r);
}

template <typename T>
Point<T> Point<T>::operator/(const T &r) const {
  return Point(x / r, y / r);
}

template <typename T>
bool Point<T>::operator==(const Point &r) const {
  return x == r.x && y == r.y;
}

template <typename T>
bool Point<T>::operator!=(const Point &r) const {
  return !operator==(r);
}

template <typename T>
double Point<T>::dis(const Point &r) const {
  return sqrt(dissq(r));
}

template <typename T>
T Point<T>::dissq(const Point &r) const {
  return (x-r.x)*(x-r.x) + (y-r.y)*(y-r.y);
}

template <typename T>
bool Point<T>::insideRec(T _x, T _y, T width, T height) const {
  return x >= _x && x <= _x + width && y >= _y && y <= _y + height;
}

template <typename T>
Point<T> Point<T>::fix2Rec(Point min, Point max) const {
  Point p(x, y);

  p.x = std::max(p.x, min.x);
  p.x = std::min(p.x, max.x - 1);

  p.y = std::max(p.y, min.y);
  p.y = std::min(p.y, max.y - 1);

  return p;
}

