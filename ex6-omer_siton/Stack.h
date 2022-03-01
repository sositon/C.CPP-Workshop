//
// Created by rotem on 07/10/2021.
//

#ifndef _STACK_H_
#define _STACK_H_
#define DEF_EMPTY_ERR "Can't process - stack is empty."
#include "Apartment.h"
#include <vector>
class Stack {
  std::vector<Apartment> stack_;
 public:
  /**
   * Default constructor, constructs an empty stack
   */
  Stack ();
  /**
   * Constructor that gets vector of pairs, and pushes them as apartments to the stack, when the first pair is pushed first.
   * @param coordinates vector of pairs
   */
  Stack (std::vector<std::pair<double, double>> coordinates);
  /**
   * Pushes an apartment to the top of the stack
   * @param apartment
   */
  void push (const Apartment &apartment);
  /**
   * A method that deletes the item from the top of the stack.
   * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
   */
  void pop ();
 /**
 *A method that returns true if the stack is empty and otherwise false.
 */
  bool empty () const;
  /**
  *A method that returns how many items are inside the stack.
  */
  size_t size () const;
  /**
   * Method that return the item from the top of the stack, but do not remove it from it.
   * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
   * @return refernce to the top most item
   */
  Apartment& top ();
  /**
   * Method that return the item from the top of the stack, but do not remove it from it.
   * Calling this method with an empty stack will throw an out of range exception with an informative message of your choice.
   * @return copy to the top most item
   */
  Apartment top () const;
  /**
   * The stack should support the iterator (at least a forward iterator) so that the item at the top of the stack is the first item.
   */
  typedef std::vector<Apartment>::reverse_iterator iterator;
  typedef std::vector<Apartment>::const_reverse_iterator const_iterator;
  iterator begin ();
  const_iterator begin () const;
  const_iterator cbegin () const;
  iterator end ();
  const_iterator end () const;
  const_iterator cend () const;
};

#endif //_STACK_H_
