//
// Created by omer siton on 19/12/2021.
//
#include <iostream>
#include "Apartment.h"
#include "Stack.h"
#include "AVL.h"



typedef std::pair<double, double> double_pair;
//void print_value(const AVL::node *pn) {
//  std::cout << "(" << pn->get_data().get_x() << ","
//  << pn->get_data().get_y() << ")";
//  std::cout << std::endl;
//}
//
//void printBT(const std::string &prefix, const AVL::node *node, bool isLeft) {
//  if (node != nullptr) {
//    std::cout << prefix;
//
//    std::cout << (isLeft ? "<-├──" : "->└──");
//
//    print_value(node);
//
//    // enter the next tree level - left and right branch
//    printBT(prefix + (isLeft ? "  │   " : "    "), node->get_left(), true);
//    printBT(prefix + (isLeft ? "  │   " : "    "), node->get_right(), false);
//  }
//}
//
//void printBT(const AVL::node *node) {
//  printBT("", node, false);
//}
//
//void print_avl(const AVL &avl) {
//  std::cout << std::endl;
//  printBT(avl.get_root());
//  std::cout << std::endl;
//}


int main(){
  // Apartment
//  std::pair<double, double> p1(10, 11);
//  std::pair<double, double> p2(12, 13);
//  Apartment a(p1);
//  Apartment b(p2);
////  std::cout << a << b;
////  std::cout << (a == b) << std::endl;
////   vector
//  std::vector<std::pair<double, double>> v {p1, p2};
//  // Stack
//  Stack* s1 = new Stack();
//  s1->push (a);
//  s1->push (b);
////  for(auto& it:*s1)
////  {
////    std::cout << it ;
////  }
//  // AVL
//  AVL avl(v);
//  print_avl (avl);
//  std::cout << avl;

  return 0;
}