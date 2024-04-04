#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Define the return values
#define SUCCESS 1
#define FAILURE 0

// Define the epsilon value
#define EPSILON 1e-7

// Define the status type 0 - OK, 1 - INCORRECT MATRIX, 2 - CALCULATION ERROR
typedef enum { OK, INVALID_MATRIX, CALCULATION_ERROR } status;
typedef enum { false, true } bool;

// Define the matrix structure
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Function prototypes
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Function to create a matrix
void s21_print_matrix(matrix_t *A);