#include <gtest/gtest.h>

// #include <iostream>

#include "../src/matrix_oop.h"

void InitMatrix(Matrix& matrix, double val) {
  int cols = matrix.GetCols();
  int rows = matrix.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix(i, j) = val;
    }
  }
}

void EqElems(Matrix& matrix, double val) {
  int cols = matrix.GetCols();
  int rows = matrix.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      EXPECT_EQ(matrix(i, j), val);
    }
  }
}

// Constructor tests

TEST(DefaultConstructor, Test_1) {
  auto matrix = Matrix();
  ASSERT_EQ(matrix.GetCols(), 0);
  ASSERT_EQ(matrix.GetRows(), 0);
}

TEST(ParameterizedConstructor, Test_1) {
  auto matrix = Matrix(2, 3);
  ASSERT_EQ(matrix.GetCols(), 3);
  ASSERT_EQ(matrix.GetRows(), 2);
}

TEST(ParameterizedConstructor, Test_2) {
  ASSERT_ANY_THROW(Matrix matrix(-2, 3));
}

TEST(ParameterizedConstructor, Test_3) {
  auto matrix = Matrix(10, 10);
  EqElems(matrix, 0);
}

TEST(CopyConstructorTest, Test_1) {
  auto matrix = Matrix(10, 10);
  matrix(1, 3) = 7.89;
  Matrix new_matrix(matrix);
  ASSERT_EQ(new_matrix(1, 3), 7.89);
}

TEST(MoveConstructorTest, Test_1) {
  Matrix matrix(10, 10);
  Matrix new_matrix(std::move(matrix));
  ASSERT_EQ(new_matrix(4, 4), 0);
}

TEST(MutatorTest, Test_1) {
  Matrix matrix(2, 2);
  matrix.SetCols(5);
  ASSERT_EQ(matrix.GetRows(), 2);
  ASSERT_EQ(matrix.GetCols(), 5);
}

TEST(MutatorTest, Test_2) {
  Matrix matrix(2, 2);
  matrix.SetRows(5);
  ASSERT_EQ(matrix.GetRows(), 5);
  ASSERT_EQ(matrix.GetCols(), 2);
}

// Operator overloading tests

TEST(OperatorSum, Test_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  Matrix result1(3, 3);
  result1 = matrix1 + matrix2;
  EqElems(result1, 6);
}

TEST(OperatorSum, Test_2) {
  Matrix matrix1(2, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  ASSERT_ANY_THROW(matrix1 + matrix2);
}

TEST(OperatorSub, Test_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  Matrix result1(3, 3);
  result1 = matrix1 - matrix2;
  EqElems(result1, 0);
}

TEST(OperatorSub, Test_2) {
  Matrix matrix1(5, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  ASSERT_ANY_THROW(matrix1 - matrix2);
}

TEST(OperatorMulMatrix, Test_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  Matrix result1(3, 3);
  result1 = matrix1 * matrix2;
  EqElems(result1, 27);
}

TEST(OperatorMulMatrix, Test_2) {
  Matrix matrix1(3, 8);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  ASSERT_ANY_THROW(matrix1 * matrix2);
}

TEST(OperatorMulNum, Test_1) {
  Matrix matrix(3, 3);
  InitMatrix(matrix, 3);
  Matrix result(3, 3);
  result = matrix * 3;
  EqElems(result, 9);
}

TEST(OperatorEqEq, Test_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  bool res = matrix1 == matrix2;
  EXPECT_EQ(res, true);
}

TEST(OperatorEqEq, Test_2) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 4);
  InitMatrix(matrix2, 3);
  bool res = matrix1 == matrix2;
  EXPECT_EQ(res, false);
}

TEST(OperatorEqEq, Test_3) {
  Matrix matrix1(10, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  ASSERT_ANY_THROW(matrix1 == matrix2);
}

TEST(OperatorGetValue, Test_1) {
  const Matrix matrix(3, 3);
  EXPECT_EQ(matrix(1, 1), 0);
}

TEST(OperatorGetValue, Test_2) {
  const Matrix matrix(3, 3);
  ASSERT_ANY_THROW(matrix(-1, 1));
}

TEST(OperatorGetValue, Test_3) {
  Matrix matrix(3, 3);
  InitMatrix(matrix, 4);
  ASSERT_ANY_THROW(matrix(-1, 1));
}

TEST(OperatorEq, Test_1) {
  Matrix matrix1(2, 2);
  Matrix matrix2(1, 1);
  matrix2 = matrix1;
  bool res = matrix1 == matrix2;
  ASSERT_EQ(matrix2.GetRows(), 2);
  ASSERT_EQ(matrix2.GetCols(), 2);
  EXPECT_EQ(res, true);
}

TEST(OperatorEq, Test_2) {
  Matrix matrix1(2, 2);
  Matrix matrix2(2, 2);
  matrix2 = matrix1;
  EXPECT_EQ(matrix1 == matrix2, true);
}

TEST(OperatorEqSum, Test_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  matrix1 += matrix2;
  EqElems(matrix1, 6);
}

TEST(OperatorEqSum, Test_2) {
  Matrix matrix1(2, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  ASSERT_ANY_THROW(matrix1 += matrix2);
}

TEST(OperatorEqSub, Test_1) {
  Matrix matrix1(3, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  matrix1 -= matrix2;
  EqElems(matrix1, 0);
}

TEST(OperatorEqSub, Test_2) {
  Matrix matrix1(5, 3);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  ASSERT_ANY_THROW(matrix1 -= matrix2);
}

TEST(OperatorEqMulMatrix, Test_1) {
  Matrix matrix1(4, 8);
  Matrix matrix2(8, 2);
  matrix1 *= matrix2;
  ASSERT_EQ(matrix1.GetRows(), 4);
  ASSERT_EQ(matrix1.GetCols(), 2);
  EqElems(matrix1, 0);
}

TEST(OperatorEqMulMatrix, Test_2) {
  Matrix matrix1(3, 8);
  Matrix matrix2(3, 3);
  InitMatrix(matrix1, 3);
  InitMatrix(matrix2, 3);
  ASSERT_ANY_THROW(matrix1 *= matrix2);
}

TEST(OperatorEqMulNum, Test_1) {
  Matrix matrix(3, 3);
  InitMatrix(matrix, 3);
  matrix *= 3;
  EqElems(matrix, 9);
}

// Function tests

TEST(EqMatrix, Test_1) {
  auto matrix_1 = Matrix{5, 5};
  auto matrix_2 = Matrix{5, 5};
  ASSERT_EQ(matrix_1.EqMatrix(matrix_2), true);
}

TEST(EqMatrix, Test_2) {
  auto matrix_1 = Matrix{5, 5};
  auto matrix_2 = Matrix{4, 4};
  ASSERT_ANY_THROW(matrix_1.EqMatrix(matrix_2));
}

TEST(SumMatrix, Test_1) {
  auto matrix_1 = Matrix{5, 5};
  auto matrix_2 = Matrix{5, 5};
  InitMatrix(matrix_1, 3);
  InitMatrix(matrix_2, 5);
  matrix_1.SumMatrix(matrix_2);
  EqElems(matrix_1, 8);
}

TEST(SubMatrix, Test_1) {
  auto matrix_1 = Matrix{5, 5};
  auto matrix_2 = Matrix{5, 5};
  InitMatrix(matrix_1, 3);
  InitMatrix(matrix_2, 5);
  matrix_1.SubMatrix(matrix_2);
  EqElems(matrix_1, -2);
}

TEST(Transpose, Test_1) {
  auto matrix = Matrix{2, 2};
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  auto result = matrix.Transpose();
  ASSERT_EQ(result(0, 0), 1);
  ASSERT_EQ(result(0, 1), 3);
  ASSERT_EQ(result(1, 0), 2);
  ASSERT_EQ(result(1, 1), 4);
}

TEST(Determinant, Test_1) {
  auto matrix = Matrix{2, 3};
  ASSERT_ANY_THROW(matrix.Determinant());
}

TEST(Determinant, Test_2) {
  auto matrix = Matrix{3, 3};
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;
  ASSERT_EQ(matrix.Determinant(), 0);
}

TEST(Determinant, Test_3) {
  auto matrix = Matrix{1, 1};
  matrix(0, 0) = 1;
  ASSERT_EQ(matrix.Determinant(), 1);
}

TEST(CalcComplements, Test_1) {
  auto matrix = Matrix{1, 3};
  ASSERT_ANY_THROW(matrix.CalcComplements());
}

TEST(CalcComplements, Test_2) {
  auto matrix_1 = Matrix{3, 3};
  matrix_1(0, 0) = 1;
  matrix_1(0, 1) = 2;
  matrix_1(0, 2) = 3;
  matrix_1(1, 0) = 0;
  matrix_1(1, 1) = 4;
  matrix_1(1, 2) = 2;
  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = 2;
  matrix_1(2, 2) = 1;
  auto matrix_2 = Matrix{3, 3};
  matrix_2(0, 0) = 0;
  matrix_2(0, 1) = 10;
  matrix_2(0, 2) = -20;
  matrix_2(1, 0) = 4;
  matrix_2(1, 1) = -14;
  matrix_2(1, 2) = 8;
  matrix_2(2, 0) = -8;
  matrix_2(2, 1) = -2;
  matrix_2(2, 2) = 4;
  matrix_1 = matrix_1.CalcComplements();
  ASSERT_EQ(matrix_1 == matrix_2, true);
}
TEST(CalcComplements, Test_3) {
  auto matrix = Matrix{1, 1};
  matrix = matrix.CalcComplements();
  ASSERT_EQ(matrix(0, 0), 1);
}

TEST(InverseMatrix, Test_1) {
  auto matrix = Matrix{1, 3};
  ASSERT_ANY_THROW(matrix.InverseMatrix());
}

TEST(InverseMatrix, Test_2) {
  auto matrix_1 = Matrix{3, 3};
  matrix_1(0, 0) = 2;
  matrix_1(0, 1) = 5;
  matrix_1(0, 2) = 7;
  matrix_1(1, 0) = 6;
  matrix_1(1, 1) = 3;
  matrix_1(1, 2) = 4;
  matrix_1(2, 0) = 5;
  matrix_1(2, 1) = -2;
  matrix_1(2, 2) = -3;
  auto matrix_2 = Matrix{3, 3};
  matrix_2(0, 0) = 1;
  matrix_2(0, 1) = -1;
  matrix_2(0, 2) = 1;
  matrix_2(1, 0) = -38;
  matrix_2(1, 1) = 41;
  matrix_2(1, 2) = -34;
  matrix_2(2, 0) = 27;
  matrix_2(2, 1) = -29;
  matrix_2(2, 2) = 24;
  matrix_1 = matrix_1.InverseMatrix();
  ASSERT_EQ(matrix_1 == matrix_2, true);
}

TEST(InverseMatrix, Test_3) {
  auto matrix = Matrix{3, 3};
  ASSERT_ANY_THROW(matrix.InverseMatrix());
}
