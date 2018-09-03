//
// HeapPriorityQueue.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
/* Artyom Chen, 20162017, artychen13@unist.ac.kr
  Most of implementation is as decribed in the book.
  Two utility functions were added: BubbleUp, BubbleDown.
  BubbleUp for a given node swaps it upward the binary tree, unless the value of the parent of the
  given node is less than the node's.
  BubbleDown for a given node swaps it downward the binary tree, unless the value of
  the node is less than the node's children's.
  Also remove and replace functions were added. Remove for a given node swaps it with last node, calls T.removeLast() and bubble downs the swapped last node.
  If the size of the heap is 1, then simply calls T.removeLast();
  Replace for a given node and value replaces node's value to the given value. If new value is more than old, bubble down the node, otherwise,
  bubble up.

*/


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
public:
  typedef typename ArrayCompleteTree<E>::Position Position;
  HeapPriorityQueue();
  HeapPriorityQueue(const HeapPriorityQueue &q);
  int size() const;
  bool empty() const;
  Position insert(const E&e);
  const E& min();
  void removeMin();
  void remove(const typename ArrayCompleteTree<E>::Position &u);
  Position replace(const Position &p, const E& e);
private:

  ArrayCompleteTree<E> T;  // the array-based complete tree
  C isLess;                // the less-than comparator

  void bubbleUp(const Position& u);
  void bubbleDown(const Position&u);

};
template<typename E, typename C>
HeapPriorityQueue<E,C>::HeapPriorityQueue():T(), isLess(){
}
template<typename E, typename C>
HeapPriorityQueue<E,C>::HeapPriorityQueue(const HeapPriorityQueue&q):T(q.T), isLess(){
}
template<typename E, typename C>
int HeapPriorityQueue<E,C>::size() const{
  return T.size();
}
template<typename E, typename C>
bool HeapPriorityQueue<E,C>::empty() const{
  return T.size() == 0;
}
template<typename E, typename C>
typename HeapPriorityQueue<E, C>::Position HeapPriorityQueue<E,C>::insert(const E&e){
  T.addLast(e);
  Position last = T.last();
  bubbleUp(last);
  return last;
}
template<typename E, typename C>
const E& HeapPriorityQueue<E,C>::min(){
  return *T.root();
}
template<typename E, typename C>
void HeapPriorityQueue<E,C>::removeMin(){
  remove(T.root());
}
template<typename E, typename C>
void HeapPriorityQueue<E,C>::remove(const HeapPriorityQueue<E, C>::Position &u){
  if(size() == 1)
    T.removeLast();
  else{
    Position a = T.last();
    T.swap(u, a);
    T.removeLast();
    bubbleDown(a);
  }
}
template<typename E, typename C>
typename HeapPriorityQueue<E, C>::Position HeapPriorityQueue<E,C>::replace(const typename HeapPriorityQueue<E, C>::Position &p, const E& e){
  if(e < *p)
  {
    *p = e;
    bubbleUp(p);
  }else if(e > *p)
  {
    *p = e;
    bubbleDown(p);
  }
  return p;
}
template<typename E, typename C>
void HeapPriorityQueue<E,C>::bubbleUp(const typename HeapPriorityQueue<E, C>::Position&u){
  while(!T.isRoot(u) && isLess(*u, *T.parent(u)))
    T.swap(u, T.parent(u));
}
template<typename E, typename C>
void HeapPriorityQueue<E,C>::bubbleDown(const typename HeapPriorityQueue<E, C>::Position &u){
  while(T.hasLeft(u))
  {
    Position v = T.left(u);
    if(T.hasRight(u) && isLess(*(T.right(u)), *v))
      v = T.right(u);
    if(isLess(*v, *u))
        T.swap(u,v);
    else
      break;
  }
}
#endif //ASSIGNMENT3_HEAPPRIORITYQUEUE_H
