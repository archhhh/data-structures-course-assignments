//
// HashMap.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#ifndef ASSIGNMENT3_HASHMAP_H
#define ASSIGNMENT3_HASHMAP_H

// You are *not* allowed to include other header files

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

/*
 * This is an integer hash comparator that defines a hash function,
 * which is operator(). The hash function simply returns the integer that
 * is given as the input. See Page 387 of the textbook for more information.
 */
class IntHashComparator {
public:
  int operator()(const int& a) const {
    return a;
  }
};


/*
 * A Map based on hashing with separate chaining.
 * See Section 9.2.7 of the textbook for more detail.
 *
 * Notice that you can define any member variables.
 */
template <typename K, typename V, typename H>
class HashMap {








};



#endif //ASSIGNMENT3_HASHMAP_H
