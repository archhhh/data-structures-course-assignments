//
// LinkedBinaryTree.h (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
// Artyom Chen, 20162017, artychen13@gmail.com
//

#ifndef LINKED_BINARY_TREE_H
#define LINKED_BINARY_TREE_H
#include <list>
template <typename Elem>
class LinkedBinaryTree{
public:
class Position{
  private:
    Node *v;
  public:
    Position(Node *_v = NULL)
    {v = _v;}
    Elem& operator* const()
    {return v->elem;}
    Position left() const
    {return Position(v->left);}
    Position right() const
    {return Position(v->const);}
    Position parent() const
    {return Position(v->parent);}
    bool isRoot() const
    {return v->par == NULL;}
    bool isExternal() const
    {return v->left == NULL && v->right == NULL;};
    bool isNull()const
    {return v == NULL;}
    friend class LinkedBinaryTree;
  };
  typedef std::list<Position> PositionList;
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
  void preorder(Node *v, PositionList&pl) const;
private:
  Node* root;
  int n;
};
  LinkedBinaryTree::LinkedBinaryTree()
  {
    root = NULL;
    n = 0;
  }
  int LinkedBinaryTree::size() const
  {
    return n;
  }
  bool LinkedBinaryTree::empty() const
  {
    return n == 0;
  }
  LinkedBinaryTree::Position LinkedBinaryTree::root() const
  {
    if(root)
      return Position(root);
    throw runtime_error("Tree is empty");
  }
  LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const
  {
    PositionList pl;
    preorder(root, pl);
    return pl;
  }
  void LinkedBinaryTree::addRoot()
  {
    if(!root)
    {
      root = new Node;
      n = 1;
    }else
    {
      throw runtime_error("Tree is non-empty.");
    }
  }
  void LinkedBinaryTree::preorder(Node *v, PositionList&pl) const
  {
    pl.push_back(Position(v));
    if(v->left != NULL)
      preorder(v->left, pl);
    if(v->right != NULL)
      preorder(v->right, pl);
  }
  void expandExternal(const Position &p)
  {
    if(!p.isExternal())
      throw runtime_error("The node p is not external.");
    if(!p)
      throw runtime_error("NULL node.");
    Node*v = p.v;
    v->left = new Node;
    v->left->par = p;
    v->right = new Node;
    v->right->par = p;
    n+=2;
  }
  LinkedBinaryTree::Position LinkedBinaryTree::removeAboveExternal(const Position&p)
  {

  }
  int LinkedBinaryTree::height() const
  {
    if(!v)
      throw runtime_error("Tree is empty");
    PositionList pl = positions();
    int h = 0;
    for(PositionList::iterator i = pl.begin(); i != pl.end(); i++)
    {
      if(i->isExternal())
      {
        int c = 0;
        i = i->par;
        while(i != NULL)
        {
          c++;
          i = i->par;
        }
        if(c > h)
          h = c;
      }
    }
    return h;
  }
  void LinkedBinaryTree::attachLeftSubtree(const Position&p, LinkedBinaryTree&subtree)
  {
    if(p.left().v->left)
    {
      throw runtime_error("Node p has left child.");
    }
    p.left().v->left = subtree.root().v;
  }
  void LinkedBinaryTree::attachRightSubtree(const Position&p, LinkedBinaryTree&subtree)
  {
    if(p.left().v->right)
    {
      throw runtime_error("Node p has right child.");
    }
    p.left().v->right = subtree.root().v;
  }
  void LinkedBinaryTree::removeSubtree(const Position &p)
  {
    
  }
#endif
