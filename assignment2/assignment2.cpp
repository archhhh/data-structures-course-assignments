//
// assignment2.cpp
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
// Artyom Chen, 20162017, artychen13@gmail.com
/*
  parsePostfixExpression: given postorder expression, stores it in LinkedBinaryTree in postorder manner. Function is implemented, using stack of
  LinkedBinaryTree objects. As we go through the list, we store each token in a separate LinkedBinaryTree. If the token is operand, we simply
  put the tree into stack. If the token is operator, we take trees from the stack and append them to the current tree. If there are no trees available,
  throws exception, otherwise the resultant tree is stored again in stack.
  print_inorder: implemented, using utility function print_inorder_recursive, which prints nodes of LinkedBinaryTree object in inorder manner, which
  results in infix expression output. print_inorder_recursive takes Position object, initally pointing to root. If it reaches external Node, it simply
  outputs the value of the node, otherwise, "( " is printed, then the function calls itself recursively, passing Position object's left child, which
  allows to traverse to the left first. After it returns, middle value of the node passed to the calling function is printed, then using recursion,
  the function traverses to the right. Upon return, closing bracket is printed.
  print_postorder: prints the values of the tree in postorder manner. The function is implemented iteratively, using two stacks of Position objects,
  st and res, where res will store the resultant expression. The root node is pushed into st stack. Then, until st stack is empty, we take node from the st stack and
  push it to the res stack, while storing the children of current node in st stack. After that, the values are poped from res stack and printed, until res stack is
  empty.
  findMinimumDepth: given tree and symbol sym, finds the minimum depth of sym in the tree. If there is single node, containing sym, then it returns depth
  of that node. To implement the function, we simply go through the positions of all nodes. Variable int h contains minimum depth found so far. Notice, it
  is impossible for any node to have tree.height()+1 depth, since it is larger than height of the tree. If current position stores sym, function finds its depth,
  as it was implemented in LinkedBinaryTree.height() function, then the depth is compared to h, and if it is smaller, then assign current depth to h.
  If variable h is unchanged after iteration, that means that no node contains such symbol. Then, we simply return -1. Otherwise, h is returned.
  substitute: given tree, symbol variable and symbol constant, function changes value of each node containing symbol variable to symbol constant.
  Function iterates through positions of all nodes, and if current node's value is equal to variable, then the value is changed to constant.
  simplify_subtree: given tree, containing expression, function simplifes the tree, evaluating all the subtrees, whose external nodes are constant values.
  The implementation combines both of parsePostfixExpression and print_postorder. First, tree is traversed in postorder manner and all the nodes
  are stored as Position objects in PositionList. This PositionList contains expression in postorder notation. Then as in parsePostfixExpression,
  function iterates through the list, but if the operator is encountered and two operands poped from the stack are constants, then instead of
  attaching the trees, expression is evaluated and the value stored in the tree tr and then pushed to the stack. If there is division by 0 , functions
  throws exception.
   */
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
void print_inorder_recursive(const LinkedBinaryTree<Symbol>::Position& node)
{
  if(node.isExternal())
  {
    cout << *node << ' ';
  }else
  {
    cout << "( ";
    print_inorder_recursive(node.left());
    cout << *node << ' ';
    print_inorder_recursive(node.right());
    cout << ")";
    if(!node.isRoot())
      cout << ' ';
  }
}
void print_inorder(const LinkedBinaryTree<Symbol>& tree){
   if(!tree.empty())
    print_inorder_recursive(tree.root());
}
void print_postorder(const LinkedBinaryTree<Symbol>& tree) {
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
