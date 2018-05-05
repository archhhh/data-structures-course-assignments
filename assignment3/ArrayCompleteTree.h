//
// ArrayCompleteTree.h  (Version 1.1)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#ifndef ASSIGNMENT3_ARRAYCOMPLETETREE_H
#define ASSIGNMENT3_ARRAYCOMPLETETREE_H

// You are *not* allowed to include other header files

#include <iostream>
#include <stdexcept>

using namespace std;


/*
 * An array-based, adaptable complete tree with location-aware entries.
 * This implementation is based on Section 8.3 and Section 8.4 in the textbook.
 * The difference is that the underlying data structure is a raw array.
 * When the array runs out of space, the doubling strategy is employed
 * to enlarge the array.
 *
 * Notice that you are *not* allowed to define any other member variables in this class.
 */
template<typename E>
class ArrayCompleteTree {
public:

  /*
   * Locator
   */
  class Locator {
    int i;   // the index of the location-aware entry in v


  };

  /*
   * Location Aware Entry
   */
  class LocationAwareEntry {
    E e;             // the element
    Locator *loc;    // a pointer to the locator of this entry


  };

  /*
   * Position
   */
  class Position {
    const ArrayCompleteTree* tree;     // a pointer to the ArrayCompleteTree object that this position object works for.
    Locator *loc;                       // a pointer to the locator object of the entry pointed by this Position object.


  };




private:

  LocationAwareEntry* v;   // the array of location-aware entries
  int vsize;               // the size of v
  int n;                   // the number of used entries in v

};


#endif //ASSIGNMENT3_ARRAYCOMPLETETREE_H
