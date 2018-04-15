//
// LinkedBinaryTree.h (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
// Artyom Chen, 20162017, artychen13@gmail.com
//
/*
  Class LinkedBinaryTree describes binary tree stucture with nodes. Every node is decribed through the struct
  Node, which is a protected member of LinkedBinaryTree. Node has element of type Elem, pointer to the left and
  right children, parent. Also there is constructor that initializes a node. Access to the nodes is provided
  through Position ADT, which is described through public class Position. Class contains private member Node * v
  which is pointer to node. Besides, it has several member functions: constructor, which initializes node;
  overloaded operator *, which returns element of Node; left, right, parent, which return Position of left,
  right children or parent respectively; isRoot, which returns true, if the Position object points to root,
  false otherwise; isExternal, which returns true, if the Position object points to external Node, false otherwise;
  isNull, which returns True, if the Position object points to Null pointer, false otherwise.
  To grant access to the node to the class LinkedBinaryTree, class is made as friend of Position class.
  In addition, class LinkedBinaryTree has private members Node *root, which points to root of the binary tree,
  and int n, which stores the number of nodes in the LinkedBinaryTree object. Also, class has the following functions:
  constructor, which initializes an empty tree; size, which returns n; empty, which returns True, if tree is empty, false otherwise;
  root, which returns Position object pointing to root; positions, which returns List ADT of Position objects, which stores
  Position objects of all nodes. List ADT is provided by <list> STL, and objects are stored in preorder traversal; addRoot, which
  creates a root Node. Throws exception, if tree is not empty; preorder is utility to help positions function to implement preorder
  traversal; expandExternal, given Position object pointing to external node, adds left and right children to it, throws exception if object points to NULL, or
  not external; removeAboveExternal, given Position object pointing to external node, delets the node pointed by object and its parent. Grandparent
  then points to the left or right child, depending on on which site the deleted parent was. Function returns a new child of grandparent.
  Throws exception, if the given object points to NULL, not external node, or root node; height, returns the height of the tree.
  If tree is empty, throws exception, otherwise it goes through positions of all nodes. If the node is external, then checks the depth of
  the node. Returns maximum depth of all external nodes; attachLeftSubtree, given Position object and LinkedBinaryTree object, attachs LinkedBinaryTree
  object as left subtree to the tree at Position object. Throws exception, if Position object has left child. Does not do anything,
  if the Position object points to NULL. Cleans LinkedBinaryTree object; attachRightSubtree is implemented as attachLeftSubtree;
  removeSubtree, given Position object pointing to the root of subtree, deletes the subtree. If Position object points to NULL node, does nothing,
  otherwise, deletes the tree one by one using recursion, where base case is external node.


*/
#ifndef LINKED_BINARY_TREE_H
#define LINKED_BINARY_TREE_H

#include <list>
#include <stdexcept>

using namespace std;

template <typename Elem>
class LinkedBinaryTree{
protected:
  struct Node{
    Elem elem;
    Node* par;
    Node* left;
    Node* right;
    Node():
    elem(), par(NULL), left(NULL), right(NULL)
    { }
  };
public:
  class Position{
    private:
      Node *v;
    public:
      Position(Node *_v = NULL)
      {v = _v;}
      Elem& operator*() const
      {return v->elem;}
      Position left() const
      {return Position(v->left);}
      Position right() const
      {return Position(v->right);}
      Position parent() const
      {return Position(v->par);}
      bool isRoot() const
      {return v->par == NULL;}
      bool isExternal() const
      {return v->left == NULL && v->right == NULL;};
      bool isNull()const
      {return v == NULL;}
      friend class LinkedBinaryTree;
  };
public:
  typedef list<Position> PositionList;
  LinkedBinaryTree();
  int size() const;
  bool empty() const;
  Position root() const;
  PositionList positions() const;
  void addRoot();
  void expandExternal(const Position&p);
  Position removeAboveExternal(const Position&p);
  int height() const;
  void attachLeftSubtree(const Position& p, LinkedBinaryTree& subtree);
  void attachRightSubtree(const Position& p, LinkedBinaryTree& subtree);
  void removeSubtree(const Position&p);
private:
  Node* _root;
  int n;
protected:
  void preorder(Node *v, PositionList&pl) const;
};


template <typename Elem>
LinkedBinaryTree<Elem>::LinkedBinaryTree()
{
  _root = NULL;
  n = 0;
}
template <typename Elem>
int LinkedBinaryTree<Elem>::size() const
{
  return n;
}
template <typename Elem>
bool LinkedBinaryTree<Elem>::empty() const
{
  return n == 0;
}
template <typename Elem>
typename LinkedBinaryTree<Elem>::Position LinkedBinaryTree<Elem>::root() const
{
  return Position(_root);
}
template <typename Elem>
typename LinkedBinaryTree<Elem>::PositionList LinkedBinaryTree<Elem>::positions() const
{
  typename LinkedBinaryTree<Elem>::PositionList pl;
  if(_root)
    preorder(_root, pl);
  return pl;
}
template <typename Elem>
void LinkedBinaryTree<Elem>::addRoot()
{
  if(_root)
    throw runtime_error("Tree is not empty.");
  _root = new Node;
  n = 1;
}
template <typename Elem>
void LinkedBinaryTree<Elem>::preorder(Node *v, PositionList&pl) const
{
  pl.push_back(Position(v));
  if(v->left != NULL)
    preorder(v->left, pl);
  if(v->right != NULL)
    preorder(v->right, pl);
}
template <typename Elem>
void LinkedBinaryTree<Elem>::expandExternal(const Position &p)
{
  if(p.isNull())
    throw runtime_error("NULL node.");
  if(!p.isExternal())
    throw runtime_error("The node p is not external.");
  Node*v = p.v;
  v->left = new Node;
  v->left->par = p.v;
  v->right = new Node;
  v->right->par = p.v;
  n+=2;
}
template <typename Elem>
typename LinkedBinaryTree<Elem>::Position LinkedBinaryTree<Elem>::removeAboveExternal(const Position&p)
{
    if(p.isNull())
      throw runtime_error("NULL node.");
    if(!p.isExternal())
      throw runtime_error("The node p is not external.");
    if(p.isRoot())
      throw runtime_error("Root node.");
    Node*w = p.v;
    Node*v = w->par;
    Node*sib = (w == v->left ? v->right : v->left);
    if(v == _root)
    {
      _root = sib;
      sib->par = NULL;
    }else
    {
      Node*gpar = v->par;
      if(v == gpar->left)
        gpar->left = sib;
      else
        gpar->right = sib;
      sib->par = gpar;
    }
    delete w;
    delete v;
    n-=2;
    return Position(sib);
}
template <typename Elem>
int LinkedBinaryTree<Elem>::height() const
{
  if(!_root)
    throw runtime_error("Tree is empty");
  typename LinkedBinaryTree<Elem>::PositionList pl = positions();
  int h = 0;
  for(typename LinkedBinaryTree<Elem>::PositionList::iterator i = pl.begin(); i != pl.end(); i++)
  {
    if((*i).isExternal())
    {
      int c = 0;
      Position t = *i;
      t = t.parent();
      while(!t.isNull())
      {
        c++;
        t = t.parent();
      }
      if(c > h)
        h = c;
    }
  }
  return h;
}
template <typename Elem>
void LinkedBinaryTree<Elem>::attachLeftSubtree(const Position&p, LinkedBinaryTree&subtree)
{
  if(!p.isNull())
  {
    if(!p.left().isNull())
      throw runtime_error("Node p has left child.");
    (p.v)->left = subtree.root().v;
    (p.v)->left->par = p.v;
    n += subtree.n;
    subtree._root = NULL;
    subtree.n = 0;
  }
}
template <typename Elem>
void LinkedBinaryTree<Elem>::attachRightSubtree(const Position&p, LinkedBinaryTree&subtree)
{
  if(!p.isNull())
  {
    if(!p.right().isNull())
      throw runtime_error("Node p has right child.");
    (p.v)->right = subtree.root().v;
    (p.v)->right->par = p.v;
    n += subtree.n;
    subtree._root = NULL;
    subtree.n = 0;
  }
}
template <typename Elem>
void LinkedBinaryTree<Elem>::removeSubtree(const Position &p)
{
  if(!p.isNull())
  {
    if(p.isExternal())
    {
      delete p.v;
    }else
    {
      Position l = p.left();
      Position r = p.right();
      delete p.v;
      removeSubtree(l);
      removeSubtree(r);
    }
    n--;
  }
}
#endif
