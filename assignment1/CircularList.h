//
// CircularList.h (Version 1.0)
//
// Please write your name, your student ID, and your email address here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
/*
  Artyom Chen 20162017 artychen13@unist.ac.kr
  Class CircularList consists of 3 member variables, class CNode, 9 functions and also constructor with destructor
  class CNode contains value and the pointer to the next CNode object, cursor is pointer to the last node in the list,
  space is pointer to the first element of the available space list. Variable s counts the number of elements in the list.
  Constructor sets size counter to 0, cursor and space pointers to NULL.
  If the list is not empty, destructor transfers all the nodes to available space list and then uses function cleanup()
  to deallocate the memory used by CNode objects of the list.
  Function empty simply returns true, if the list is empty and 0 if it is not. Uses member variable s to get
  the information about list's size.
  Function front returns the value of the node that is after cursor. If the list is empty, throws exception.
  Function back returns the value of the node pointed by cursor. If the list is empty, throws exception.
  Function advance changes the cursor's position to the next node after the cursor. If the list is empty, does nothing.
  Function add adds the node after the cursor with value e. If there are any nodes available in available space list,
  takes the node from there, otherwise allocates new memory for the node. If the list is empty, set the cursor to point
  to the added node and set the next value of the node to be the same node, otherwise, set the node before the previous
  front value. Increments s variable.
  Function remove removes the node after the cursor. If the list is empty, throws an exception, otherwise
  checks whether there is only one node in the list. If it is, deallocate the node and set cursor value to NULL, otherwise
  deallocate the node and set cursor's next pointer to point to the node that was next to the deleted node. By deallocating
  it is meant that nodes are added to the available space list. Deincrements the s variable.
  Function size simply returns the value of s.
  Function reverse reverses the list. To implement the function, the following algorithm was used:
  if the list is empty, do nothing, otherwise store the front node in prev variable and the node next to the front node in
  curr variable. Until the curr variable points to the back element, make the curr node point to the prev node. Assign prev
  pointer to curr, and curr to curr->next. Once the curr pointer points to the back element, we have all the previous elements
  reversed, so the only thing left to do is to make cursor point to the element before cursor, make front element point to the cursor
  and make cursor point to the front node. Once we are done, our new front node is old back node and new back node is old front node
  with all other nodes reversed in direction.
  Function cleanup deallocates all the nodes in the available space list. Since space points to the first element of
  available space list, function deallocates the front node in the available space list and sets space pointer to the
  node following the deleted one. Continues the same process until space points to NULL.
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
