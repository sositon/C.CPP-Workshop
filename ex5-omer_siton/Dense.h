//
// Created by yuval on 01-Oct-21.
//

#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense {
  Matrix weight;
  Matrix bias;
  Activation act;
 public:
  Dense (const Matrix &weight, const Matrix &bias, ActivationType act_type);
  Matrix get_weights () const;
  Matrix get_bias () const;
  Activation get_activation () const;
  Matrix operator() (const Matrix &vector) const;
};

#endif //DENSE_H
