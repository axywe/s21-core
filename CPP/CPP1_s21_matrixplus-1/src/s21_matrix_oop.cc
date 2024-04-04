#include "s21_matrix_oop.h"

// Default constructor
S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

// Constructor with parameters
S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) {
    throw std::runtime_error(
        "Error: The number of rows and columns must be greater than zero");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

// Copy constructor
S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Move constructor
S21Matrix::S21Matrix(S21Matrix&& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

// Destructor
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

// Assignment operator
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

// Compare two matrices
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

// Sum two matrices
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Subtract two matrices
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Multiply a matrix by a number
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

// Multiply two matrices
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0.0;
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = S21Matrix(result);
}

// Transpose a matrix
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

// Calculate the complements of a matrix
S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      // Create a new matrix with the size of the original matrix minus one
      S21Matrix sub_matrix(rows_ - 1, cols_ - 1);

      // Copy the values of the original matrix to the new matrix
      for (int k = 0; k < rows_ - 1; k++) {
        for (int l = 0; l < cols_ - 1; l++) {
          if (k < i && l < j) {
            sub_matrix.matrix_[k][l] = matrix_[k][l];
          } else if (k < i && l >= j) {
            sub_matrix.matrix_[k][l] = matrix_[k][l + 1];
          } else if (k >= i && l < j) {
            sub_matrix.matrix_[k][l] = matrix_[k + 1][l];
          } else {
            sub_matrix.matrix_[k][l] = matrix_[k + 1][l + 1];
          }
        }
      }

      // Calculate the determinant of the new matrix
      result.matrix_[i][j] = sub_matrix.Determinant();

      // Calculate the sign of the complement
      if ((i + j) % 2 == 1) {
        result.matrix_[i][j] *= -1;
      }
    }
  }

  return result;
}

// Calculate the determinant of a matrix
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::runtime_error("Error: The matrix must be square");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double det = 0;

  for (int i = 0; i < rows_; i++) {
    S21Matrix sub_matrix(rows_ - 1, cols_ - 1);

    for (int j = 1; j < rows_; j++) {
      for (int k = 0; k < cols_; k++) {
        if (k < i) {
          sub_matrix.matrix_[j - 1][k] = matrix_[j][k];
        } else if (k > i) {
          sub_matrix.matrix_[j - 1][k - 1] = matrix_[j][k];
        }
      }
    }

    double sub_det = sub_matrix.Determinant();

    if (i % 2 == 0) {
      det += matrix_[0][i] * sub_det;
    } else {
      det -= matrix_[0][i] * sub_det;
    }
  }

  return det;
}

// Calculate the inverse of a matrix
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::runtime_error("Error: The matrix must be square");
  }

  double determinant = Determinant();
  if (determinant == 0) {
    throw std::runtime_error("Error: The matrix is not invertible");
  }

  S21Matrix result = CalcComplements();
  result = result.Transpose();
  result.MulNumber(1 / determinant);

  return result;
}

// Addition of two matrices. Different matrix dimensions.
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }

  return result;
}

// Subtraction of one matrix from another. Different matrix dimensions.
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }

  return result;
}

// Matrix multiplication and matrix multiplication by a number. The number of
// columns of the first matrix does not equal the number of rows of the second
// matrix.
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match number of rows in "
        "the second matrix.");
  }

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j] * num;
    }
  }

  return result;
}

// Checks for matrices equality (EqMatrix).
bool S21Matrix::operator==(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
}

// Addition assignment (SumMatrix) different matrix dimensions.
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }

  return *this;
}

// Difference assignment (SubMatrix) different matrix dimensions.
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error(
        "Error: The matrices must have the same dimensions");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }

  return *this;
}

// Multiplication assignment (MulMatrix/MulNumber). The number of columns of the
// first matrix does not equal the number of rows of the second matrix.
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::runtime_error(
        "Number of columns in the first matrix should match the number of rows "
        "in the second matrix for matrix multiplication.");
  }

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;

      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = result;

  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }

  return *this;
}

// Indexation by matrix elements (row, column). Index is outside the matrix.
double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::runtime_error("Error: Index is outside the matrix");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::runtime_error("Error: Index is outside the matrix");
  }
  return matrix_[row][col];
}

// Setter functions
void S21Matrix::set_cols(int cols) {
  if (cols < 0) {
    throw std::invalid_argument(
        "Error: The number of columns must be greater than zero");
  }
  cols_ = cols;
}

void S21Matrix::set_rows(int rows) {
  if (rows < 0) {
    throw std::invalid_argument(
        "Error: The number of rows must be greater than zero");
  }
  rows_ = rows;
}