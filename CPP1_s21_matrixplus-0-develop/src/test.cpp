#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

using namespace s21;

const double array[] = {1.08767,  3.4637,  7.5677,  372.7573, 0.8753, 0.2266,
                        0.2266,   -3.4567, -0.4235, -0.8657,  0.4406, 0.6234,
                        0.171,    0.0579,  0.1891,  0.336,    0.2373, 0.4509,
                        0.4646,   -1.0,    0.5,     -4.444,   0.7,    0.6,
                        -113.113, 0.0,     -0.0,    1.0};

void print_matrix(S21Matrix* matrix);
void fill_matrix(double num, S21Matrix* matrix);
void fill_matrix_num(double num, S21Matrix* matrix);
void fill_matrixArray(const double array[], S21Matrix* matrix);
void fill_Identity(S21Matrix* matrix);

// TEST CONSTRUCTOR
// EXCEPTION

TEST(test_constructor, test_1) {
  EXPECT_THROW(S21Matrix A(0, 3), std::out_of_range);
}

TEST(test_constructor, test2) {
  EXPECT_THROW(S21Matrix A(-3, 3), std::out_of_range);
}

TEST(test_constructor, test3) {
  EXPECT_THROW(S21Matrix A(0), std::out_of_range);
}

// NORMAL

TEST(test_constructor, test4) {
  S21Matrix A(2);
  A.set_matr_value(1, 0, 0.113);
  ASSERT_DOUBLE_EQ(A.get_matr_value(1, 0), 0.113);
}

TEST(test_constructor, test5) {
  S21Matrix A(3, 2);
  A.set_matr_value(2, 1, 0.113);
  S21Matrix B(A);
  ASSERT_DOUBLE_EQ(B.get_matr_value(2, 1), 0.113);
}

TEST(test_constructor, test6) {
  S21Matrix A(3, 2);
  A.set_matr_value(2, 1, 0.113);
  S21Matrix B(std::move(A));
  ASSERT_DOUBLE_EQ(B.get_matr_value(2, 1), 0.113);
}

TEST(test_constructor, test7) {
  S21Matrix A(3, 2);
  A.set_matr_value(2, 1, 0.113);
  S21Matrix B(std::move(A));
  ASSERT_DOUBLE_EQ(B.get_matr_value(1, 1), 0.0);
}

// TEST MUTATOR
// EXCEPTION

TEST(test_mutator, test1) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A.set_rows(-3), std::out_of_range);
}

TEST(test_mutator, test2) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A.set_cols(-3), std::out_of_range);
}

TEST(test_mutator, test3) {
  S21Matrix A(1, 1);
  EXPECT_THROW(A.set_matr_value(-1, 1, 1), std::out_of_range);
}

// NORMAL

TEST(test_mutator, test4) {
  S21Matrix A(1, 1);
  A.set_cols(3);
  ASSERT_DOUBLE_EQ(A.get_matr_value(0, 2), 0.0);
}

TEST(test_mutator, test5) {
  S21Matrix A(1, 1);
  A.set_rows(5);
  ASSERT_DOUBLE_EQ(A.get_matr_value(4, 0), 0.0);
}

TEST(test_mutator, test6) {
  S21Matrix A(3, 3);
  A.set_matr_value(2, 2, 0.1231);
  ASSERT_DOUBLE_EQ(A.get_matr_value(2, 2), 0.1231);
}

// TEST ACCESSOR
// EXCEPTION

TEST(test_acessor, test1) {
  S21Matrix A;
  EXPECT_THROW(A.get_matr_value(-3, 3), std::out_of_range);
}

// NORMAL

TEST(test_acessor, test2) {
  S21Matrix A(3, 3);
  ASSERT_EQ(A.get_cols(), 3);
}

TEST(test_acessor, test3) {
  S21Matrix A(3, 3);
  ASSERT_EQ(A.get_rows(), 3);
}

// LIBRARY FUNCTION TESTS
// EQ_MATRIX

TEST(test_eq_matrix, test1) {
  S21Matrix A;
  fill_matrix(1, &A);
  S21Matrix B(A);
  ASSERT_TRUE(A.eq_matrix(B));
}

TEST(test_eq_matrix, test2) {
  S21Matrix A;
  fill_matrix(1, &A);
  S21Matrix B;
  ASSERT_FALSE(A.eq_matrix(B));
}

// SUM_MATRIX
// EXCEPTION

TEST(test_sum_matrix, test1) {
  S21Matrix A;
  S21Matrix B(1, 5);
  EXPECT_THROW(A.sum_matrix(B), std::invalid_argument);
}

// NORMAL

TEST(test_sum_matrix, test2) {
  S21Matrix A;
  fill_matrix_num(1, &A);
  S21Matrix B;
  fill_matrix_num(2, &B);
  A.sum_matrix(A);
  ASSERT_TRUE(A.eq_matrix(B));
}

// SUB_MATRIX
// EXCEPTION

TEST(test_sub_matrix, test1) {
  S21Matrix A;
  S21Matrix B(1, 5);
  EXPECT_THROW(A.sub_matrix(B), std::invalid_argument);
}

// NORMAL

TEST(test_sub_matrix, test2) {
  S21Matrix A;
  fill_matrix_num(1, &A);
  S21Matrix B;
  fill_matrix_num(2, &B);
  B.sub_matrix(A);
  ASSERT_TRUE(A.eq_matrix(B));
}

// MUL_NUMBER
// EXCEPTION

TEST(test_mul_number, test1) {
  S21Matrix A(5, 2);
  S21Matrix B(std::move(A));
  EXPECT_THROW(A.mul_number(2), std::invalid_argument);
}

// NORMAL

TEST(test_mul_number, test2) {
  S21Matrix A;
  fill_matrix_num(1, &A);
  S21Matrix B;
  fill_matrix_num(2, &B);
  A.mul_number(2);
  ASSERT_TRUE(A.eq_matrix(B));
}

TEST(test_mul_number, test3) {
  S21Matrix A;
  fill_matrix_num(1, &A);
  S21Matrix B;
  fill_matrix_num(2, &B);
  A.mul_number(-2);
  ASSERT_FALSE(A.eq_matrix(B));
}

// MUL_MATRIX
// EXCEPTION

TEST(test_mult_matrix, test1) {
  S21Matrix A;
  S21Matrix B(1);
  EXPECT_THROW(A.mul_matrix(B), std::invalid_argument);
}

// NORMAL

TEST(test_mult_matrix, test2) {
  S21Matrix A;
  A.set_matr_value(0, 0, 2);
  S21Matrix B;
  B.set_matr_value(0, 0, 2.32456);
  A.mul_matrix(B);
  ASSERT_DOUBLE_EQ(A.get_matr_value(0, 0), 4.64912);
}

// TRANSPOSE
// EXCEPTION

TEST(test_transpose, test1) {
  S21Matrix A(5, 2);
  S21Matrix B(std::move(A));
  EXPECT_THROW(A.transpose(), std::invalid_argument);
}

// NORMAL

TEST(test_transpose, test2) {
  S21Matrix A(5, 2);
  A.transpose();
  ASSERT_TRUE((5 == A.get_cols() && 2 == A.get_rows()));
}

TEST(test_transpose, test3) {
  S21Matrix A(5, 2);
  A.set_matr_value(4, 0, 13);
  A.transpose();
  ASSERT_DOUBLE_EQ(A.get_matr_value(0, 4), 13);
}

// DETERMINANT
// EXCEPTION

TEST(test_determinant, test1) {
  S21Matrix A(5, 2);
  EXPECT_THROW(A.determinant(), std::invalid_argument);
}

// NORMAL

TEST(test_determinant, test2) {
  S21Matrix A;
  double det = A.determinant();
  ASSERT_DOUBLE_EQ(det, 0.0);
}

TEST(test_determinant, test3) {
  S21Matrix A;
  fill_matrixArray(array, &A);
  double det = A.determinant();
  ASSERT_DOUBLE_EQ(det, -9205.14361469974755891598761081695556640625);
}

TEST(test_determinant, test4) {
  S21Matrix A(1);
  fill_matrixArray(array, &A);
  double det = A.determinant();
  ASSERT_DOUBLE_EQ(det, 1.08766999999999991466);
}

// CALC_COMPLEMENTES
// EXCEPTION

TEST(test_complements, test1) {
  S21Matrix A(5, 2);
  S21Matrix B(std::move(A));
  EXPECT_THROW(A.calc_complements(), std::invalid_argument);
}

// NORMAL

TEST(test_complements, test2) {
  S21Matrix A;
  fill_matrix(1, &A);
  S21Matrix B = A.calc_complements();
  ASSERT_DOUBLE_EQ(B.get_matr_value(1, 1), -12);
}

TEST(test_complements, test3) {
  S21Matrix A(1, 1);
  fill_matrix(1, &A);
  S21Matrix B = A.calc_complements();
  ASSERT_DOUBLE_EQ(B.get_matr_value(0, 0), 1);
}

// INVERSE_MATRIX
// EXCEPTION

TEST(test_inverse_matrix, test1) {
  S21Matrix A;
  EXPECT_THROW(A.inverse_matrix(), std::invalid_argument);
}

// NORMAL

TEST(test_inverse_matrix, test2) {
  S21Matrix A;
  fill_matrixArray(array, &A);
  S21Matrix B = A.inverse_matrix();
  ASSERT_DOUBLE_EQ(B.get_matr_value(1, 1), 0.00023633189834496235);
}

TEST(test_inverse_matrix, test3) {
  S21Matrix A;
  S21Matrix Identity;
  fill_Identity(&Identity);
  fill_matrixArray(array, &A);
  S21Matrix C = A.inverse_matrix();
  A.mul_matrix(C);
  ASSERT_EQ(A.eq_matrix(Identity), true);
}

// TEST OPERATORS

// TEST OPERATOR "="

TEST(test_operator_eq, test1) {
  S21Matrix A(5, 5);
  S21Matrix B;
  fill_matrixArray(array, &A);
  B = A;
  ASSERT_DOUBLE_EQ(B.get_matr_value(4, 4), -113.113);
}

// TEST OPERATOR "+"








// END TEST - END TEST - END TEST - END TEST - END TEST

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void print_matrix(S21Matrix* matrix) {
  int rows = matrix->get_rows();
  int cols = matrix->get_cols();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      std::cout.setf(std::ios::left);
      std::cout.width(4);
      std::cout << matrix->get_matr_value(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

void fill_matrix(double num, S21Matrix* matrix) {
  int rows = matrix->get_rows();
  int cols = matrix->get_cols();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix->set_matr_value(i, j, num);
      num++;
    }
  }
}

void fill_matrix_num(double num, S21Matrix* matrix) {
  int rows = matrix->get_rows();
  int cols = matrix->get_cols();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix->set_matr_value(i, j, num);
    }
  }
}

void fill_matrixArray(const double array[], S21Matrix* matrix) {
  int rows = matrix->get_rows();
  int cols = matrix->get_cols();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix->set_matr_value(i, j, (array[i * rows + j]));
    }
  }
}

void fill_Identity(S21Matrix* matrix) {
  int rows = matrix->get_rows();
  int cols = matrix->get_cols();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == j)
        matrix->set_matr_value(i, j, 1.0);
      else
        matrix->set_matr_value(i, j, 0.0);
    }
  }
}

// void fill_matrix(S21Matrix* matrix) {
//   int rows = matrix->get_rows();
//   int cols = matrix->get_cols();
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       matrix->set_matr_value(i, j, (i * rows + j));
//     }
//   }
// }

// int main() {
//   try {
//     // s21::S21Matrix m7(m6);
//     // s21::S21Matrix m8(std::move(m4));
//     // s21::S21Matrix m9(std::move(m4));
//     // m.set_cols(4);
//     // std::cout << std::endl;
//     // m.print_matrix();
//     // std::cout << std::endl;
//     m.fill_matrix(0);
// m.print_matrix();
//     std::cout << m.get_matrix(3, 1);
//     std::cout << std::endl;
//     // std::cout << m.get_rows() << " " << m.get_cols() << std::endl;
//     // std::cout << m.get_rows() << " " << m.get_cols() << std::endl;
//     // m.set_rows(7);
//     // std::cout<< m.get_rows() << " " << m.get_cols() << std::endl;

//   } catch (const char* msg) {

//     std::cout << msg << std::endl;

//   }

//   std::cout << "EXIT" << std::endl;
//   return 0;
// }
