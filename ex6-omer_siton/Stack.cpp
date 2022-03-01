//
// Created by omer siton on 19/12/2021.
//

#include "Stack.h"
/// Ctor
Stack::Stack (): stack_(std::vector<Apartment>())
{}
Stack::Stack (std::vector<std::pair<double, double>> coordinates)
{
  for(const auto& pair:coordinates)
    push(Apartment(pair));
}
/// Methods
void Stack::push (const Apartment &apartment)
{
  stack_.push_back (apartment);
}
void Stack::pop ()
{
  if (this->empty())
    throw std::out_of_range (DEF_EMPTY_ERR);
  stack_.pop_back();
}
bool Stack::empty () const
{
  return stack_.empty();
}
size_t Stack::size () const
{
  return stack_.size();
}
Apartment &Stack::top ()
{
  if (this->empty())
    throw std::out_of_range (DEF_EMPTY_ERR);
  return stack_.back();
}
Apartment Stack::top () const
{
  if (this->empty())
    throw std::out_of_range (DEF_EMPTY_ERR);
  return stack_.back();
}
/// Iterators
Stack::iterator Stack::begin ()
{
  return stack_.rbegin();
}
Stack::const_iterator Stack::begin () const
{
  return stack_.crbegin();
}
Stack::const_iterator Stack::cbegin () const
{
  return stack_.crbegin();
}
Stack::iterator Stack::end ()
{
  return stack_.rend();
}
Stack::const_iterator Stack::end () const
{
  return stack_.crend();
}
Stack::const_iterator Stack::cend () const
{
 return stack_.crend();
}

