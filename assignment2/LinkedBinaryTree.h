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
using namespace std;
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
  LinkedBinaryTree<Elem>::LinkedBinaryTree()
  {
    root = NULL;
    n = 0;
  }
  int LinkedBinaryTree<Elem>::size() const
  {
    return n;
  }
  bool LinkedBinaryTree<Elem>::empty() const
  {
    return n == 0;
  }
  LinkedBinaryTree<Elem>::Position LinkedBinaryTree<Elem>::root() const
  {
    if(root)
      return Position(root);
    throw runtime_error("Tree is empty");
  }
  LinkedBinaryTree<Elem>::PositionList LinkedBinaryTree<Elem>::positions() const
  {
    PositionList pl;
    if(!root)
      throw runtime_error("NULL root.");
    preorder(root, pl);
    return pl;
  }
  void LinkedBinaryTree<Elem>::addRoot()
  {
    if(root)
      throw runtime_error("Tree is non-empty.");
    root = new Node;
    n = 1;
  }
  void LinkedBinaryTree<Elem>::preorder(Node *v, PositionList&pl) const
  {
    pl.push_back(Position(v));
    if(v->left != NULL)
      preorder(v->left, pl);
    if(v->right != NULL)
      preorder(v->right, pl);
  }
  void LinkedBinaryTree<Elem>::expandExternal(const Position &p)
  {
    if(p.isNull())
      throw runtime_error("NULL node.");
    if(!p.isExternal())
      throw runtime_error("The node p is not external.");
    Node*v = p.v;
    v->left = new Node;
    v->left->par = p;
    v->right = new Node;
    v->right->par = p;
    n+=2;
  }
  LinkedBinaryTree<Elem>::Position LinkedBinaryTree<Elem>::removeAboveExternal(const Position&p)
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
      if(v == root)
      {
        root = sib;
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
  int LinkedBinaryTree<Elem>::height() const
  {
    if(!root)
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
  void LinkedBinaryTree<Elem>::attachLeftSubtree(const Position&p, LinkedBinaryTrees&subtree)
  {
    if(p.left().v)
    {
      throw runtime_error("Node p has left child.");
    }
    p.left().v = subtree.root().v;
  }
  void LinkedBinaryTree<Elem>::attachRightSubtree(const Position&p, LinkedBinaryTree&subtree)
  {
    if(p.right().v)
    {
      throw runtime_error("Node p has right child.");
    }
    p.right().v = subtree.root().v;
  }
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
    }
  }
#endif
