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
public:
  class Entry{
  public:
    Entry(const K&k = K(), const V& v = V()):
    _key(k), _value(v){}
    const K& key() const{ return _key;}
    V& value(){return _value;}
    void setValue(const V& v){_value = v;}
  private:
    K _key;
    V _value;
  };
  typedef list<Entry> Bucket;
  typedef vector<Bucket> BktArray;
  typedef typename BktArray::iterator BItor;
  typedef typename Bucket::iterator EItor;
  class Iterator{
  private:
    BItor bkt;
    EItor ent;
    const BktArray* ba;
    Iterator(const BktArray& a, const BItor &b,  const EItor& q = EItor()):
    ent(q), bkt(b), ba(&a){}
  public:
    Entry & operator*() const;
    bool operator==(const Iterator&p)const;
    Iterator & operator++();
    friend class HashMap;
  };

  HashMap(int capacity = 100): n(), B(capacity){}
  int size() const;
  bool empty() const;
  Iterator find(const K& k);
  Iterator put(const K& k, const V& v);
  void erase(const K&k);
  void erase(const Iterator &p);
  Iterator begin();
  Iterator end();
  V& operator[](const K&k);
private:
  H hash;
  int n;
  BktArray B;
protected:
  Iterator finder(const K&k);
  Iterator inserter(const Iterator&p, const Entry &e);
  void eraser(const Iterator&p);
  static void nextEntry(Iterator&p){++p.ent;}
  static bool endOfBkt(const Iterator&p){return p.ent == p.bkt->end();}
};
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K,V,H>::finder(const K&k)
{
  int i = hash(k) % B.size();
  BItor bkt = B.begin() + i;
  Iterator p(B, bkt, bkt->begin());
  while(!endOfBkt(p) && (*p).key() != k)
    nextEntry(p);
  return p;
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K,V,H>::inserter(const typename HashMap<K, V, H>::Iterator&p, const typename HashMap<K, V, H>::Entry &e)
{
  EItor ins = p.bkt->insert(p.ent,e);
  n++;
  return Iterator(B, p.bkt, ins);
}
template <typename K, typename V, typename H>
void HashMap<K,V,H>::eraser(const typename HashMap<K, V, H>::Iterator&p)
{
  p.bkt->erase(p.ent);
  n--;
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Entry& HashMap<K,V,H>::Iterator::operator*() const{
  return *ent;
}
template <typename K, typename V, typename H>
bool HashMap<K,V,H>::Iterator::operator==(const typename HashMap<K,V,H>::Iterator &p) const{
  if(ba != p.ba || bkt != p.bkt) return false;
  if(bkt == ba->end())   return true;
  return (ent == p.ent);
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K,V,H>::Iterator::operator++(){
  ++ent;
  if(endOfBkt(*this)){
    ++bkt;
    while(bkt!=ba->end() && bkt->empty())
      ++bkt;
    if(bkt == ba->end()) return *this;
    ent = bkt->begin();
  }
  return *this;
}
template <typename K, typename V, typename H>
int HashMap<K,V,H>::size() const{
  return n;
}
template <typename K, typename V, typename H>
bool HashMap<K,V,H>::empty() const{
  return n == 0;
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K,V,H>::find(const K&k){
  Iterator p = finder(k);
  if(endOfBkt(p))
    return end();
  else
    return p;
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K,V,H>::put(const K&k, const V&v){
  Iterator p = finder(k);
  if(endOfBkt(p))
    return inserter(p,Entry(k,v));
  else{
    p.ent->setValue(v);
    return p;
  }
}
template <typename K, typename V, typename H>
void HashMap<K,V,H>::erase(const K&k){
  Iterator p = finder(k);
  if(endOfBkt(p))
    throw runtime_error("No such key.");
  eraser(p);
}
template <typename K, typename V, typename H>
void HashMap<K,V,H>::erase(const typename HashMap<K,V,H>::Iterator &p){
  eraser(p);
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K,V,H>::begin(){
  if(empty()) return end();
  BItor bkt = B.begin();
  while(bkt->empty()) ++bkt;
  return Iterator(B, bkt, bkt->begin());
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K,V,H>::end(){
  return Iterator(B, B.end());
}
template <typename K, typename V, typename H>
V& HashMap<K,V,H>::operator[](const K&k){
  Iterator p = finder(k);
  if (endOfBkt(p)) {
    Iterator ins = inserter(p, Entry(k));
    return (*ins).value();
  }
  return (*p).value();
}
#endif //ASSIGNMENT3_HASHMAP_H
