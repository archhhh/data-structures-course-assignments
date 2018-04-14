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

using namespace std;

LinkedBinaryTree<Symbol> parsePostfixExpression(list<string> tokens){
  stack < LinkedBinaryTree<Symbol> >st;
  for(list <string>::iterator i = tokens.begin(); i != tokens.end(); i++)
  {
    Symbol a(*i);
    LinkedBinaryTree<Symbol> tr;
    tr.addRoot();
    LinkedBinaryTree<Symbol>::Position b = tr.root();
    *b = a;
    if(a.isOperator())
    {
      if(st.empty())
        throw runtime_error("Invalid expression.");
      LinkedBinaryTree<Symbol> right = st.top();
      st.pop();
      if(st.empty())
        throw runtime_error("Invalid expression.");
      LinkedBinaryTree<Symbol> left = st.top();
      st.pop();
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
void print_inorder_recursive(const LinkedBinaryTree<Symbol>::Position& root)
{
  if(root.isExternal())
  {
    cout << *root << ' ';
  }else
  {
    cout << "( ";
    print_inorder_recursive(root.left());
    cout << *root << ' ';
    print_inorder_recursive(root.right());
    cout << ") ";
  }
}
void print_inorder(const LinkedBinaryTree<Symbol>& tree){
   print_inorder_recursive(tree.root());
}
void print_postorder(const LinkedBinaryTree<Symbol>& tree) {
  if(!tree.empty())
  {
    stack < LinkedBinaryTree<Symbol>::Position > st;
    stack < LinkedBinaryTree<Symbol>::Position > res;
    st.push(tree.root());;
    while(!st.empty())
    {
      LinkedBinaryTree<Symbol>::Position a = st.top();
      st.pop();
      res.push(a);
      if(!a.left().isNull())
        st.push(a.left());
      if(!a.right().isNull())
        st.push(a.right());
    }
    while(!res.empty())
    {
      cout << *res.top();
      if(res.size() != 1)
        cout << ' ';
      res.pop();
    }
  }
}
int findMinimumDepth(const LinkedBinaryTree<Symbol>& tree, const Symbol& sym) {
  typename LinkedBinaryTree<Symbol>::PositionList a = tree.positions();
  int h = tree.height()+1;
  for(typename LinkedBinaryTree<Symbol>::PositionList::iterator i = a.begin(); i != a.end(); i++)
  {
    if(**i == sym)
    {
      int c = 0;
      LinkedBinaryTree<Symbol>::Position t = *i;
      t = t.parent();
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
  typename LinkedBinaryTree<Symbol>::PositionList a = tree.positions();
  for(typename LinkedBinaryTree<Symbol>::PositionList::iterator i = a.begin(); i != a.end(); i++)
  {
    if(**i == variable)
      **i = constant;
  }
}
void simplify_subtree(LinkedBinaryTree<Symbol>& tree) {
  if(!tree.empty())
  {
    stack < LinkedBinaryTree<Symbol>::Position > st;
    stack < LinkedBinaryTree<Symbol>::Position > res;
    st.push(tree.root());
    while(!st.empty())
    {
      LinkedBinaryTree<Symbol>::Position a = st.top();
      st.pop();
      res.push(a);
      if(!a.left().isNull())
        st.push(a.left());
      if(!a.right().isNull())
        st.push(a.right());
    }
    typename LinkedBinaryTree<Symbol>::PositionList a;
    while(!res.empty())
    {
      a.push_back(res.top());
      res.pop();
    }
    stack < LinkedBinaryTree<Symbol> >temp;
    for(typename LinkedBinaryTree<Symbol>::PositionList::iterator i = a.begin(); i != a.end(); i++)
    {
      LinkedBinaryTree<Symbol> tr;
      tr.addRoot();
      LinkedBinaryTree<Symbol>::Position b = tr.root();
      *b = **i;
      if((**i).isOperator())
      {
        if(temp.empty())
          throw runtime_error("Invalid expression.");
        LinkedBinaryTree<Symbol> right = temp.top();
        temp.pop();
        if(temp.empty())
          throw runtime_error("Invalid expression.");
        LinkedBinaryTree<Symbol> left = temp.top();
        temp.pop();
        if((*right.root()).isConstant() && (*left.root()).isConstant())
        {
          if((**i).getOperator() == 3)
            if((*right.root()).getConstant() == 0)
              throw runtime_error("Divide by 0");
          *b = Symbol((**i).compute((*left.root()).getConstant(), (*right.root()).getConstant()));
        }else
        {
          tr.attachLeftSubtree(b, left);
          tr.attachRightSubtree(b, right);
        }
      }
      temp.push(tr);
    }
    if(!temp.empty())
      tree = temp.top();
  }
}
