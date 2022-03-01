//
// Created by omer siton on 02/12/2021.
//
#include <iostream>
#include "Matrix.h"
#include <cmath>
using namespace std;
//// ctor
Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
    {
      cerr << DEF_ERR << DEF_SIZE_ERR << endl;
      exit (EXIT_FAILURE);
    }
  dims.rows = rows;
  dims.cols = cols;
  total_size = rows * cols;
  data = new (nothrow) float[total_size];
  if (data == nullptr)
    {
      cerr << DEF_ERR << DEF_ALLOC_ERR << endl;
      exit (EXIT_FAILURE);
    }
  for (int k = 0; k < total_size; ++k)
    data[k] = 0;
}
Matrix::Matrix ()
{
  dims.cols = dims.rows = 1;
  total_size = dims.rows * dims.cols;
  data = new (nothrow) float[total_size];
  if (data == nullptr)
    {
      cerr << DEF_ERR << DEF_ALLOC_ERR << endl;
      exit (EXIT_FAILURE);
    }
  data[0] = 0;
}
Matrix &Matrix::operator= (const Matrix &rhs)
{
  if (this == &rhs)
    return *this;
  if (total_size == rhs.total_size)
    for (int i = 0; i < rhs.total_size; ++i)
      data[i] = rhs.data[i];
  else
    {
      delete[] data;
      data = new (nothrow) float[rhs.total_size];
      if (data == nullptr)
        {
          cerr << DEF_ERR << DEF_ALLOC_ERR << endl;
          exit (EXIT_FAILURE);
        }
      for (int i = 0; i < rhs.total_size; ++i)
        data[i] = rhs.data[i];
    }
  dims.rows = rhs.dims.rows;
  dims.cols = rhs.dims.cols;
  total_size = rhs.total_size;
  return *this;
}
Matrix::Matrix (const Matrix &other)
{
  dims = other.dims;
  total_size = other.total_size;
  data = new (nothrow) float[total_size];
  if (data == nullptr)
    {
      cerr << DEF_ERR << DEF_ALLOC_ERR << endl;
      exit (EXIT_FAILURE);
    }
  for (int i = 0; i < total_size; ++i)
    data[i] = other.data[i];
}
Matrix::~Matrix ()
{
  delete[] data;
}
//// getters
int Matrix::get_rows () const
{
  return dims.rows;
}
int Matrix::get_cols () const
{
  return dims.cols;
}
//// methods
Matrix &Matrix::transpose ()
{
  float *transpose_data = new (nothrow) float[total_size];
  if (transpose_data == nullptr)
    {
      cerr << DEF_ERR << DEF_ALLOC_ERR << endl;
      exit (EXIT_FAILURE);
    }
  int rows = dims.rows, cols = dims.cols;
  for (int i = 0; i < cols; ++i)
    {
      for (int j = 0; j < rows; ++j)
        transpose_data[INDEXING(i, j, rows)] = data[INDEXING(j, i, cols)];
    }
  delete[] data;
  data = transpose_data;
  dims.rows = cols;
  dims.cols = rows;
  return *this;
}
Matrix &Matrix::vectorize ()
{
  if (dims.cols == 1)
    return *this;
  dims.cols = 1;
  dims.rows = total_size;
  return *this;
}
void Matrix::plain_print () const
{
  for (int i = 0; i < dims.rows; ++i)
    {
      for (int j = 0; j < dims.cols; ++j)
        cout << data[INDEXING(i, j, dims.cols)] << ONE_SPACE;
      cout << endl;
    }
}
Matrix Matrix::dot (const Matrix &other) const
{
  if (dims.cols != other.dims.cols || dims.rows != other.dims.rows)
    {
      cerr << DEF_ERR << DEF_SIZE_ERR << endl;
      exit (EXIT_FAILURE);
    }
  Matrix res (*this);
  for (int i = 0; i < res.total_size; ++i)
    res.data[i] = data[i] * other.data[i];
  return res;
}
float Matrix::norm () const
{
  float res = 0;
  for (int i = 0; i < total_size; ++i)
    res += (data[i] * data[i]);
  return std::sqrt (res);
}
//// operators
Matrix Matrix::operator+ (const Matrix &rhs) const
{
  if (dims.cols != rhs.dims.cols || dims.rows != rhs.dims.rows)
    {
      cerr << DEF_ERR << DEF_SIZE_ERR << endl;
      exit (EXIT_FAILURE);
    }
  Matrix res (*this);
  for (int i = 0; i < total_size; ++i)
    res.data[i] += rhs.data[i];
  return res;
}
Matrix Matrix::operator* (const Matrix &rhs) const
{
  if (dims.cols != rhs.dims.rows)
    {
      cerr << DEF_ERR << DEF_SIZE_ERR << endl;
      exit (EXIT_FAILURE);
    }
  Matrix res (dims.rows, rhs.dims.cols);
  for (int i = 0; i < res.dims.rows; ++i)
    {
      for (int j = 0; j < res.dims.cols; ++j)
        {
          for (int k = 0; k < dims.cols; ++k)
            {
              res.data[INDEXING(i, j, res.dims.cols)] +=
                  data[INDEXING(i, k, dims.cols)]
                  * rhs.data[INDEXING(k, j, rhs.dims.cols)];
            }
        }
    }
  return res;
}
Matrix Matrix::operator* (float x) const
{
  Matrix res (*this);
  for (int i = 0; i < total_size; ++i)
    res.data[i] = (res.data[i]) * x;
  return res;
}
Matrix operator* (float x, const Matrix &matrix)
{
  return matrix * x;
}
Matrix &Matrix::operator+= (const Matrix &rhs)
{
  if (dims.cols != rhs.dims.cols || dims.rows != rhs.dims.rows)
    {
      cerr << DEF_ERR << DEF_SIZE_ERR << endl;
      exit (EXIT_FAILURE);
    }
  for (int i = 0; i < total_size; ++i)
    data[i] += rhs.data[i];
  return *this;
}
float &Matrix::operator() (int i, int j)
{
  if (i < 0 || j < 0 || i >= dims.rows || j >= dims.cols)
    {
      cerr << DEF_ERR << DEF_IDX_ERR << endl;
      exit (EXIT_FAILURE);
    }
  return data[INDEXING(i, j, dims.cols)];
}
float Matrix::operator() (int i, int j) const
{
  if (i < 0 || j < 0 || i >= dims.rows || j >= dims.cols)
    {
      cerr << DEF_ERR << DEF_IDX_ERR << endl;
      exit (EXIT_FAILURE);
    }
  return data[INDEXING(i, j, dims.cols)];
}
float &Matrix::operator[] (int i)
{
  if (i < 0 || i >= total_size)
    {
      cerr << DEF_ERR << DEF_IDX_ERR << endl;
      exit (EXIT_FAILURE);
    }
  return data[i];
}
float Matrix::operator[] (int i) const
{
  if (i < 0 || i >= total_size)
    {
      cerr << DEF_ERR << DEF_IDX_ERR << endl;
      exit (EXIT_FAILURE);
    }
  return data[i];
}
ostream &operator<< (ostream &os, const Matrix &matrix)
{
  for (int i = 0; i < matrix.dims.rows; ++i)
    {
      for (int j = 0; j < matrix.dims.cols; ++j)
        {
          if (matrix (i, j) > PRINT_VAL)
            os << DOUBLE_ASTERISK;
          else
            os << DOUBLE_SPACE;
        }
      os << endl;
    }
  return os;
}
std::istream &operator>> (istream &is, Matrix &matrix)
{
  if (is.good())
    is.read ((char *) matrix.data,
             (streamsize) (matrix.total_size * sizeof (float)));
  if (is.good ())
    return is;
  cerr << DEF_ERR << is.gcount () << DEF_READ_ERR;
  exit (EXIT_FAILURE);
}


