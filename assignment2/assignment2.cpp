//
// assignment2.cpp
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//

#include <iostream>
#include <stdexcept>
#include <list>
#include <stack>
#include <limits>
#include "LinkedBinaryTree.h"
#include "Symbol.h"
#include "assignment2.h"


LinkedBinaryTree<Symbol> parsePostfixExpression(list<string> tokens){
  stack < LinkedBinaryTree<Symbol> >st;
  for(list <string>::iterator i = tokens.begin(); tokens[i] != '#'; i++)
  {
    Symbol a(*i);
    LinkedBinaryTree<Symbol> tr;
    tr.addRoot();
    Position b = tr.root();
    *b = a;
    if(a.isOperator())
    {
      if(st.empty())
        throw runtime_error("Invalid expression.");
      LinkedBinaryTree<Symbol> right = st.pop();
      if(st.empty())
        throw runtime_error("Invalid expression.");
      LinkedBinaryTree<Symbol> left = st.pop();
      tr.attachLeftSubtree(b, left);
      tr.attachRightSubtree(b, right);
    }
    st.push(tr);
  }
  if(!st.empty())
    return st.top();
  else
    return LinkedBinaryTree<Symbol>();
}
void print_inorder(const LinkedBinaryTree<Symbol>& tree){
  if(!tree.empty())
  {
    stack < typename LinkedBinaryTree<Symbol>::Position > st;
    LinkedBinaryTree<Symbol> currentNode = tree.root();
    while(1){
      while(!currentNode.isNull())
      {
        if(*currentNode.isOperator())
          cout << '(';
        st.push(currentNode);
        currentNode = currentNode.left();
      }
      if(st.empty())
        return;
      currentNode = st.top();
      st.pop();
      cout << *currentNode;
      currentNode = currentNode.right();
    }
  }
}
void print_postorder(const LinkedBinaryTree<Symbol>& tree) {
  if(!tree.empty())
  {
    stack < typename LinkedBinaryTree<Symbol>::Position > st;
    stack < typename LinkedBinaryTree<Symbol>::Position > res;
    st.push(tree.root());
    while(!st.empty())
    {
      typename LinkedBinaryTree<Symbol>::Position a = st.top();
      st.pop();
      res.push(a);
      if(*a.left())
        st.push(a.left());
      if(*a.right())
        st.push(a.right());
    }
    while(!res.empty())
    {
      cout << *res.top();
      res.pop();
    }
  }
}
int findMinimumDepth(const LinkedBinaryTree<Symbol>& tree, const Symbol& sym) {
  list < typename LinkedBinaryTree<Symbol>::Position > a = tree.positions();
  int h = tree.height()+1;
  for(list < typename LinkedBinaryTree<Symbol>::Position >::iterator i = a.begin(); i != a.end(); i++)
  {
    if(**i == sym)
    {
      int c = 0;
      typename LinkedBinaryTree<Symbol>::Position t = *i;
      while(!t.isNull())
      {
        c++;
        t = t.parent();
      }
      if(c < h)
        h = c;
    }
  }
  if(h == tree.height()+1)
    return -1;
  return h;
}


void substitute(const LinkedBinaryTree<Symbol>& tree, const Symbol& variable, const Symbol& constant) {
  list < typename LinkedBinaryTree<Symbol>::Position > a = tree.positions();
  for(list < typename LinkedBinaryTree<Symbol>::Position >::iterator i = a.begin(); i != a.end(); i++)
  {
    if(**i == variable)
      **i = constant;
  }
}


void simplify_subtree(LinkedBinaryTree<Symbol>& tree) {

}
