//
// HeapPriorityQueue.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#ifndef ASSIGNMENT3_HEAPPRIORITYQUEUE_H
#define ASSIGNMENT3_HEAPPRIORITYQUEUE_H

// You are *not* allowed to include other header files

#include <iostream>
#include <stdexcept>
#include "ArrayCompleteTree.h"

using namespace std;


/*
 * This is a generic less-than comparator that relies on operator<() to
 * compare two objects. This generalizes the LeftRight class on Page 326
 * in the textbook.
 */
template<typename T>
class LessThanComparator {
public:
  bool operator()(const T& a, const T& b) const { return a < b; }
};


/*
 * A heap-based priority queue based on ArrayCompleteTree.
 * See Section 8.3.4 in the textbook for more information.
 *
 * Notice that you are *not* allowed to define any other member variables in this class.
 */
template<typename E, typename C>
class HeapPriorityQueue {





private:

  ArrayCompleteTree<E> T;  // the array-based complete tree
  C isLess;                // the less-than comparator

};


#endif //ASSIGNMENT3_HEAPPRIORITYQUEUE_H
