/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

#include<queue>

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

  bool visited(int x, int y) const;
  void setVisited(int x, int y);

private:
  /** @todo [Part 1] */
  /** add private members here*/
  std::queue<Point> toVisit;
  double tolerance_;
  const PNG& png_;
  Point startPt;
  std::vector<std::vector<int>> seen;
};
