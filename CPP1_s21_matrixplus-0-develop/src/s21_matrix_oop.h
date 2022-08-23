#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <math.h>

#include <exception>
#include <iostream>
#include <stdexcept>

constexpr double EPS = 1e-7;

namespace s21 {

class S21Matrix {
 public:
  // Constructor
  S21Matrix() : S21Matrix(3) {}
  S21Matrix(int rows) : S21Matrix(rows, rows) {}
  S21Matrix(int rows, int colums);
  // Copy
  S21Matrix(const S21Matrix &another);
  // Move
  S21Matrix(S21Matrix &&another);
  // Distructor
  ~S21Matrix();

  // Getter function
  int get_rows() const;
  int get_cols() const;
  double get_matr_value(int rows, int colums) const;
  // Setter function
  void set_rows(int rows);
  void set_cols(int colums);
  void set_matr_value(int row, int col, double num);

  // Standart function the matrix lib
  bool eq_matrix(const S21Matrix &other);
  void sum_matrix(const S21Matrix &other);
  void sub_matrix(const S21Matrix &other);
  void mul_number(const double num);
  void mul_matrix(const S21Matrix &other);
  S21Matrix transpose();
  S21Matrix calc_complements();
  double determinant();
  S21Matrix inverse_matrix();
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double number);
  // to do оператор умножения числа на матрицу;
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);

  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  double operator()(int rows, int colums);
  
  // // Additional public functions
  // void print_matrix() const;
  // void fill_matrix(double num);

 private:
  // Main parameters
  int rows_;
  int cols_;
  double **matrix_;

  // Additional private functions
  bool check_matrix() const;
  bool checkSize_matrix(const S21Matrix& other) const;
  bool checkSquare_matrix() const;
  void create_matrix();
  void remove_matrix();
  void copy_matrix(const S21Matrix &another);
  void resize_matrix(int rows, int colums);
  void get_minor(int row, int column);
};
}  // namespace s21

#endif  // SRC_S21_MATRIX_OOP_H_