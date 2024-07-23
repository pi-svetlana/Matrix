#ifndef MATRIXPLUS_MATRIX_OOP_H_
#define MATRIXPLUS_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <iostream>
#define EPS 1e-7

class Matrix {
 public:
  Matrix();                    //Базовый конструктор
  Matrix(int rows, int cols);  //Параметризированный конструктор с
  //количеством строк и столбцов
  Matrix(const Matrix& other);  //Конструктор копирования
  Matrix(Matrix&& other) noexcept;  //Конструктор переноса
  ~Matrix();                        //Деструктор класса Matrix

  int GetCols();
  int GetRows();
  void SetCols(const int& cols);
  void SetRows(const int& rows);

  /// operator overloading

  Matrix operator+(const Matrix& other);  //Сложение двух матриц
  Matrix operator-(const Matrix& other);  //Вычитание одной матрицы из другой
  Matrix operator*(const Matrix& other);  //Умножение двух матриц
  Matrix operator*(const double num);  //Умножение матрицы на число
  bool operator==(
      const Matrix& other) const;  //Проверка на равенство матриц (EqMatrix)
  Matrix& operator=(
      const Matrix& other);  //Присвоение матрице значений другой матрицы
  Matrix& operator=(Matrix&& other) noexcept;  //Оператор переноса
  // Matrix& operator=(Matrix& other) noexcept;
  Matrix& operator+=(const Matrix& other);  //Присвоение сложения (SumMatrix)
  Matrix& operator-=(const Matrix& other);  //Присвоение разности (SubMatrix)
  Matrix& operator*=(const Matrix& other);  //Присвоение умножения (MulMatrix)
  Matrix& operator*=(const double num);  //Присвоение умножения (MulNumber)
  double& operator()(
      int row, int col);  //Индексация по элементам матрицы (строка, колонка)
  const double& operator()(int row, int col)
      const;  //Индексация по элементам матрицы (строка, колонка)

  /// library functions

  bool EqMatrix(
      const Matrix& other) const;  //Проверяет матрицы на равенство между собой
  void SumMatrix(const Matrix& other);  //Прибавляет вторую матрицы к текущей
  void SubMatrix(const Matrix& other);  //Вычитает из текущей матрицы другую
  void MulNumber(
      const double num) noexcept;  //Умножает текущую матрицу на число
  void MulMatrix(const Matrix& other);  //Умножает текущую матрицу на вторую
  Matrix Transpose() noexcept;  //Создает новую транспонированную матрицу из
  //текущей и возвращает ее
  Matrix CalcComplements();  //Вычисляет матрицу алгебраических дополнений
  //текущей матрицы и возвращает ее
  double Determinant();  //Вычисляет и возвращает определитель текущей матрицы
  Matrix InverseMatrix();  //Вычисляет и возвращает обратную матрицу

 private:
  int rows_, cols_;
  double** matrix_;

  void Resize(const int rows, const int cols);
  Matrix GetMinor(int row, int col);
};

#endif  // MATRIXPLUS_MATRIX_OOP_H_