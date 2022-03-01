//
// Created by omer siton on 06/11/2021.
//
# include "ex3.h"

#define ALLOC_ERR "allocation failure"
#define DEF_ERR "ERROR: %s(), %s\n"
#define RANGE_ERR "index out of range\n"
#define EMPTY 0
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/**
 * create a new matrix_s on the heap.
 * @param n_rows number of rows in the new matrix_s.
 * @param n_columns number of columns in the new matrix_s.
 * @return A pointer to the new matrix_s struct.
 */
matrix *create_matrix (size_t n_rows, size_t n_columns)
{
  matrix *new_matrix = malloc (sizeof (*new_matrix));
  if (new_matrix)
    {
      double **data = calloc (n_rows, sizeof (double *));
      if (data)
        {
          if (n_rows > 0 && n_columns > 0)
            {
              for (int i = 0; i < (int) n_rows; ++i)
                {
                  data[i] = calloc (n_columns, sizeof (double));
                  if (data[i] == NULL) // Alloc Fail
                    {
                      fprintf (stderr, DEF_ERR, __func__, ALLOC_ERR);
                      for (int j = 0; j < i; ++j)
                        {
                          free (data[j]);
                        }
                      free (data);
                      free (new_matrix);
                      new_matrix = NULL;
                      return new_matrix;
                    }
                  new_matrix->data = data;
                  new_matrix->n_rows = n_rows;
                  new_matrix->n_columns = n_columns;
                }
            }
          else // n_rows = 0 or n_cols = 0
            {
              new_matrix->data = NULL;
              new_matrix->n_rows = EMPTY;
              new_matrix->n_columns = EMPTY;
            }
        }
      else // Alloc Fail
        {
          fprintf (stderr, DEF_ERR, __func__, ALLOC_ERR);
          free (new_matrix);
          new_matrix = NULL;
          return new_matrix;
        }
    }
  else fprintf (stderr, DEF_ERR, __func__, ALLOC_ERR);
  return new_matrix;
}
/**
 * Get value based on index.
 * @param matrix
 * @param row_index
 * @param col_index
 * @return matrix_s[row_index, col_index],
 * NULL if the index is out of range.
 */
double *get_by_index (matrix *mat, size_t row_index, size_t col_index)
{
  // check row and col
  double *res = NULL;
  if (row_index >= (mat->n_rows) || col_index >= (mat->n_columns))
    {
      fprintf (stderr, DEF_ERR, __func__, RANGE_ERR);
      return res;
    }
  res = &(mat->data[row_index][col_index]);
  return res;
}

/**
 * put the sliced data from matrix to a new matrix based on indexing
 * @param matrix
 * @param row_range
 * @param col_range
 * @return matrix[row_s:row_e)[col_s:col_e)
 */
matrix *slice (matrix *mat, size_t row_start,
               size_t row_end, size_t col_start, size_t col_end)
{
  if (row_start >= row_end || col_start >= col_end)
    {
      return create_matrix (EMPTY, EMPTY);
    }
  size_t n_rows = MIN((row_end - row_start), mat->n_rows - row_start);
  size_t n_columns = MIN((col_end - col_start), mat->n_columns - col_start);
  matrix *new_mat = create_matrix (n_rows, n_columns);
  double *p;
  if (new_mat)
    {
      if (mat->data && new_mat->data)
        {
          for (size_t j = 0, i = row_start; j < n_rows; ++i, ++j)
            {
              p = get_by_index (mat, i, col_start);
              memcpy(new_mat->data[j], p,
                     n_columns * sizeof (double));
            }
        }
      return new_mat;
    }
  return NULL;
}
/**
 * connects two matrices vertically - top and bottom
 * @param top
 * @param bottom
 * @return new matrix if size is matching else empty matrix.
 */
matrix *concatenate_vertically (matrix *top, matrix *bottom)
{
  size_t k1 = top->n_columns, k2 = bottom->n_columns;
  size_t n_rows = top->n_rows + bottom->n_rows;
  if (k1 != k2)
    {
      fprintf (stderr, DEF_ERR, __func__, RANGE_ERR);
      return NULL;
    }
  matrix *new_mat = create_matrix (n_rows, k1);
  if (new_mat)
    {
      if (new_mat->data && top->data && bottom->data)
        {
          for (int i = 0; i < (int) n_rows; ++i)
            {
              if (i < (int) top->n_rows)
                {
                  memcpy(new_mat->data[i], top->data[i], k1 * sizeof (double));
                }
              else
                memcpy(new_mat->data[i], bottom->data[i - top->n_rows],
                       k2 * sizeof (double));
            }
        }
      return new_mat;
    }
  return NULL;
}

/**
 *connects two matrices horizontally - left and right
 * @param left
 * @param right
 * @retur new matrix if size is matching else empty matrix.
 */
matrix *concatenate_horizontally (matrix *left, matrix *right)
{
  size_t k1 = left->n_rows, k2 = right->n_rows;
  size_t n_columns = left->n_columns + right->n_columns;
  if (k1 != k2)
    {
      fprintf (stderr, DEF_ERR, __func__, RANGE_ERR);
      return NULL;
    }
  matrix *new_mat = create_matrix (k1, n_columns);
  double *p;
  if (new_mat)
    {
      if (new_mat->data && left->data && right->data)
        {
          for (int i = 0; i < (int) k1; ++i)
            {
              memcpy(new_mat->data[i], left->data[i],
                     left->n_columns * sizeof (double));
              p = get_by_index (new_mat, i, left->n_columns);
              memcpy(p, right->data[i], right->n_columns * sizeof (double));
            }
        }
      return new_mat;
    }
  return NULL;
}

/**
 *
 * @param matrix
 * @return the transposed matrix
 */
matrix *transpose (matrix *mat)
{
  matrix *new_mat = create_matrix (mat->n_columns, mat->n_rows);
  if (new_mat)
    {
      if (new_mat->data)
        {
          for (int i = 0; i < (int) new_mat->n_rows; ++i)
            {
              for (int j = 0; j < (int) new_mat->n_columns; ++j)
                {
                  new_mat->data[i][j] = mat->data[j][i];
                }
            }
        }
      return new_mat;
    }
  return NULL;
}

/**
 *
 * @param matrix
 * @return 1 dimension matrix
 */
double *ravel (matrix *mat)
{
  double *res = malloc (mat->n_rows * mat->n_columns * sizeof (double));
  if (res && mat->data)
    {
      for (int i = 0; i < (int) mat->n_rows; ++i)
        {
          memcpy(res + (i * mat->n_columns), mat->data[i],
                 mat->n_columns * sizeof (double));
        }
      return res;
    }
  free (res);
  res = NULL;
  return res;
}

/** free all heap allocations
 * of a given matrix
 * @param mat
 */
void free_matrix (matrix *mat)
{
  if (mat)
    {
      if (mat->data)
        {
          for (int i = 0; i < (int) (mat->n_rows); ++i)
            {
              free (mat->data[i]);
              mat->data[i] = NULL;
            }
          free (mat->data);
          mat->data = NULL;
        }
      free (mat);
    }
}