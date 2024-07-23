#include "matrix_oop.h"

Matrix::Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

Matrix::Matrix(int rows, int cols) : Matrix() {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "The size of rows and columns must be greater then zero");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_]();
  for (auto i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[other.rows_]();
  for (auto i = 0; i < other.rows_; ++i) {
    matrix_[i] = new double[other.cols_]();
    std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
  }
}

Matrix::Matrix(Matrix&& other) noexcept {
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.rows_ = 0;
  other.cols_ = 0;
}

Matrix::~Matrix() {
  for (auto i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void Matrix::Resize(const int rows, const int cols) {
  auto tmp = Matrix(rows, cols);
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (i < tmp.rows_ && j < tmp.cols_) tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(tmp);
}

int Matrix::GetCols() { return cols_; }

int Matrix::GetRows() { return rows_; }

void Matrix::SetCols(const int& cols) { Resize(rows_, cols); }

void Matrix::SetRows(const int& rows) { Resize(rows, cols_); }

bool Matrix::EqMatrix(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  bool result = true;
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) result = false;
    }
  }
  return result;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) noexcept {
  for (auto i = 0; i < rows_; i++) {
    for (auto j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Incorrect input, the number of columns of the first matrix must be "
        "equal to the number of rows of the second matrix");
  }
  Matrix result = Matrix(rows_, other.cols_);
  for (auto k = 0; k < cols_; k++) {
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < other.cols_; j++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = Matrix(result);
}

Matrix Matrix::Transpose() noexcept {
  Matrix result = Matrix(cols_, rows_);
  for (auto i = 0; i < cols_; i++) {
    for (auto j = 0; j < rows_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

Matrix Matrix::GetMinor(int row, int col) {
  Matrix result(rows_ - 1, cols_ - 1);
  auto minor_i = 0;
  for (auto i = 0; i < rows_; i++) {
    auto minor_j = 0;
    if (row != i) {
      for (auto j = 0; j < cols_; j++) {
        if (col != j) {
          result.matrix_[minor_i][minor_j++] = matrix_[i][j];
        }
      }
      minor_i++;
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::domain_error("Matrix is not square");
  }
  Matrix result(rows_, cols_);
  if (rows_ != 1) {
    for (auto i = 0; i < rows_; i++) {
      for (auto j = 0; j < cols_; j++) {
        double det = 0;
        Matrix minor(rows_ - 1, cols_ - 1);
        minor = this->GetMinor(i, j);
        det = minor.Determinant();
        result(i, j) = pow(-1, i + j) * det;
      }
    }
  } else {
    result(0, 0) = 1;
  }
  return result;
}

double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::domain_error("Matrix is not square");
  }
  double result = 0;
  if (rows_ > 2) {
    Matrix minor(rows_ - 1, cols_ - 1);
    for (auto i = 0; i < cols_; i++) {
      minor = GetMinor(0, i);
      double det = minor.Determinant();
      result += matrix_[0][i] * pow(-1, i) * det;
    }
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (rows_ == 1) {
    result = matrix_[0][0];
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::domain_error("Matrix is not square");
  }
  double det = Determinant();
  if (fabs(det) < EPS) {
    throw std::domain_error("Inverse matrix does not exist");
  }
  auto result = CalcComplements();
  result = result.Transpose();
  result *= 1 / det;
  return result;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

Matrix Matrix::operator*(const double num) {
  Matrix result = *this;
  result.MulNumber(num);
  return result;
}

bool Matrix::operator==(const Matrix& other) const { return EqMatrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) {
    return *this;
  }
  for (auto i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  for (auto i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.rows_ = 0;
  other.cols_ = 0;
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || cols_ <= col || rows_ <= row) {
    throw std::out_of_range("Out of range");
  }
  return matrix_[row][col];
}

const double& Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || cols_ <= col || rows_ <= row) {
    throw std::out_of_range("Out of range");
  }
  return matrix_[row][col];
}
