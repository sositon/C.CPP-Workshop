//
// Created by omer siton on 02/12/2021.
//
#include <iostream>
#include "Activation.h"
#include <cmath>
Activation::Activation (ActivationType act_type) : act_type (act_type)
{
  if (act_type != RELU && act_type != SOFTMAX){
    std::cerr << DEF_ERR << DEF_ACT_ERR << std::endl;
    exit(EXIT_FAILURE);
  }
}
ActivationType Activation::get_activation_type () const
{
  return act_type;
}
Matrix Activation::operator() (const Matrix &vector) const
{
  Matrix res (vector);
  if (act_type == RELU)
    {
      for (int i = 0; i < (res.get_rows () * res.get_cols ()); ++i)
        {
          if (res[i] < 0)
            res[i] = 0;
        }
    }
  else if (act_type == SOFTMAX)
    {
      float sigma = 0, exp_i;
      for (int i = 0; i < (res.get_rows () * res.get_cols ()); ++i)
        {
          exp_i = std::exp ((res)[i]);
          sigma += exp_i;
          res[i] = exp_i;
        }
      res = (res * (1 / sigma));
    }
  return res;
}
