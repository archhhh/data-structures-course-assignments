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
typename HeapPriorityQueue<E, C>::Position HeapPriorityQueue<E,C>:: insert(const E&e){
  T.addLast(e);
  typename ArrayCompleteTree<E>::Position last = T.last();
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
  T.swap(u, T.last());
  T.removeLast();
  bubbleDown(u);
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
    if(T.hasRight(u) && isLess(*T.right(u), *v))
      v = T.right(u);
    if(isLess(*u, *v))
      T.swap(u,v);
    else
      break;
  }
}
#endif //ASSIGNMENT3_HEAPPRIORITYQUEUE_H
