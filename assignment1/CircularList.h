//
// CircularList.h (Version 1.0)
//
// Please write your name, your student ID, and your email address here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
/*
  Artyom Chen 20162017 artychen13@unist.ac.kr
class CircularList consists of 3 member variables, class CNode, 9 functions and also constructor with destructor
class CNode contains value and the pointer to the next CNode object, cursor is pointer to the last node in the list,
space is pointer to the available space list.


*/
#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H
#include <stdexcept>

using namespace std;

template <typename Elem>
class CircularList{
public:
  CircularList();
  ~CircularList();
  bool empty() const;
  Elem& front() const;
  Elem& back() const;
  void advance();
  void add(const Elem& e);
  void remove();
  int size() const;
  void reverse();
  void cleanup();
private:
  class CNode{
      Elem value;
      CNode* next;
      friend class CircularList;
  };
  CNode* cursor;
  CNode* space;
  int s;
};
template <typename Elem>
CircularList<Elem>::CircularList()
{
      s = 0;
      cursor = NULL;
      space = NULL;
}
template <typename Elem>
CircularList<Elem>::~CircularList()
{
      if(!empty())
      {
        CNode* f = cursor->next;
        cursor->next = space;
        space = f;
      }
      cleanup();
}
template <typename Elem>
bool CircularList<Elem>::empty() const
{
    return s == 0;
}
template <typename Elem>
Elem& CircularList<Elem>::front() const
{
      if(empty())
        throw runtime_error("List is empty.");
      return cursor->next->value;
}
template <typename Elem>
Elem& CircularList<Elem>::back() const
{
      if(empty())
        throw runtime_error("List is empty.");
      return cursor->value;
}
template <typename Elem>
void CircularList<Elem>::advance()
{
    if(!empty())
      cursor = cursor->next;
}
template <typename Elem>
void CircularList<Elem>::add(const Elem& e)
{
      CNode* n;
      if(space)
      {
        n = space;
        space = space->next;
      }else{
        n = new CNode;
      }
      n->value = e;
      if(empty())
      {
        cursor = n;
        cursor->next = cursor;
      }else
      {
        n->next = cursor->next;
        cursor->next = n;
      }
      s++;
}
template <typename Elem>
void CircularList<Elem>::remove()
{
      if(empty())
        throw runtime_error("List is empty.");
      CNode* t = cursor->next;
      if(t == cursor)
      {
        cursor = NULL;
      }else
      {
        cursor->next = t->next;
      }
      t->next = space;
      space = t;
      s--;
}
template <typename Elem>
int CircularList<Elem>::size() const{
    return s;
}
template <typename Elem>
void CircularList<Elem>::reverse()
{
      if(!empty())
      {
        CNode* prev = cursor->next;
        CNode* curr = prev->next;
        while(curr != cursor)
        {
            CNode* t = prev;
            prev = curr;
            curr = prev->next;
            prev->next = t;
        }
        CNode* b = cursor->next;
        b->next = cursor;
        cursor->next = prev;
        cursor = b;
      }
}
template <typename Elem>
void CircularList<Elem>::cleanup()
{
    while(space != NULL)
    {
      CNode*old = space;
      space = space->next;
      delete old;
    }
}
#endif
