//
// Created by omer siton on 02/12/2021.
//
#include "Matrix.h"
#include "Activation.h"
#include "Dense.h"
#include <iostream>
void fill_mat(Matrix& mat){
  float k = 1;
  for (int i = 0; i < mat.get_rows (); ++i)
  {
    for (int j = 0; j < mat.get_cols (); ++j)
      mat(i,j) = k++;
  }
}
int main(){
  Matrix m1 = Matrix(3, 3);
  fill_mat (m1);
  Matrix m2 = m1;
  m2.transpose();
  std::cout << "m1: " << std::endl;
  m1.plain_print();
  std::cout << "m2: " << std::endl;
  m2.plain_print();
  std::cout << "m1*m2: " << std::endl;
  (m1*m2).plain_print();
  std::cout << "m1.dot(m2): " << std::endl;
  (m1.dot (m2).plain_print());
  std::cout << "m1.norm(): " << m1.norm() <<std::endl;
}