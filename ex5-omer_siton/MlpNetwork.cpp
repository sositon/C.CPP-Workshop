//
// Created by omer siton on 02/12/2021.
//
#include <iostream>
#include "MlpNetwork.h"
MlpNetwork::MlpNetwork (Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
{
  for (int i = 0; i < MLP_SIZE; ++i)
    {
      if (weights_dims[i].rows != weights[i].get_rows() ||
          weights_dims[i].cols != weights[i].get_cols()){
        std::cerr << DEF_ERR << DEF_MISMATCHED_ERR << std::endl;
        exit(EXIT_FAILURE);
      }
      if (bias_dims[i].rows != biases[i].get_rows() ||
      bias_dims[i].cols != biases[i].get_cols()){
        std::cerr << DEF_ERR << DEF_MISMATCHED_ERR << std::endl;
        exit(EXIT_FAILURE);
      }
      this->weights[i] = weights[i];
      this->biases[i] = biases[i];
    }
}
digit MlpNetwork::operator() (const Matrix &img) const
{
  Dense layer_1 = Dense (weights[0], biases[0], RELU);
  Dense layer_2 = Dense (weights[1], biases[1], RELU);
  Dense layer_3 = Dense (weights[2], biases[2], RELU);
  Dense layer_4 = Dense (weights[3], biases[3], SOFTMAX);
  Matrix r1 = layer_1 (img);
  Matrix r2 = layer_2 (r1);
  Matrix r3 = layer_3 (r2);
  Matrix r4 = layer_4 (r3);
  float max_prob = 0;
  unsigned int idx = 0;
  for (int i = 0; i < r4.get_rows (); ++i)
    {
      if (r4[i] > max_prob)
        {
          max_prob = r4[i];
          idx = i;
        }
    }
  return digit{idx, max_prob};
}
