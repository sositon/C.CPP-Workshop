//
// Created by omer siton on 28/12/2021.
//

#include "MesureTimeHelper.h"
#include "Apartment.h"
#include "Stack.h"
#include "AVL.h"
#include "Find.h"
#include <unordered_set>
#include <chrono>


void stack_time(std::vector<std::pair<double, double>> cords){
  Apartment x (std::pair<double, double>(X_FEEL_BOX, Y_FEEL_BOX));
  auto t1 = std::chrono::high_resolution_clock::now();
  Stack stack(cords);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "insertion time: " << time << std::endl;
  t1 = std::chrono::high_resolution_clock::now();
  find (stack.begin(), stack.end(), x);
  t2 = std::chrono::high_resolution_clock::now();
  time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "find time: " << time << std::endl;
}

void avl_time(const std::vector<std::pair<double, double>>& cords){
  Apartment x (std::pair<double, double>(X_FEEL_BOX, Y_FEEL_BOX));
  auto t1 = std::chrono::high_resolution_clock::now();
  AVL avl(cords);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "insertion time: " << time << std::endl;

  t1 = std::chrono::high_resolution_clock::now();
  avl.find (x);
  t2 = std::chrono::high_resolution_clock::now();
  time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "find time with avl find: " << time << std::endl;

  t1 = std::chrono::high_resolution_clock::now();
  find (avl.begin(), avl.end(), x);
  t2 = std::chrono::high_resolution_clock::now();
  time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "find time with general find: " << time << std::endl;
}

void set_time(const std::vector<std::pair<double, double>>& cords){
  Apartment x (std::pair<double, double>(X_FEEL_BOX, Y_FEEL_BOX));
  std::unordered_set<Apartment, MyHashFunction> a;
  auto t1 = std::chrono::high_resolution_clock::now();
  for (auto val:cords)
    a.insert (val);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "insertion time: " << time << std::endl;

  t1 = std::chrono::high_resolution_clock::now();
  a.find(x);
  t2 = std::chrono::high_resolution_clock::now();
  time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "find time with set find: " << time << std::endl;

  t1 = std::chrono::high_resolution_clock::now();
  find (a.begin(), a.end(), x);
  t2 = std::chrono::high_resolution_clock::now();
  time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  std::cout << "find time with general find: " << time << std::endl;
}
//
//int main(){
//  std::vector<std::pair<double, double>> f100 =
//      xy_from_file ("/Users/omersiton/CLionProjects/ex6-omer_siton/apartments100.txt");
//  std::vector<std::pair<double, double>> f1000 =
//      xy_from_file ("/Users/omersiton/CLionProjects/ex6-omer_siton/apartments1000.txt");
//  std::vector<std::pair<double, double>> f10000 =
//      xy_from_file ("/Users/omersiton/CLionProjects/ex6-omer_siton/apartments10000.txt");
//  stack_time (f100);
//  stack_time (f1000);
//  stack_time (f10000);
//  std::cout << std::endl;
//  avl_time (f100);
//  avl_time (f1000);
//  avl_time (f10000);
//  std::cout << std::endl;
//  set_time (f100);
//  set_time (f1000);
//  set_time (f10000);
//}