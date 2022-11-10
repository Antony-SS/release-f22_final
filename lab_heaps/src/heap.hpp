
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <cassert>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.


    size_t leftChildIndex = (currentIdx*2)+1;

    return leftChildIndex;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.

    size_t rightChildIndex = (currentIdx*2) + 2;

    return rightChildIndex;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    assert(currentIdx < _elems.size());
    if (currentIdx == 0) { // if index is 0, special case b/c we don't want to return negative
        return 0;
    } else {
        // using int to floor result
    
        int parent = (currentIdx - 1) / 2;
        return ((unsigned) parent);
    }
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{

    unsigned childIndex = leftChild(currentIdx); 

    // only have to check left b/c tree is pushed all the way to left, so if left doesn't exist, neither does right

    if (childIndex < _elems.size()) {
        return true;
    } else {
        return false;
    }
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    unsigned rightIndex = rightChild(currentIdx);

    if (rightIndex > _elems.size() - 1) { // if right out of bounds just return leftData 
        return leftChild(currentIdx);
    }

    // otherwise do comparison 

    T leftData = _elems.at(leftChild(currentIdx));
    T rightData = _elems.at(rightChild(currentIdx));

    if (higherPriority(leftData, rightData)) { // not sure if I am using higher priority right
        return leftChild(currentIdx);
    } else {
        return rightChild(currentIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (!hasAChild(currentIdx)) {
        return;
    }

    unsigned min = maxPriorityChild(currentIdx);
    if (_elems[currentIdx] > _elems[min]) {
        std::swap(_elems[currentIdx], _elems[maxPriorityChild(currentIdx)]);
        heapifyDown(min);
    }

    return;


}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    for (unsigned i = 0; i < elems.size(); ++i) {
        push(elems.at(i));
    }

    return;

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty()) {
        return T();
    }
    
    std::swap(_elems[root()], _elems[_elems.size() - 1]);
    T toReturn = _elems[_elems.size() - 1];
    _elems.pop_back();
    heapifyDown(0);
    return toReturn;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return (_elems.empty());
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
