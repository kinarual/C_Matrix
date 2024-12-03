#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (supp_check_matrix(A)) {
    s21_remove_matrix(result);
    return ERROR;
  }
  if (s21_create_matrix(A->columns, A->rows, result) == OK) {
    for (int j = 0; j < result->rows; j++) {
      for (int i = 0; i < result->columns; i++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else {
    s21_remove_matrix(A);
    return ERROR;
  }
  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  if (supp_check_matrix(A)) return ERROR;
  if (A->rows == A->columns) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      for (int i = 0; i < A->columns; i++) {
        matrix_t tmp = {0};
        if ((s21_create_matrix(A->rows - 1, A->columns - 1, &tmp)) == 0) {
          supp_cut_matrix(A, 0, i, &tmp);
          double tmp_det = 0;
          s21_determinant(&tmp, &tmp_det);
          *result += A->matrix[0][i] * pow(-1, 2 + i) * tmp_det;
          s21_remove_matrix(&tmp);
        } else {
          return ERROR;
        }
      }
    }
  } else {
    return CULC_ERR;
  }
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (supp_check_matrix(A)) {
    s21_remove_matrix(result);
    return ERROR;
  }
  if (A->rows == A->columns) {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      double res = 0;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t temp = {0};
          s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
          supp_cut_matrix(A, i, j, &temp);
          s21_determinant(&temp, &res);
          result->matrix[i][j] = pow((-1), i + j) * res;
          res = 0;
          s21_remove_matrix(&temp);
        }
      }
    } else {
      s21_remove_matrix(A);
      return ERROR;
    }
  } else {
    return CULC_ERR;
  }
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (supp_check_matrix(A)) {
    s21_remove_matrix(result);
    return ERROR;
  }
  double det = 0;
  s21_determinant(A, &det);
  if (A->rows == A->columns && det != 0.0) {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      if (A->rows == 1) {
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      } else {
        matrix_t minor = {0};
        matrix_t trans = {0};
        if ((s21_calc_complements(A, &minor) == OK)) {
          if ((s21_transpose(&minor, &trans) == OK)) {
            s21_remove_matrix(result);
            s21_mult_number(&trans, (1 / det), result);
          }
          s21_remove_matrix(&trans);
        }
        s21_remove_matrix(&minor);
      }
    } else {
      s21_remove_matrix(A);
      return ERROR;
    }
  } else {
    return CULC_ERR;
  }
  return OK;
}
