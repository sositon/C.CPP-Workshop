//
// Created by omer siton on 19/12/2021.
//

#include "AVL.h"

/// Ctor!
AVL::AVL () : root_ (nullptr)
{}
AVL::AVL (const AVL &other) : root_(nullptr)
{
  if (other.root_)
    root_ = new node(*other.root_);
}
AVL::AVL (std::vector<std::pair<double, double>> coordinates) : root_(nullptr)
{
//  auto it = coordinates.begin();
//  for (int i = 0; it+i != coordinates.end() ; ++i)
//      insert (Apartment(*it));
  for (const auto &pair:coordinates)
    insert (Apartment (pair));
}
AVL& AVL::operator= (const AVL &rhs)
{
  if (this == &rhs)
      return *this;
  root_ = new node(*rhs.root_);
  return *this;
}
AVL::~AVL ()
{
  if (root_)
    destructor_helper (root_);
}
/// Methods
void AVL::insert (const Apartment &apartment)
{
  if (!root_){
    root_ = new node(apartment,nullptr, nullptr, nullptr);
    return;
  }
  node* cur = root_;
  node* cur_parent = nullptr;
  while (cur)
    {
      cur_parent = cur;
      if (apartment < cur->data_)
      {
        if (cur->left_)
          cur = cur->left_;
        else
          break;
      }
      else
        if (cur->right_)
          cur = cur->right_;
        else
          break;
    }
  cur = new node(apartment, nullptr, nullptr, cur_parent);
  if (cur_parent)
  {
    (apartment < cur_parent->data_) ? cur_parent->left_ = cur
                                    : cur_parent->right_ = cur;
    cur->balance_up(this);
  }
}
void AVL::erase (const Apartment &apartment)
{
  node* z = find_node (apartment);
  if (!z)
    return;
  if (z->left_ == nullptr)
  {
    transplant (z, z->right_);
    if (z->right_)
      z->right_->balance_up (this);
    else if (z->parent_)
      z->parent_->balance_up (this);
  }

  else if (z->right_ == nullptr)
  {
    transplant (z, z->left_);
    if (z->left_)
      z->left_->balance_up (this);
    else if (z->parent_)
      z->parent_->balance_up (this);
  }
  else
  {
    node * y = z->right_;
    while(y->left_)
      y = y->left_;
    if (y->parent_ != z)
    {
      transplant (y, y->right_);
      y->right_ = z->right_;
      y->right_->parent_ = y;
    }
    transplant (z, y);
    y->left_ = z->left_;
    y->left_->parent_ = y;
    y->balance_up (this);
  }
  delete z;
}
AVL::iterator AVL::find (const Apartment &data)
{
//  return {find_node (data)};
  for (auto it = begin(); it != end(); ++it)
  {
    if (*it == data)
      return it;
  }
  return end();
}
AVL::const_iterator AVL::find (const Apartment &data) const
{
  for (auto it = cbegin(); it != cend(); ++it)
  {
    if (*it == data)
      return it;
  }
  return cend();
}
std::ostream &operator<< (std::ostream &os, const AVL &avl)
{
  for (auto i : avl)
    os << i;
  return os;
}
/// Iterator
AVL::Iterator::Iterator (AVL::node *cur):cur(cur)
{}
Apartment &AVL::Iterator::operator* ()
{
  return cur->data_;
}
Apartment *AVL::Iterator::operator-> ()
{
  return &(cur->data_);
}
AVL::Iterator &AVL::Iterator::operator++ ()
{
  if (cur->left_){
    cur = cur->left_;
  }
  else if (cur->right_)
    cur = cur->right_;
  else
  {
    node* y = cur->parent_;
    while(y && y->data_ < cur->data_)
      y = y->parent_;
    y ? cur = y->right_ : cur = y;
  }
  return *this;
}
AVL::Iterator AVL::Iterator::operator++ (int)
{
  Iterator it = *this;
  if (cur->left_){
    cur = cur->left_;
  }
  else if (cur->right_)
    cur = cur->right_;
  else{
    node* y = cur->parent_;
    while(y && y->data_ < cur->data_)
      y = y->parent_;
    y ? cur = y->right_ : cur = y;
  }
  return it;
}
bool AVL::Iterator::operator== (const AVL::Iterator &rhs) const
{
  return cur == rhs.cur;
}
bool AVL::Iterator::operator!= (const AVL::Iterator &rhs) const
{
  return !(rhs == *this);
}
/// ConstIterator
AVL::ConstIterator::ConstIterator (AVL::node *cur): cur(cur)
{}
AVL::ConstIterator::ConstIterator (const AVL::Iterator &it): cur(it.cur)
{}
const Apartment *AVL::ConstIterator::operator-> () const
{
  return &(cur->data_);
}
Apartment AVL::ConstIterator::operator* () const
{
  return cur->data_;
}
AVL::ConstIterator &AVL::ConstIterator::operator++ ()
{
  if (cur->left_){
    cur = cur->left_;
  }
  else if (cur->right_)
    cur = cur->right_;
  else{
    node* y = cur->parent_;
    while(y && y->data_ < cur->data_)
      y = y->parent_;
    y ? cur = y->right_ : cur = y;
  }
  return *this;
}
AVL::ConstIterator AVL::ConstIterator::operator++ (int)
{
  ConstIterator it = *this;
  if (cur->left_){
    cur = cur->left_;
  }
  else if (cur->right_)
    cur = cur->right_;
  else{
    node* y = cur->parent_;
    while(y && y->data_ < cur->data_)
      y = y->parent_;
    y ? cur = y->right_ : cur = y;
  }
  return it;
}
bool AVL::ConstIterator::operator== (const AVL::ConstIterator &rhs) const
{
  return cur == rhs.cur;
}
bool AVL::ConstIterator::operator!= (const AVL::ConstIterator &rhs) const
{
  return !(rhs == *this);
}
/// node
AVL::node::node (Apartment data, AVL::node *left, AVL::node *right, AVL::node *parent)
: data_ (data), left_ (left), right_ (right), parent_(parent), h_(0)
{
  if (left_ && right_)
    h_ = std::max(left_->h_, right_->h_);
  else if (left_ || right_)
    left_ ? h_ = left_->h_ : h_ = right_->h_;
}
AVL::node::node (const AVL::node &other): data_ (other.data_),
left_(nullptr), right_(nullptr), parent_(nullptr), h_(other.h_)
{
  if (other.left_)
  {
    left_ = new node(*other.left_);
    left_->parent_ = this;
  }
  if (other.right_)
  {
    right_ = new node(*other.right_);
    right_->parent_ = this;
  }
}
void AVL::node::height_update ()
{
  if (left_ || right_)
    h_ = height_calc (this);
  else
    h_ = 0;
}
void AVL::node::left_rotation (AVL::node *u)
{
  u->parent_ = parent_;
  if (parent_)
    parent_->left_ == this ? parent_->left_ = u : parent_->right_ = u;
  parent_ = u;
  right_ = u->left_;
  u->left_ = this;
  height_update();
  u->height_update();
}
void AVL::node::right_rotation (AVL::node *u)
{
  u->parent_ = parent_;
  if (parent_)
    parent_->left_ == this ? parent_->left_ = u : parent_->right_ = u;
  parent_ = u;
  left_ = u->right_;
  u->right_ = this;
  height_update();
  u->height_update();
}
void AVL::node::balance ()
{
  if (get_bf()==2)
  {
    /// LR
    if (left_->get_bf() == -1)
    {
      left_->left_rotation(left_->right_);
      right_rotation(left_);
    }
    /// LL
    else
      right_rotation(left_);
  }
  if (get_bf() == -2)
  {
    /// RL
    if (right_->get_bf() == 1)
    {
      right_->right_rotation(right_->left_);
      left_rotation(right_);
    }
    /// RR
    else
      left_rotation(right_);
  }
}
void AVL::node::balance_up (AVL *avl)
{
  height_update();
  if (get_bf() <= -2 || get_bf() >= 2)
    balance();
  if (parent_)
    parent_->balance_up(avl);
  else
    avl->root_ = this;
}
int AVL::node::height_calc (AVL::node *v)
{
  if (!v)
    return -1;
  return max(height_calc (v->left_), height_calc (v->right_)) + 1;
}
/// Iterators Methods
AVL::iterator AVL::begin ()
{
  return {root_};
}
AVL::const_iterator AVL::begin () const
{
  return {root_};
}
AVL::const_iterator AVL::cbegin () const
{
  return {root_};
}
AVL::iterator AVL::end ()
{
  return {nullptr};
}
AVL::const_iterator AVL::end () const
{
  return {nullptr};
}
AVL::const_iterator AVL::cend () const
{
  return {nullptr};
}
/// Private Methods
void AVL::transplant (AVL::node *u, AVL::node *v)
{
  if (u->parent_ == nullptr)
    root_ = v;
  else
    (u == u->parent_->left_) ? u->parent_->left_ = v
                              : u->parent_->right_ = v;
  if (v != nullptr)
    v->parent_ = u->parent_;
}
AVL::node* AVL::find_node (const Apartment &apt)
{
  node* cur = root_;
  while(cur != nullptr && (cur->data_ < apt || cur->data_ > apt)){
    apt < cur->data_  ? cur = cur->left_ : cur = cur->right_;
  }
  return cur;
}
void AVL::destructor_helper (AVL::node *v)
{
  if (v->left_)
    destructor_helper (v->left_);
  if (v->right_)
    destructor_helper (v->right_);
  delete v;
}

