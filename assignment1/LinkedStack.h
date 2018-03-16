//
// LinkedStack.h - Version 1.0
//
// This file is created by Tsz-Chiu Au on 9/24/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#ifndef ASSIGNMENT1_STACK_H
#define ASSIGNMENT1_STACK_H

#include <stdexcept>
#include "CircularList.h"

using namespace std;


/*
 * A stack based on a CircularList
 */
template<typename Elem>
class LinkedStack {

  CircularList<Elem> cir_list;  // the circular list of elements

public:

  /*
   * Get the size of the stack.
   *
   * return the number of elements in the stack
   */
  int size() const { return cir_list.size(); }

  /*
   * Check whether the stack is empty.
   *
   * return true if the stack has no element
   */
  bool empty() const { return cir_list.empty(); }

  /*
   * Get a reference to the element at the top of the stack.
   *
   * return a reference to the top element.
   */
  Elem& top() const;

  /*
   * Push an element onto the stack.
   *
   * e - the element
   */
  void push(const Elem& e) { cir_list.add(e); }

  /*
   * Pop the top element on the stack. The top element
   * will be removed from the stack.
   */
  void pop();  // pop the stack
};


template<typename Elem>
Elem& LinkedStack<Elem>::top() const {
  if (cir_list.empty()) throw runtime_error("Cannot get the top element from an empty stack.");
  return cir_list.front();
}


template<typename Elem>
void LinkedStack<Elem>::pop() {
  if (cir_list.empty()) throw runtime_error("Cannot remove the top element from an empty stack.");
  cir_list.remove();
}

#endif //ASSIGNMENT1_STACK_H
