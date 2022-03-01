// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#define INDEXING(I, J, COLS) ((I*COLS) + J)

#define DEF_ERR "Error: "
#define DEF_SIZE_ERR "invalid Matrix size."
#define DEF_IDX_ERR "invalid index."
#define DEF_ALLOC_ERR "bad allocation."
#define DEF_READ_ERR " only, could be read."
#define PRINT_VAL 0.1
#define DOUBLE_ASTERISK "**"
#define DOUBLE_SPACE "  "
#define ONE_SPACE " "
/**
 * @struct MatrixDims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and in main.cpp.
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

class Matrix {
  matrix_dims dims{};
  int total_size;
  float *data;
 public:
  //// constructors
  Matrix (int rows, int cols); //// ctor
  Matrix (); //// def ctor
  Matrix (const Matrix &other); //// copy ctor
  Matrix &operator= (const Matrix &rhs); //// assign ctor
  ~Matrix (); //// dtor
  //// getters
  int get_rows () const;
  int get_cols () const;
  //// methods
  Matrix &transpose ();
  Matrix &vectorize ();
  void plain_print () const;
  Matrix dot (const Matrix &other) const;
  float norm () const;
  //// operators
  Matrix operator+ (const Matrix &rhs) const;
  Matrix operator* (const Matrix &rhs) const;
  Matrix operator* (float x) const;
  friend Matrix operator* (float x, const Matrix &matrix);
  Matrix &operator+= (const Matrix &rhs);
  float operator() (int i, int j) const;
  float &operator() (int i, int j);
  float operator[] (int i) const;
  float &operator[] (int i);
  friend std::ostream &operator<< (std::ostream &os, const Matrix &matrix);
  friend std::istream &operator>> (std::istream &is, Matrix &matrix);
};

#endif //MATRIX_H
