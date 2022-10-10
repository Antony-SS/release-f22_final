#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance): png_(png) {  
  /** @todo [Part 1] */

  tolerance_ = tolerance;
  startPt = start;
  toVisit.push(startPt);

  // leave current point uninitialized?

  // I think a map actually may be more effective but Im not sure if we are allowed to use
  // going to use vector over array b/c I don't have to deal with memory
  int height = png.height();
  int width = png.width();

  // resize seen vector into size of image and intialize all members to 0
  // CHECK THIS IF GETTING WEIRD SHIT
  // seen.resize(width, std::vector<int> (height, 0));

  // think this should do it
  seen.resize(width);
  for (unsigned i = 0; i < seen.size(); i++) {
    seen[i].resize(height , 0);
  }

  
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, startPt, &png_, tolerance_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  toVisit.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point tmp = toVisit.front();
  toVisit.pop();
  return tmp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  return toVisit.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return toVisit.empty();
}

bool BFS::visited(int x, int y) const {
  if (seen.at(x).at(y)) {
    return true;
  } else {
    return false;
  }
}

void BFS::setVisited(int x, int y) {
  seen.at(x).at(y) = 1;
}
