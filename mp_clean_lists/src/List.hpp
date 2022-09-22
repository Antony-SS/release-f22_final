/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

template <class T>
List<T>::List(ListNode* head, ListNode* tail, int length) // this is a problem
    : head_(head), tail_(tail), length_(length)
{
    
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_); // CHANGED THIS FROM NULL TO HEAD
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL); // I think this is actually right
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (length_ != 0) {
    ListNode* curr = head_;
    while (curr != NULL) {
      ListNode* tmpNext = curr->next;
      delete curr;
      curr = tmpNext;
    }
    
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */

// DONE (95% certainty)
template <typename T>
void List<T>::insertFront(T const & ndata) { 
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);

  // I am sure about these two
  newNode -> next = head_;
  newNode -> prev = NULL;

  // Case 1 : First node in list(both head and tail should pt to A)  Null | A
  // Case 2: Anything other than first node:  A | B <-> A

  // handles Case 2, in which case the the now second node, still pnted to by head, needs to get a previous pointer to new node.
  if (head_ != NULL) { 
    head_ -> prev = newNode;
  }

  head_ = newNode; // in whatever case we need to assign head to this node

  // only time tail should be updated at insert front is when the new node is the first one.
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */

// Done (95% certainty)
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1

  ListNode * newNode = new ListNode(ndata);

  // sure about these two
  newNode->next = NULL;
  newNode->prev = tail_;

  // Case 1 : First node in list(both head and tail should pt to A)  Null | A
  // Case 2: Anything other than first node:  A | A <-> B

  if (tail_ != NULL) {  // means added node isnt' first one, have to update current tail's next ptr
    tail_ -> next = newNode;
  } 

  tail_ = newNode; // whatever case, tail has to become newNode

  if (head_ == NULL) { // if inserted node is first one (head_ is null) then head & tail should pt to new Node
    head_ = newNode;
  }

  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1

  if(splitPoint == 0){ // in this case the the new list starts at the current start point
    return start;
  }

  ListNode* curr = start;
  for(int i = 0; i < splitPoint; ++i){ 
    // temp = second;
    // second = second->next;
    curr = curr->next;
  }

  if (curr != NULL) {
    tail_ = curr->prev; // I think I need this
    curr->prev->next = NULL;
    curr->prev = NULL;
  }
  
  // think about updating head, tail, and length or current list . . . not sure if we should . . .
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1

  // handle edge case with less than 3 nodes

  if (length_ < 3) {
    return;
  }

  ListNode* curr = head_;

  for (int i = 0; i < length_ - 2; i += 3) { // think the range here works
    std::cout << i << std::endl;
    ListNode* index0 = curr;
    ListNode* index1 = curr->next;
    ListNode* index2 = curr->next->next;

    // first we need to change index 0s previous pointer, but keep it in a tmp var b/c we will need it for index 2; previous;
    ListNode* index0tmpprevious = index0->prev;
    index0->prev = index2;
    index1->prev = index0tmpprevious;
    ListNode* index2tmpnext = index2->next;
    index2->next = index0;
    index0->next = index2tmpnext;
    if (i != 0) { // means we are not dealing with a head so we can access prev-> next. . . 
      index0->prev->next = index2;
    } else if (i == 0) {
      head_ = index2;
    }

    index1->next = index2tmpnext; // used tmp2prevnext!, don't use again

    if (i + 3 != length_ ) { // not dealing with a tail node . . . . 
      index2tmpnext->prev = index1;
    } else { // dealing with a tail . . . 
      tail_ = index1;
    }
    return;
  }



}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  return NULL;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  return NULL;
}
