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
  public:
    Locator(int _i){
      i = _i;
    }
  private:
    int i;   // the index of the location-aware entry in v
    friend class ArrayCompleteTree;
  };
  /*
   * Location Aware Entry
   */
  class LocationAwareEntry{
  public:
    LocationAwareEntry(){
      e = E();
      loc = NULL;
    }
    LocationAwareEntry(E _e, int i){
      e = _e;
      loc = new Locator(i);
    }
    void clear();
  private:
    E e;             // the element
    Locator *loc;    // a pointer to the locator of this entry
    friend class ArrayCompleteTree;
  };
  /*
   * Position
   */
  class Position {
  public:
    Position(){
      tree = NULL;
      loc = NULL;
    }
    Position(const ArrayCompleteTree * _tree, Locator * _loc){
      tree = _tree;
      loc = _loc;
    }
    bool operator==(const Position &p) const;
    E& operator*();
  private:
    const ArrayCompleteTree* tree;     // a pointer to the ArrayCompleteTree object that this position object works for.
    Locator *loc;                       // a pointer to the locator object of the entry pointed by this Position object.
    friend class ArrayCompleteTree;
  };
  ArrayCompleteTree(int _vsize = 10);
  ArrayCompleteTree(const ArrayCompleteTree& t);
  ~ArrayCompleteTree();
  int size() const;
  Position left(const Position &p) const;
  Position right(const Position &p) const;
  Position parent(const Position &p) const;
  bool hasLeft(const Position &p) const;
  bool hasRight(const Position &p) const;
  bool isRoot(const Position &p) const;
  Position root() const;
  Position last() const;
  void addLast(const E& e);
  void removeLast();
  void swap(const Position &p, const Position &q);
  void cleanup();
private:
  LocationAwareEntry* v;   // the array of location-aware entries
  int vsize;               // the size of v
  int n;                   // the number of used entries in v
};
template<typename E>
void ArrayCompleteTree<E>::LocationAwareEntry::clear(){
  delete loc;
  loc = NULL;
}
template<typename E>
bool ArrayCompleteTree<E>::Position::operator==(const Position &p) const{
  return (tree == p.tree) && (loc == p.loc);
}
template<typename E>
E& ArrayCompleteTree<E>::Position::operator*(){
  if(!tree)
    throw runtime_error("Wrong position.");
  if(!loc)
    throw runtime_error("Wrong position.");
  if(loc->i < 0 || loc->i >= tree->n)
    throw runtime_error("Wrong position.");
  if(tree->v[loc->i].loc != loc)
      throw runtime_error("Wrong position.");
  return tree->v[loc->i].e;
}
template<typename E>
ArrayCompleteTree<E>::ArrayCompleteTree(int _vsize = 10){
  v = new LocationAwareEntry[10];
  vsize = _vsize;
  n = 0;
}
template<typename E>
ArrayCompleteTree<E>::ArrayCompleteTree(const ArrayCompleteTree& t){
  _v = new LocationAwareEntry[t.vsize];
  vsize = t.vsize;
  n = t.n;
  for(int i = 0; i < n;i++)
    _v[i] = LocationAwareEntry((t.v)[i].e, (t.v)[i].loc->i);
  ~ArrayCompleteTree();
  v = _v;
}
template<typename E>
ArrayCompleteTree<E>::~ArrayCompleteTree(){
  for(int i = 0; i < n; i++)
    v[i].clear();
  delete [] v;
}
template<typename E>
int ArrayCompleteTree<E>::size() const{
  return n;
}
template<typename E>
Position ArrayCompleteTree<E>::left(const Position&p) const{
  if(!hasLeft(p))
    throw runtime_error("No left child.");
  return Position(this, v[2*((p.loc)->i)+1].loc);
}
template<typename E>
Position ArrayCompleteTree<E>::right(const Position&p) const{
  if(!hasRight(p))
    throw runtime_error("No right child.");
  return Position(this, v[2*((p.loc)->i)+2].loc);
}
template<typename E>
Position ArrayCompleteTree<E>::parent(const Position&p) const{
  if(isRoot(p))
    throw runtime_error("No parent.");
  return Position(this, v[(((p.loc)->i)+1)/2].loc);
}
template<typename E>
bool ArrayCompleteTree<E>::hasLeft(const Position &p) const{
  if(!p.tree)
    throw runtime_error("Wrong position.");
  if(!p.loc)
    throw runtime_error("Wrong position.");
  if(p.tree != this)
    throw runtime_error("Wrong position.");
  if((p.loc)->i < 0 || (p.loc)->i >= n)
    throw runtime_error("Wrong position.");
  if(p.tree->v[i].loc != p.loc)
    throw runtime_error("Wrong position.");
  if((2*((p.loc)->i)+1) >= n)
    return false;
  return true;
}
template<typename E>
bool ArrayCompleteTree<E>::hasRight(const Position &p) const{
  if(!p.tree)
    throw runtime_error("Wrong position.");
  if(!p.loc)
    throw runtime_error("Wrong position.");
  if(p.tree != this)
    throw runtime_error("Wrong position.");
  if((p.loc)->i < 0 || (p.loc)->i >= n)
    throw runtime_error("Wrong position.");
  if(p.tree->v[i].loc != p.loc)
    throw runtime_error("Wrong position.");
  if((2*((p.loc)->i)+2) >= n)
    return false;
  return true;
}
template<typename E>
bool ArrayCompleteTree<E>::isRoot(const Position &p) const{
  if(!p.tree)
    throw runtime_error("Wrong position.");
  if(!p.loc)
    throw runtime_error("Wrong position.");
  if(p.tree != this)
    throw runtime_error("Wrong position.");
  if((p.loc)->i < 0 || (p.loc)->i >= n)
      throw runtime_error("Wrong position.");
  if(p.tree->v[i].loc != p.loc)
      throw runtime_error("Wrong position.");
  if((p.loc->i) != 0)
      return false;
  return true;
}
template<typename E>
Position ArrayCompleteTree<E>::root() const{
  if(n == 0)
    throw runtime_error("Tree is empty.");
  return Position(this, v[0].loc);
}
template<typename E>
Position ArrayCompleteTree<E>::last() const{
  if(n == 0)
    throw runtime_error("Tree is empty.");
  return Position(this, v[n-1].loc);
}
template<typename E>
void ArrayCompleteTree<E>::addLast(const E& e){
  if(n < vsize)
  {
    v[n] = LocationAwareEntry(e, n);
  }else
  {
    _v = new LocationAwareEntry[2*vsize];
    for(int i = 0; i < n; i++)
      _v[i] = v[i];
    _v[n] = = LocationAwareEntry(e, n);
    delete [] v;
    v = _v;
    vsize = 2*vsize;
  }
  n++;
}
template<typename E>
void ArrayCompleteTree<E>::removeLast(const E& e){
  if(n == 0)
    throw runtime_error("Empty tree.");
  n--;
}
template<typename E>
void ArrayCompleteTree<E>::swap(const Position& p, const Position &q){
  if(!p.tree || !q.tree)
  if(p.tree != q.tree)
    throw runtime_error("Wrong position.");
  if(p.tree != this)
    throw runtime_error("Wrong position.");
  if(!p.loc || !q.loc)
    throw runtime_error("Wrong position.");
  if((p.loc)->i < 0 || (p.loc)->i >= n ||(q.loc)->i < 0 || (q.loc)->i >= n)
      throw runtime_error("Wrong position.");
  if(p.tree->v[i].loc != p.loc || q.tree->v[i].loc != q.loc)
      throw runtime_error("Wrong position.");
  E temp_e = *p;
  *p = *q;
  *q = temp_e;
  Locator * temp_loc = p.loc;
  p.loc = q.loc;
  q.loc = temp_loc;
  int temp_ind = p.loc->i;
  p.loc->i = q.loc->i;
  q.loc->i = p.loc->i;
  v[p.loc->i].loc = p.loc;
  v[q.loc->i].loc = q.loc;
}
template<typename E>
void ArrayCompleteTree<E>::cleanup(){
  if(n < vsize)
  {
    _v = new LocationAwareEntry[n];
    for(int i = 0; i < n; i++)
      _v[i] = v[i];
    for(int i = n; i < vsize; i++)
      v[i].clear;
    delete [] v;
    v = _v;
    vsize = n;
  }
}
#endif //ASSIGNMENT3_ARRAYCOMPLETETREE_H
