#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance): png_(png) {  
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
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, startPt, &png_, tolerance_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */ // think this might stay the same
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  toVisit.push(point);
  // not sure I have to do anything else
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point tmp = toVisit.top();
  toVisit.pop();
  return tmp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return toVisit.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if (toVisit.empty()) {
    return true;
  } else {
    return false;
  }
}

bool DFS::visited(int x, int y) const {
  if (seen[x][y] == 1) {
    return true;
  } else {
    return false;
  }
}

void DFS::setVisited(int x, int y) {
  seen[x][y] = 1;
}

