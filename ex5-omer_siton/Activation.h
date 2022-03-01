//Activation.h

#ifndef ACTIVATION_H
#define ACTIVATION_H

#define DEF_ACT_ERR "invalid activation type."
#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType {
    RELU,
    SOFTMAX
};

class Activation {
  ActivationType act_type;
 public:
  explicit Activation (ActivationType act_type);
  ActivationType get_activation_type () const;
  Matrix operator() (const Matrix &vector) const;
};

#endif //ACTIVATION_H
