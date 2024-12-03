#include "s21_matrix.h"

int supp_compare_size(matrix_t *A, matrix_t *B) {
  int comp_result = 0;
  if (A->rows == B->rows && A->columns == B->columns) comp_result = 1;
  return comp_result;
}

int supp_check_matrix(matrix_t *A) {
  int flag = 0;
  if ((A->matrix == NULL) || (A->rows <= 0) || (A->columns <= 0)) flag = 1;
  return flag;
}

void supp_cut_matrix(matrix_t *A, int init_i, int init_j, matrix_t *result) {
  int cut_i = 0;
  int cut_j = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i != init_i) {
      for (int j = 0; j < A->columns; j++) {
        if (j != init_j) {
          result->matrix[cut_i][cut_j] = A->matrix[i][j];
          cut_j++;
        }
      }
      cut_j = 0;
      cut_i++;
    }
  }
}