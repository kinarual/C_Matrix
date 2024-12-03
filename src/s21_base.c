#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows >= 1 && columns >= 1) {
    if ((result->matrix = (double **)calloc(rows, sizeof(double *))) != NULL) {
      result->rows = rows;
      result->columns = columns;
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = (double *)calloc(result->columns, sizeof(double));
      }
      return OK;
    } else {
      return ERROR;
    }
  } else {
    return ERROR;
  }
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
}