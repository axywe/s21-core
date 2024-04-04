#include "s21_matrix.h"

// Function to create a matrix
int s21_create_matrix(int rows, int columns, matrix_t *A) {
  if (rows <= 0 || columns <= 0) {
    return INVALID_MATRIX;
  }
  A->rows = rows;
  A->columns = columns;
  A->matrix = malloc(rows * sizeof(double *));
  if (A->matrix == NULL) {
    return CALCULATION_ERROR;
  }
  for (int i = 0; i < rows; i++) {
    A->matrix[i] = malloc(columns * sizeof(double));
    if (A->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(A->matrix[j]);
      }
      free(A->matrix);
      return CALCULATION_ERROR;
    }
  }
  return OK;
}

// Function to remove a matrix
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
        A->matrix[i] = NULL;
      }
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  A->rows = 0;
  A->columns = 0;
}

// Function to compare two matrices
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A->rows != B->rows || A->columns != B->columns || A->matrix == NULL ||
      B->matrix == NULL || A->rows == 0 || A->columns == 0 || B->rows == 0 ||
      B->columns == 0) {
    return FAILURE;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}

// Function to add two matrices
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->matrix == NULL || B->matrix == NULL) {
    return INVALID_MATRIX;
  }
  if (A->rows != B->rows || A->columns != B->columns || A->rows == 0 ||
      A->columns == 0 || B->rows == 0 || B->columns == 0) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return OK;
}

// Function to subtract two matrices
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->matrix == NULL || B->matrix == NULL) {
    return INVALID_MATRIX;
  }
  if (A->rows != B->rows || A->columns != B->columns || A->rows == 0 ||
      A->columns == 0 || B->rows == 0 || B->columns == 0) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}

// Function to multiply a matrix by a number
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A->matrix == NULL) {
    return INVALID_MATRIX;
  }
  if (A->rows == 0 || A->columns == 0) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}

// Function to multiply two matrices
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->matrix == NULL || B->matrix == NULL) {
    return INVALID_MATRIX;
  }
  if (A->columns != B->rows || A->rows == 0 || A->columns == 0 ||
      B->rows == 0 || B->columns == 0) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->rows, B->columns, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}

// Function to transpose a matrix
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A->matrix == NULL) {
    return INVALID_MATRIX;
  }
  if (A->rows == 0 || A->columns == 0) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}

// Function to calculate the determinant of a matrix
int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || A->matrix == NULL) {
    return INVALID_MATRIX;
  }
  if (A->columns != A->rows || A->columns <= 0 || A->rows <= 0) {
    return CALCULATION_ERROR;
  }
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] == NULL) {
      return INVALID_MATRIX;
    }
  }

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }

  double det = 0;
  if (A->rows == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->columns; i++) {
      matrix_t sub_mat;
      int sign = (i % 2 == 0) ? 1 : -1;
      int new_rows = A->rows - 1;
      int new_cols = A->columns - 1;

      s21_create_matrix(new_rows, new_cols, &sub_mat);

      for (int m = 1, sub_i = 0; m < A->rows; m++, sub_i++) {
        for (int n = 0, sub_j = 0; n < A->columns; n++) {
          if (n == i) continue;
          sub_mat.matrix[sub_i][sub_j++] = A->matrix[m][n];
        }
      }

      double sub_det;
      s21_determinant(&sub_mat, &sub_det);
      det += sign * A->matrix[0][i] * sub_det;
      s21_remove_matrix(&sub_mat);
    }
  }

  *result = det;
  return OK;
}

// Function to calculate the complements of a matrix
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A->matrix == NULL) {
    return INVALID_MATRIX;
  }
  double det = 0;
  if (A->rows == 0 || A->columns == 0 || A->rows != A->columns ||
      (s21_determinant(A, &det) != OK || fabs(det) < EPSILON)) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->rows, A->columns, result);
  matrix_t temp = {0};
  s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      int k = 0;
      for (int l = 0; l < A->rows; l++) {
        if (l == i) {
          continue;
        }
        int m = 0;
        for (int n = 0; n < A->rows; n++) {
          if (n == j) {
            continue;
          }
          temp.matrix[k][m] = A->matrix[l][n];
          m++;
        }
        k++;
      }
      double res = 0;
      s21_determinant(&temp, &res);
      if ((i + j) % 2 == 0) {
        result->matrix[i][j] = res;
      } else {
        result->matrix[i][j] = -res;
      }
    }
  }
  s21_remove_matrix(&temp);
  return OK;
}

// Function to calculate the inverse of a matrix
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || A->columns <= 0 || A->rows <= 0) {
    return INVALID_MATRIX;
  }

  if (A->columns != A->rows) {
    return CALCULATION_ERROR;
  }
  double det = 0;
  s21_determinant(A, &det);
  if (det == 0) return CALCULATION_ERROR;
  matrix_t complements;
  s21_calc_complements(A, &complements);

  matrix_t transponted_complements;
  s21_transpose(&complements, &transponted_complements);

  s21_mult_number(&transponted_complements, 1.0 / det, result);

  s21_remove_matrix(&complements);
  s21_remove_matrix(&transponted_complements);

  return OK;
}