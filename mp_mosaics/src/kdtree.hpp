/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    assert(curDim >= 0 && curDim <= Dim); // not sure if assert is ok here, might have to change to just returning false in the case that this causes problems
    
    double firstPt = first[curDim];
    double secondPt = second[curDim];

    if (firstPt < secondPt) {
      return true;
    } else if (firstPt == secondPt) {
      return (first < second);
    } else {
      return false;
    }

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double currentDist = 0;
    double potentialDist = 0;

    for (int i = 0; i < Dim; ++i) {
      double targetVal = target[i];

      // calcs for currentbest

      double currentBestval = currentBest[i];
      double diff = (targetVal - currentBestval)*(targetVal - currentBestval);

      currentDist += diff;

      // calcs for potential

      double potentialVal = potential[i];
      diff = (targetVal - potentialVal)*(targetVal - potentialVal);

      potentialDist += diff;

    }

    // currentDist and potentialDist now calculated

    if (potentialDist < currentDist) {
      return true;
    } else if (potentialDist == currentDist) {
      return (potential < currentBest);
    } else {
      return false;
    }



}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    if (newPoints.empty()) {
      size = 0;
      // root = new KDTreeNode();
      root = nullptr;
      return;
    } else {
      vector<Point<Dim>> copiedPts = newPoints;
      root = createHelper(0, copiedPts.size() - 1, 0, copiedPts);
      size = 0;
    }

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode *KDTree<Dim>::createHelper(int left, int right, int dim, vector<Point<Dim>>& pts) {

  if (left <= right) {
    KDTreeNode *tmp = new KDTreeNode(); // top level call will return the root
    int avg = (left + right) / 2; // will truncate, which will floor whatever value we end up getting

    tmp->point = quickSelect(left, right, dim, pts, avg);

    int rightSide = avg + 1;
    tmp->right = createHelper(rightSide, right, (dim + 1) % Dim, pts);

    int leftSide = avg - 1;
    tmp->left = createHelper(left, leftSide, (dim + 1) % Dim, pts);

    return tmp;
  } else {
    return nullptr;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(int left, int right, int dim, vector<Point<Dim>>& pts, int pivot) {
  

    int tmp = partition(left, right, dim, pts, pivot);

    if (pivot < tmp) {
      return quickSelect(left, tmp - 1, dim, pts, pivot);
    } else if (pivot == tmp) {
      return pts[tmp];
    } else {
      return quickSelect(tmp + 1, right, dim, pts, pivot);
    }
}

template <int Dim>
int KDTree<Dim>::partition(int left, int right, int dimension, vector<Point<Dim>>& pts, int pivotIndex) {
  

    Point<Dim> tmpRight = pts[right];
  	pts[right] = pts[pivotIndex];
  	pts[pivotIndex] = tmpRight;



  	int i = left;
    Point<Dim> temp = pts[right];
    int a = i;
  	while(a < right)
    {
      if(smallerDimVal(pts[a], pts[right],dimension) == true)
      {
        temp = pts[a];
        pts[a] = pts[i];
        pts[i] = temp;
        ++i;
      }
      ++a;
  	}

  	temp = pts[right];
  	pts[right] = pts[i];
  	pts[i] = temp;
    
  	return i;
  	
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

  clear(root);

  root = copy(other);
  size = other.size(); // not sure if I have to do this . . . 
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode *other)
{

  if (other == this) {
    return this;
  }
  
  if (other != NULL){
    KDTreeNode *tmp = new KDTreeNode();

    tmp->point = other->point;

    tmp->left = copy(other->left);
    tmp->right = copy(other->right); // recursive call to copy
    
    return tmp;
  } else {
    return nullptr;
  }
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  clear(root);

  root = copy(root, rhs);

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  if (root == nullptr) {
    clear(root);
  } else {
    return;
  }
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode*& subroot){

  if (subroot == nullptr) {
    return;
  } else {
    clear(subroot->left);
    clear(subroot->right);
    delete subroot;
    return;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighborHelper(root, query, 0);
  
    
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(typename KDTree<Dim>::KDTreeNode* subroot, const Point<Dim>& query, int dim) const
{

  int fromSide = 0;
  Point<Dim> best = subroot->point;

  if (subroot->right == nullptr && subroot -> left == nullptr) {
    return best;
  }

  if (subroot->left == nullptr) {
    fromSide = 2;
    best = findNearestNeighborHelper(subroot->right, query, (dim + 1) % Dim);
  } else if (subroot->right == nullptr) {
    fromSide = 1;
    best = findNearestNeighborHelper(subroot->left, query, (dim + 1) % Dim);
  } else if (smallerDimVal(query, subroot->point, dim)) { // means we want to go left if we can
    fromSide = 1;
    best =  findNearestNeighborHelper(subroot->left, query, (dim + 1) % Dim);
  } else { // go right
    fromSide = 2;
    best =  findNearestNeighborHelper(subroot->right, query, (dim + 1) % Dim);
  }


  if (shouldReplace(query, best, subroot->point)) {
    best = subroot->point;
  }
	
	// Calculate radius of closest point and then also split distance

  // calculate the distance from current point to query point (in current dimension)

  double dist = (subroot->point[dim] - query[dim])*(subroot->point[dim] - query[dim]);

  // now we have to calculate radius around this point and determine if we have to check other subtrees

  double rad = 0;

  for (int i = 0; i < Dim; ++i) {
    rad += (best[i] - query[i])*(best[i] - query[i]);
  }

	// Check if we need to traverse the other subtree or not
	if (dist <= rad) {
		KDTreeNode * toCheck;

    if (fromSide == 1) {
      toCheck = subroot->right;
    } else {
      toCheck = subroot->left;
    }

		if (toCheck != NULL) {  // If we can traverse other subtree, then traverse
			Point<Dim> potential = findNearestNeighborHelper(toCheck, query, (dim + 1) % Dim);
			// Replace currentbest if need be
			if (shouldReplace(query, best, potential)) {
        best = potential;
      } 
		}
	}
  
	return best;
}
