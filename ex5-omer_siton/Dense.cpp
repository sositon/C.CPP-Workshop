//
// Created by omer siton on 02/12/2021.
//
#include <iostream>
#include "Matrix.h"
#include "Dense.h"
Dense::Dense (const Matrix &weight, const Matrix &bias,
              ActivationType act_type)
    : weight (weight), bias (bias), act (Activation (act_type))
{
  if (weight.get_rows() != bias.get_rows()){
    std::cerr << DEF_ERR << DEF_SIZE_ERR << std::endl;
    exit (EXIT_FAILURE);
  }
}
Matrix Dense::get_weights () const
{
  return weight;
}
Matrix Dense::get_bias () const
{
  return bias;
}
Activation Dense::get_activation () const
{
  return act;
}
Matrix Dense::operator() (const Matrix &vector) const
{
  return Matrix (act (((weight * vector) + bias)));
}
