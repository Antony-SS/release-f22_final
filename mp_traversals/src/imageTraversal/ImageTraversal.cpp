#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(): png_(nullptr) {
  /** @todo [Part 1] */
  traversal_ = nullptr;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point& startPt, const PNG* png, double& tolerance): png_(png) {
  // std::cout << "Calling constructor" << std::endl;
  startPt_ = startPt;
  traversal_ = traversal;
  currentPt_ = startPt;
  tolerance_ = tolerance;
  // std::cout << "Ending constructor" << std::endl;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  // std::cout << "Segfault-1" << std::endl;
  /** @todo [Part 1] */

  if (traversal_->empty()) {
    return *this;
  } 

  // this is going to be a lonnnggg case . . . .

  Point popped = traversal_->pop();
  traversal_->setVisited(popped.x, popped.y);

  const HSLAPixel & poppedpix = png_->getPixel(popped.x, popped.y);

  const HSLAPixel & startpix = png_->getPixel(startPt_.x, startPt_.y);
  // pixels around the pt, in the order they should be added

  std::cout << "x,y is: " <<  currentPt_.x << " , " << currentPt_.y << std::endl;

  Point right_ = Point(popped.x + 1, popped.y);
  Point below_ = Point(popped.x, popped.y + 1);
  Point left_ = Point(popped.x - 1, popped.y);
  Point top_ = Point(popped.x, popped.y - 1);

  // going right first
    // std::cout << "Segfault0" << std::endl;

  // if we approach a point from 2 directions it will be added to the stack/queue twice b/c it will be unseen, but will already be on the queue or stack.

  // so before we do any of this shit to add points/

  if (right_.x < png_->width()) {
    const HSLAPixel& currPix = png_->getPixel(right_.x, right_.y);
    double diff  = calculateDelta(startpix, currPix);
    if (diff < tolerance_ && !(traversal_->visited(right_.x, right_.y))) { // check tolerance and making sure it is not seen
      traversal_->add(right_);
    }
  }

  // std::cout << "Segfault1" << std::endl;

  // now below
  if (below_.y < png_->height()) {
    const HSLAPixel& currPix = png_->getPixel(below_.x, below_.y);
    double diff  = calculateDelta(startpix, currPix);
    if (diff < tolerance_ && !(traversal_->visited(below_.x, below_.y))) { // check tolerance and making sure it is not seen
      traversal_->add(below_);
    }
  }

  // std::cout << "Segfault2" << std::endl;

  // left .. DOUBLE CHECK GREATER THAN 0 BOUNDS 

  if (left_.x < png_->width()) { // since ints wrap around we are going to do a weird check here
    const HSLAPixel& currPix = png_->getPixel(left_.x, left_.y);
    double diff  = calculateDelta(startpix, currPix);
    if (diff < tolerance_ && !(traversal_->visited(left_.x, left_.y))) { // check tolerance and making sure it is not seen
      traversal_->add(left_);
    }
  }

  // above .. DOUBLE CHECK GREATER THAN 0 BOUNDS 

  // std::cout << "Segfault3" << std::endl;

    if (top_.y < png_->height()) { // since ints wrap around we are going to do a weird check here
    const HSLAPixel& currPix = png_->getPixel(top_.x, top_.y);
    double diff  = calculateDelta(startpix, currPix);
    if (diff < tolerance_ && !(traversal_->visited(top_.x, top_.y))) { // check tolerance and making sure it is not seen
      traversal_->add(top_);
    }
  }

  // now all points are added if in bounds, below tolerance, and not seen

  // if traversal is empty at this point we are done . . . 

  while (!traversal_->empty() && traversal_->visited(traversal_->peek().x, traversal_->peek().y)) {
    currentPt_ = traversal_->pop();
  }

  if (traversal_->empty()) {
    return *this;
  }
  // in the case that it isn't we update currentPt

  currentPt_ = traversal_->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  // std::cout << "Calling dereference" << std::endl;
  return currentPt_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal_ == nullptr) thisEmpty = true;
  if (other.traversal_ == nullptr) otherEmpty = true;

  if (!thisEmpty) thisEmpty = traversal_->empty();
  if (!otherEmpty) otherEmpty = other.traversal_->empty();

  if (thisEmpty && otherEmpty) return false;

  return true;
}


