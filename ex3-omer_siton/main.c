//
// Created by omer siton on 07/11/2021.
//
//#define NDEBUG
#include <assert.h>
#include "ex3.h"
#include <stdio.h>

#define LINE "\n------------------------------------------------------\n\n"
#define SHORT_SEP "****************\n"
#define EMPTY_MAT "**EMPTY MAT**\n"
#define NULL_POINTER "Got NULL as pointer to mat\n"

void print_matrix (matrix *mat)
{
  if (mat == NULL)
  {
    printf (NULL_POINTER);
    return;
  }
  if (mat->data == NULL)
  {
    printf (EMPTY_MAT);
    return;
  }
  for (size_t i = 0; i < mat->n_rows; i++)
  {
    for (size_t j = 0; j < mat->n_columns; j++)
    {
      printf ("%f, ", mat->data[i][j]);
    }
    printf ("\n");
  }
}
matrix * fill_matrix(int rows, int cols)
{
  printf ("Create Mat of size: %d x %d\n", rows, cols);

  matrix *mat = create_matrix (rows, cols);
  double num = 1;
  for (size_t i = 0; i < mat->n_rows; i++)
  {
    for (size_t j = 0; j < mat->n_columns; j++)
    {
      mat->data[i][j] = num;
      num++;
    }
  }
  return mat;
}
void print_array(matrix *mat, double * arr)
{
  if (arr){
    printf ("ravel mat: [");
    for (size_t i = 0; i < mat->n_rows * mat->n_columns; i++)
    {
      printf ("%f, ", arr[i]);
    }
    printf ("]\n");
  }
  else printf(NULL_POINTER);
}

void test_create_matrix(){
  // create a regular matrix
  matrix * matrix1 = create_matrix (5, 4);
  print_matrix (matrix1);
  // create a 0,0 matrix
  matrix * matrix2 = create_matrix (0, 0);
  assert(matrix2->data == NULL);
  print_matrix (matrix2);
  // create 1,0 matrix
  matrix * matrix3 = create_matrix (1, 0);
  assert(matrix3->data == NULL);
  print_matrix (matrix3);
  //create 0,1 matrix
  matrix * matrix4 = create_matrix (0, 1);
  assert(matrix4->data == NULL);
  print_matrix (matrix4);
  //// FREE ALL ALLOCATIONS!!!!
  free_matrix (matrix1);
  free_matrix (matrix2);
  free_matrix (matrix3);
  free_matrix (matrix4);
}
void test_Get_By_Index ()
{
  printf (LINE);
  printf ("Check GetIndex: \n");

  matrix *mat = fill_matrix(2, 4);
  print_matrix(mat);
  double *n = get_by_index (mat, 0, 0);
  printf("get_by_index (mat, %d, %d)\n",0,0);
  printf ("got: %f expected: %d -- %s\n", *n, 1, (*n == 1) ? "True": "False");

  n = get_by_index (mat, 0, mat->n_columns - 1);
  printf("get_by_index (mat, %d, %zu)\n",0,mat->n_columns-1);
  printf ("got: %f expected: %zu -- %s\n", *n, mat->n_columns,
          (*n== mat->n_columns)  ? "True" : "False");

  n = get_by_index (mat, mat->n_rows - 1, 0);
  printf("get_by_index (mat, %zu, %d)\n",mat->n_rows - 1,0);
  printf ("got: %f expected: %zu -- %s\n", *n, (
      (mat->n_rows - 1) * (mat->n_columns) + 1),
          (*n == ((mat->n_rows - 1) * (mat->n_columns)+ 1)) ? "True"
          : "False");

  n = get_by_index (mat, mat->n_rows - 1, mat->n_columns - 1);
  printf("get_by_index (mat, %zu, %zu)\n",mat->n_rows - 1,mat->n_columns - 1);

  printf ("got: %f expected: %zu -- %s\n", *n,
          mat->n_rows * mat->n_columns, (*n == mat->n_rows * mat->n_columns)
          ? "True" : "False");
  free_matrix (mat);
}
void test_get_by_index(){
  matrix* mat = fill_matrix (3, 4);
  double * p = get_by_index (mat, 3, 3);
  assert(!p);
  p = get_by_index (mat, 2, 3);
  assert(*p == 12.0);
  assert(p);
  free_matrix (mat);
  test_Get_By_Index();
}
void test_slice ()
{
  printf (LINE);
  printf ("Check slice: \n");

  matrix *mat = fill_matrix(3, 3);
  print_matrix(mat);
  printf (SHORT_SEP);
  printf ("Check slice: \n");

  matrix *e_mat = fill_matrix(0, 3);
  print_matrix (e_mat);
  print_matrix(mat);
  printf (SHORT_SEP);

  int row_start = 0, row_end = 2, col_start = 0, col_end = 2;
  printf ("Slice mat[%d:%d][%d:%d]\n", row_start, row_end, col_start, col_end);
  matrix *s_mat = slice (e_mat, row_start, row_end, col_start, col_end);
  print_matrix(s_mat);
  free_matrix (s_mat);

  row_start = 0, row_end = 2, col_start = 0, col_end = 2;
  printf ("Slice mat[%d:%d][%d:%d]\n", row_start, row_end, col_start, col_end);
  s_mat = slice (mat, row_start, row_end, col_start, col_end);
  print_matrix(s_mat);
  free_matrix (s_mat);

  row_start = 0, row_end = 3, col_start = 0, col_end = 3;
  printf ("Slice mat[%d:%d][%d:%d]\n", row_start, row_end, col_start, col_end);
  s_mat = slice (mat, row_start, row_end, col_start, col_end);
  print_matrix(s_mat);
  free_matrix (s_mat);

  row_start = 2, row_end = 3, col_start = 2, col_end = 3;
  printf ("Slice mat[%d:%d][%d:%d]\n", row_start, row_end, col_start, col_end);
  s_mat = slice (mat, row_start, row_end, col_start, col_end);
  print_matrix(s_mat);
  free_matrix (s_mat);

  row_start = 10, row_end = 3, col_start = 2, col_end = 3;
  printf ("Slice mat[%d:%d][%d:%d]\n", row_start, row_end, col_start, col_end);
  s_mat = slice (mat, row_start, row_end, col_start, col_end);
  print_matrix(s_mat);
  free_matrix (s_mat);

  row_start = 1, row_end = 300, col_start = 0, col_end = 30;
  printf ("Slice mat[%d:%d][%d:%d]\n", row_start, row_end, col_start, col_end);
  s_mat = slice (mat, row_start, row_end, col_start, col_end);
  assert(s_mat->n_rows == 2);
  assert(s_mat->n_columns == 3);
  print_matrix(s_mat);
  free_matrix (s_mat);
  free_matrix (mat);
  free_matrix (e_mat);
}
void test_concatenate_vertically ()
{
  printf (LINE);
  printf ("Check concatenate vertically: \n");

  matrix *top_mat = fill_matrix(1, 3);
  print_matrix(top_mat);

  matrix *b_mat = fill_matrix(2, 3);
  print_matrix(b_mat);

  printf ("concatenate Mats: \n");
  matrix *con_mat = concatenate_vertically (top_mat, b_mat);
  print_matrix(con_mat);
  free_matrix (top_mat);
  free_matrix (b_mat);
  free_matrix (con_mat);

  printf (SHORT_SEP);
  top_mat = fill_matrix(2, 2);
  print_matrix(top_mat);
  b_mat = fill_matrix(3, 3);
  print_matrix(b_mat);

  printf (SHORT_SEP);
  printf ("concatenate Mats: \n");
  con_mat = concatenate_vertically (top_mat, b_mat);
  print_matrix(con_mat);
  free_matrix (top_mat);
  free_matrix (b_mat);

  printf (SHORT_SEP);
  top_mat = fill_matrix(0, 3);
  print_matrix(top_mat);
  b_mat = fill_matrix(3, 3);
  print_matrix(b_mat);

  printf (SHORT_SEP);
  printf ("concatenate Mats: \n");
  con_mat = concatenate_vertically (top_mat, b_mat);
  assert(con_mat->n_rows == 3);
  print_matrix(con_mat);
  free_matrix (top_mat);
  free_matrix (b_mat);
  free_matrix (con_mat);

  printf (SHORT_SEP);
  top_mat = fill_matrix(0, 0);
  print_matrix(top_mat);
  b_mat = fill_matrix(3, 0);
  print_matrix(b_mat);

  printf (SHORT_SEP);
  printf ("concatenate Mats: \n");
  con_mat = concatenate_vertically (top_mat, b_mat);
  print_matrix(con_mat);
  free_matrix (top_mat);
  free_matrix (b_mat);
  free_matrix (con_mat);

}
void test_concatenate_horizontally ()
{
  printf (LINE);
  printf ("Check concatenate horizontally: \n");

  matrix *left_mat = fill_matrix (2, 4);
  print_matrix (left_mat);
  matrix *right_mat = fill_matrix (2, 2);
  print_matrix (right_mat);

  printf ("concatenate Mats: \n");
  matrix *con_mat = concatenate_horizontally (left_mat, right_mat);
  print_matrix (con_mat);
  free_matrix (left_mat);
  free_matrix (right_mat);
  free_matrix (con_mat);

  printf (SHORT_SEP);

  left_mat = fill_matrix (1, 2);
  print_matrix (left_mat);
  right_mat = fill_matrix (1, 3);
  print_matrix (right_mat);

  printf ("concatenate Mats: \n");
  con_mat = concatenate_horizontally (left_mat, right_mat);
  print_matrix (con_mat);
  free_matrix (left_mat);
  free_matrix (right_mat);
  free_matrix (con_mat);

  printf (SHORT_SEP);

  left_mat = fill_matrix (0, 2);
  print_matrix (left_mat);
  right_mat = fill_matrix (1, 3);
  print_matrix (right_mat);

  printf ("concatenate Mats: \n");
  con_mat = concatenate_horizontally (left_mat, right_mat);
  print_matrix (con_mat);
  free_matrix (left_mat);
  free_matrix (right_mat);
  free_matrix (con_mat);

  printf (SHORT_SEP);

  left_mat = fill_matrix (0, 2);
  print_matrix (left_mat);
  right_mat = fill_matrix (0, 3);
  print_matrix (right_mat);

  printf ("concatenate Mats: \n");
  con_mat = concatenate_horizontally (left_mat, right_mat);
  print_matrix (con_mat);
  free_matrix (left_mat);
  free_matrix (right_mat);
  free_matrix (con_mat);

  printf (SHORT_SEP);

  left_mat = fill_matrix (4, 3);
  print_matrix (left_mat);
  right_mat = fill_matrix (2, 2);
  print_matrix (right_mat);

  printf ("concatenate Mats: \n");
  con_mat = concatenate_horizontally (left_mat, right_mat);
  print_matrix (con_mat);
  free_matrix (left_mat);
  free_matrix (right_mat);

}
void test_transpose ()
{
  printf (LINE);
  printf ("Check Transpose: \n");

  matrix *mat = fill_matrix (2, 4);
  print_matrix (mat);
  printf ("after transpose:\n");
  matrix *transpose_mat = transpose (mat);
  print_matrix (transpose_mat);
  free_matrix (mat);
  free_matrix (transpose_mat);

  mat = fill_matrix (1, 4);
  print_matrix (mat);
  printf ("after transpose:\n");
  transpose_mat = transpose (mat);
  print_matrix (transpose_mat);
  free_matrix (mat);
  free_matrix (transpose_mat);

  mat = fill_matrix (2, 2);
  print_matrix (mat);
  printf ("after transpose:\n");
  transpose_mat = transpose (mat);
  print_matrix (transpose_mat);
  free_matrix (mat);
  free_matrix (transpose_mat);

  mat = fill_matrix (0, 2);
  print_matrix (mat);
  printf ("after transpose:\n");
  transpose_mat = transpose (mat);
  print_matrix (transpose_mat);
  free_matrix (mat);
  free_matrix (transpose_mat);
}
void test_ravel ()
{
  printf (LINE);
  printf ("Check ravel: \n");
  matrix *mat = fill_matrix (4, 4);
  print_matrix (mat);
  double *r_array = ravel (mat);
  print_array (mat, r_array);
  free_matrix (mat);
  free (r_array);

  printf(SHORT_SEP);
  mat = fill_matrix (2, 4);
  print_matrix (mat);
  r_array = ravel (mat);
  print_array(mat, r_array);
  free_matrix (mat);
  free (r_array);

  printf(SHORT_SEP);
  mat = fill_matrix (5, 1);
  print_matrix (mat);
  r_array = ravel (mat);
  print_array(mat, r_array);
  free_matrix (mat);
  free (r_array);

  printf(SHORT_SEP);
  mat = fill_matrix (0, 1);
  print_matrix (mat);
  r_array = ravel (mat);
  print_array(mat, r_array);
  free_matrix (mat);
  free (r_array);
}
void test_free ()
{
  printf (LINE);
}

int main(){
//  test_create_matrix();
//  test_get_by_index();
  test_slice();
//  test_concatenate_vertically();
//  test_concatenate_horizontally();
//  test_transpose();
//  test_ravel();
}