//
// Created by rotem on 07/10/2021.
//

#ifndef _AVL_H_
#define _AVL_H_
#include <queue>
#include "Apartment.h"
#include "Stack.h"

class AVL {
 public:
  /**
   * To manage the tree nodes, we use a nested struct. This struct contains the
   * apartment corresponding to the node, the left son and the right son of the
   * node, both of them node type themselves.
   */
  struct node {
      Apartment data_;
      node *left_, *right_, *parent_;
      int h_;
      /**
       * Constructor - It can be expanded
       * @param data the corresponding apartment object
       * @param left child
       * @param right child
       * @param parent parent
       */
      /// Ctor
      node (Apartment data, node *left, node *right, node* parent);
      node& operator=(const node& rhs) = delete;
      node(const node& other);
      /// Getters
      node *get_left () const
      {
        return left_;
      }
      node *get_right () const
      {
        return right_;
      }
      const Apartment &get_data () const
      {
        return data_;
      }
      node *get_parent () const
      {
        return parent_;
      }
      int get_bf () const
      {
        if (left_ && right_)
          return left_->h_ - right_->h_;
        else if (left_)
          return left_->h_ + 1;
        else if (right_)
          return -1 - right_->h_ ;
        return 0;
      }
      int get_h () const
      {
        return h_;
      }
      /// Methods
      void height_update();
      void left_rotation (node* u);
      void right_rotation (node* u);
      void balance();
      void balance_up(AVL* avl);
      static int height_calc(node* v);
      static int max(int a, int b) {return (a > b) ? a : b;}
  };
  /**
   * Constructor. Constructs an empty AVL tree
   */
  AVL ();
  /**
   * Copy constructor
   * @param other
   */
  AVL (const AVL &other);
  /**
   * A constructor that receives a vector of a pairs. Each such pair is an
   * apartment that will inserted to the tree. Insert can be used to insert the
   * apartments a vector of a pairs
   * @param coordinates
   */
  AVL (std::vector<std::pair<double, double>> coordinates);
  ~AVL();
  /**
   *
   * @return the root node of this tree
   */
  node *get_root () const
  {
    return root_;
  }
  /**
   * assignment ctor
   * @param rhs
   * @return
   */
  AVL& operator=(const AVL& rhs);
  /**
   * The function inserts the new apartment into the tree so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void insert (const Apartment &apartment);
  /**
   * The function deletes the apartment from the tree (if it is in that tree) so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void erase (const Apartment &apartment);
  /**
   * The class should support forward iterator. Don't forget to define the
   * iterator traits and all the actions required to support a forward iterator
   * The iterator will move in preorder.
   */
  class ConstIterator;
  class Iterator {
    friend class ConstIterator;
    node *cur;
   public:
    typedef Apartment value_type;
    typedef Apartment& reference;
    typedef Apartment* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    Iterator (node *cur);
    Apartment& operator* ();
    Apartment* operator-> ();
    Iterator &operator++ ();
    Iterator operator++ (int);
    bool operator== (const Iterator &rhs) const;
    bool operator!= (const Iterator &rhs) const;
  };
  class ConstIterator {
    node *cur;
   public:
    typedef const Apartment value_type;
    typedef const Apartment& reference;
    typedef const Apartment* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    ConstIterator (node*cur);
    ConstIterator(const Iterator & it);
    const Apartment *operator-> () const;
    Apartment operator* () const;
    ConstIterator &operator++ ();
    ConstIterator operator++ (int);
    bool operator== (const ConstIterator &rhs) const;
    bool operator!= (const ConstIterator &rhs) const;
  };
  using iterator = Iterator; // same as typedef Iterator iterator;
  using const_iterator = ConstIterator;
  iterator begin ();
  const_iterator begin () const;
  const_iterator cbegin () const;
  iterator end ();
  const_iterator end () const;
  const_iterator cend () const;
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  iterator find (const Apartment &data);
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  const_iterator find (const Apartment &data) const;
  /**
   * Insertion operator, prints the apartment in the tree in preorder traversal.
   * Each apartment will be printed in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param avl tree
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const AVL &avl);
 private:
  void destructor_helper(node* v);
  void transplant (node* u, node* v);
  node* find_node(const Apartment& apt);
  node *root_;
};

#endif //_AVL_H_
