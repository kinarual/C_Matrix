#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if ((supp_check_matrix(A)) || (supp_check_matrix(B))) return FAILURE;
  int diff = 1;
  if (supp_compare_size(A, B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((fabs(A->matrix[i][j] - B->matrix[i][j]) > ACCURACY)) diff = 0;
        if (diff == 0) return FAILURE;
      }
    }
  } else {
    return FAILURE;
  }
  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if ((supp_check_matrix(A)) || (supp_check_matrix(B))) {
    s21_remove_matrix(result);
    return ERROR;
  }
  if (supp_compare_size(A, B)) {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      s21_remove_matrix(A);
      s21_remove_matrix(B);
      return ERROR;
    }
  } else {
    return CULC_ERR;
  }
  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if ((supp_check_matrix(A)) || (supp_check_matrix(B))) {
    s21_remove_matrix(result);
    return ERROR;
  }
  if (supp_compare_size(A, B)) {
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      s21_remove_matrix(A);
      s21_remove_matrix(B);
      return ERROR;
    }
  } else {
    return CULC_ERR;
  }
  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (supp_check_matrix(A)) {
    s21_remove_matrix(result);
    return ERROR;
  }
  if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    s21_remove_matrix(A);
    return ERROR;
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->matrix == NULL || B->matrix == NULL) return ERROR;
  if (A->rows <= 0 && B->rows <= 0) return ERROR;
  if (A->columns == B->rows) {
    if (s21_create_matrix(A->rows, B->columns, result) == OK) {
      int temp = 0;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < B->rows; k++) {
            temp += A->matrix[i][k] * B->matrix[k][j];
          }
          result->matrix[i][j] = temp;
          temp = 0;
        }
      }
    } else {
      s21_remove_matrix(A);
      s21_remove_matrix(B);
      return ERROR;
    }
  } else {
    return CULC_ERR;
  }
  return OK;
}
