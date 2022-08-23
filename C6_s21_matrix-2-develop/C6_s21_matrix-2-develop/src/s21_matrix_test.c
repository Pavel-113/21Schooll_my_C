#include "s21_matrix.h"

#include <check.h>

int test_case();
matrix_t create_identity_matrix(int n);
void fill_matrix(matrix_t *A);
void fill_matrix_1(matrix_t *A, double n);
void print_matrix(matrix_t *A);
void fill_matrix_array(matrix_t *A, double *arr);
void fill_matrix_num(matrix_t *A, double n);

START_TEST(test_s21_create_matrix) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  int num = s21_create_matrix(4, 4, &A);
  ck_assert_int_eq(num, 0);
  num = s21_create_matrix(1, 1, &B);
  ck_assert_int_eq(num, 0);
  num = s21_create_matrix(-3, -4, &C);
  ck_assert_int_eq(num, 1);
  num = s21_create_matrix(0, 0, &D);
  ck_assert_int_eq(num, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_s21_remove_matrix) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  s21_create_matrix(3, 4, &A);
  s21_remove_matrix(&A);
  s21_remove_matrix(&A);
  ck_assert_ptr_eq(A.matrix, NULL);
  s21_create_matrix(1, 1, &B);
  s21_remove_matrix(&B);
  ck_assert_ptr_eq(B.matrix, NULL);
  s21_create_matrix(-3, -4, &C);
  s21_remove_matrix(&C);
  ck_assert_ptr_eq(C.matrix, NULL);
  s21_create_matrix(0, 0, &D);
  s21_remove_matrix(&D);
  ck_assert_ptr_eq(D.matrix, NULL);
}
END_TEST

START_TEST(test_s21_eq_matrix) {
  matrix_t A;
  s21_create_matrix(3, 4, &A);
  matrix_t B;
  s21_create_matrix(4, 3, &B);
  matrix_t C;
  s21_create_matrix(3, 4, &C);
  matrix_t D;
  s21_create_matrix(-4, 3, &D);
  matrix_t E;
  s21_create_matrix(1, 1, &E);
  fill_matrix(&A);
  fill_matrix(&B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  int eq = s21_eq_matrix(&A, &C);
  ck_assert_int_eq(eq, FAILURE);
  fill_matrix(&C);
  ck_assert_int_eq(s21_eq_matrix(&A, &C), SUCCESS);
  A.matrix[0][0] = 0.000005;
  int eq1 = s21_eq_matrix(&E, &E);
  ck_assert_int_eq(s21_eq_matrix(&A, &C), FAILURE);
  ck_assert_int_eq(eq1, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
  s21_remove_matrix(&E);
}
END_TEST

START_TEST(SUM_RETURN_CODE) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t result_C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(-5, 0, &B);
  s21_create_matrix(8, 3, &C);
  ck_assert_int_eq(s21_sum_matrix(&A, &A, &result_A), 0);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result_B), 1);
  ck_assert_int_eq(s21_sum_matrix(&A, &C, &result_C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&result_C);
}
END_TEST

START_TEST(SUM_FUNCTIONAL) {
  matrix_t A;
  matrix_t B;
  matrix_t ans;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  fill_matrix_1(&A, 0);
  s21_create_matrix(3, 3, &B);
  fill_matrix_num(&B, 1);
  s21_create_matrix(3, 3, &ans);
  fill_matrix_1(&ans, 1);
  s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(s21_eq_matrix(&ans, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&ans);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(SUB_RETURN_CODE) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t result_C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(-5, 0, &B);
  s21_create_matrix(8, 3, &C);
  ck_assert_int_eq(s21_sub_matrix(&A, &A, &result_A), 0);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result_B), 1);
  ck_assert_int_eq(s21_sub_matrix(&A, &C, &result_C), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&result_C);
}
END_TEST

START_TEST(SUB_FUNCTIONAL) {
  matrix_t A;
  matrix_t B;
  matrix_t ans;
  matrix_t result;
  s21_create_matrix(3, 3, &A);
  fill_matrix_1(&A, 1);
  s21_create_matrix(3, 3, &B);
  fill_matrix_1(&B, 0);
  s21_create_matrix(3, 3, &ans);
  fill_matrix_num(&ans, 1);
  s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(s21_eq_matrix(&ans, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&ans);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(MULT_N_RETURN_CODE) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t result_C;
  double num = 2.0;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(-5, 0, &B);
  s21_create_matrix(8, 3, &C);
  ck_assert_int_eq(s21_mult_number(&A, num, &result_A), 0);
  ck_assert_int_eq(s21_mult_number(&B, num, &result_B), 1);
  ck_assert_int_eq(s21_mult_number(&C, num, &result_C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&result_C);
}
END_TEST

START_TEST(MULT_N_FUNCTIONAL) {
  matrix_t A;
  matrix_t result;
  matrix_t ans;
  double num = 2.0;
  s21_create_matrix(3, 3, &A);
  fill_matrix_1(&A, 1);
  s21_sum_matrix(&A, &A, &ans);
  s21_mult_number(&A, num, &result);
  ck_assert_int_eq(s21_eq_matrix(&ans, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(MULT_MATRIX_RETURN_CODE) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t result_C;
  matrix_t result_D;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(-5, 0, &C);
  s21_create_matrix(8, 3, &D);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result_A), 0);
  ck_assert_int_eq(s21_mult_matrix(&A, &A, &result_B), 2);
  ck_assert_int_eq(s21_mult_matrix(&A, &C, &result_C), 1);
  ck_assert_int_eq(s21_mult_matrix(&A, &D, &result_D), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&result_C);
  s21_remove_matrix(&result_D);
}
END_TEST

START_TEST(MULT_MATRIX_FUNCTIONAL) {
  matrix_t A;
  matrix_t B;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t ans;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &ans);
  s21_mult_matrix(&A, &A, &result_A);
  ck_assert_int_eq(s21_eq_matrix(&ans, &result_A), SUCCESS);
  fill_matrix_num(&A, 3.333333);
  fill_matrix_num(&B, 3.333333);
  fill_matrix_num(&ans, 33.333326666667);
  s21_mult_matrix(&A, &B, &result_B);
  ck_assert_int_eq(s21_eq_matrix(&ans, &result_B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&ans);
}
END_TEST

START_TEST(TRANSPOSE_RETURN_CODE) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t result_C;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(-5, 0, &B);
  s21_create_matrix(3, 3, &C);
  ck_assert_int_eq(s21_transpose(&A, &result_A), 0);
  ck_assert_int_eq(s21_transpose(&B, &result_B), 1);
  ck_assert_int_eq(s21_transpose(&C, &result_C), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&result_C);
}
END_TEST

START_TEST(TRANSPOSE_FUNCTIONAL) {
  matrix_t A;
  matrix_t result;
  matrix_t ans;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &ans);
  s21_transpose(&A, &result);
  ck_assert_int_eq(s21_eq_matrix(&ans, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&ans);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(DETERMINANT_RETURN_CODE) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(-3, 3, &B);
  s21_create_matrix(5, 3, &C);
  double d = 0.0;
  int res_A = s21_determinant(&A, &d);
  int res_B = s21_determinant(&B, &d);
  int res_C = s21_determinant(&C, &d);
  ck_assert_int_eq(res_A, 0);
  ck_assert_int_eq(res_B, 1);
  ck_assert_int_eq(res_C, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(DETERMINANT_FUNCTIONAL) {
  double d = 0.0;
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  s21_determinant(&A, &d);
  ck_assert_int_eq(d, 0);
  d = 0.0;
  s21_remove_matrix(&A);
  matrix_t D;
  s21_create_matrix(2, 2, &D);
  fill_matrix(&D);
  s21_determinant(&D, &d);
  ck_assert_int_eq(d, -2);
  s21_remove_matrix(&D);
  d = 0.0;
  matrix_t E;
  s21_create_matrix(4, 4, &E);
  double mass_E[] = {3.00, 5.00, 7.00, -5.00, 68.00, -3.00, 4.00, 0.00,
                     0.00, -91.00, 5.00, -76.00, 7.00, 6.00, 3.00, 1.00};
  fill_matrix_array(&E, mass_E);
  s21_determinant(&E, &d);
  ck_assert_int_eq(d, 19050);
  s21_remove_matrix(&E);
  d = 0.0;
  matrix_t F;
  s21_create_matrix(3, 3, &F);
  fill_matrix_num(&F, 1);
  s21_determinant(&F, &d);
  ck_assert_int_eq(d, 0);
  s21_remove_matrix(&F);
  d = 0.0;
  matrix_t G = create_identity_matrix(5);
  s21_determinant(&G, &d);
  ck_assert_int_eq(d, 1);
  s21_remove_matrix(&G);
  d = 0.0;
  matrix_t J;
  s21_create_matrix(3, 3, &J);
  double mass_J[] = {23.00, 345.00, 2.00,
                     65.00, 176.00, 4.00,
                     0.00, 345.00, 14.00};
  fill_matrix_array(&J, mass_J);
  s21_determinant(&J, &d);
  ck_assert_int_eq(d, -244168);
  s21_remove_matrix(&J);
  d = 0.0;
}
END_TEST

START_TEST(CALC_COMPLEMENTS_RETURN_CODE) {
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t result_C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(-3, 3, &B);
  s21_create_matrix(5, 3, &C);
  int res_A_res = s21_calc_complements(&A, &result_A);
  int res_B_res = s21_calc_complements(&B, &result_B);
  int res_C_res = s21_calc_complements(&C, &result_C);
  ck_assert_int_eq(res_A_res, 0);
  ck_assert_int_eq(res_B_res, 1);
  ck_assert_int_eq(res_C_res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&result_C);
}
END_TEST

START_TEST(CALC_COMPLEMENTS_FUNCTIONAL) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  double arr_A[] = {1.00, 2.00, 3.00, 0.00, 4.00, 2.00, 5.00, 2.00, 1.00};
  fill_matrix_array(&A, arr_A);
  matrix_t A_res;
  s21_calc_complements(&A, &A_res);
  matrix_t A_ans;
  s21_create_matrix(3, 3, &A_ans);
  double arr_A_ans[] = {0.00, 10.00, -20.00, 4.00, -14.00, 8.00, -8.00, -2.00, 4.00};
  fill_matrix_array(&A_ans, arr_A_ans);
  ck_assert_int_eq(s21_eq_matrix(&A_ans, &A_res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&A_res);
  s21_remove_matrix(&A_ans);
  matrix_t D = create_identity_matrix(3);
  matrix_t D_res;
  s21_calc_complements(&D, &D_res);
  ck_assert_int_eq(s21_eq_matrix(&D, &D_res), SUCCESS);
  s21_remove_matrix(&D);
  s21_remove_matrix(&D_res);
  matrix_t B;
  matrix_t B_res;
  s21_create_matrix(1, 1, &B);
  s21_calc_complements(&B, &B_res);
  s21_remove_matrix(&B);
  s21_remove_matrix(&B_res);
}
END_TEST

START_TEST(INVERSE_RETURN_CODE) {
  matrix_t A = create_identity_matrix(4);
  matrix_t B;
  matrix_t C;
  matrix_t D;
  matrix_t result_A;
  matrix_t result_B;
  matrix_t result_C;
  matrix_t result_D;
  s21_create_matrix(-3, 3, &B);
  s21_create_matrix(5, 3, &C);
  s21_create_matrix(3, 3, &D);
  int res_A_res = s21_inverse_matrix(&A, &result_A);
  int res_B_res = s21_inverse_matrix(&B, &result_B);
  int res_C_res = s21_inverse_matrix(&C, &result_C);
  int res_D_res = s21_inverse_matrix(&D, &result_D);
  ck_assert_int_eq(res_A_res, 0);
  ck_assert_int_eq(res_B_res, 1);
  ck_assert_int_eq(res_C_res, 2);
  ck_assert_int_eq(res_D_res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
  s21_remove_matrix(&result_A);
  s21_remove_matrix(&result_B);
  s21_remove_matrix(&result_C);
  s21_remove_matrix(&result_D);
}

START_TEST(INVERSE_FUNCTIONAL) {
  matrix_t A;
  matrix_t A_res;
  s21_create_matrix(3, 3, &A);
  double arr_a[] = {2.00, 5.00, 7.00, 6.00, 3.00, 4.00, 5.00, -2.00, 3.00};
  fill_matrix_array(&A, arr_a);

  s21_inverse_matrix(&A, &A_res);

  matrix_t identity = create_identity_matrix(3);
  matrix_t res_mult;
  s21_mult_matrix(&A, &A_res, &res_mult);
  ck_assert_int_eq(s21_eq_matrix(&res_mult, &identity), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&A_res);
  s21_remove_matrix(&identity);
  s21_remove_matrix(&res_mult);
}

int main(void) {
  int nf = 0;
  nf += test_case();
  return 0;
}

int test_case() {
  Suite *s = suite_create("Â¯\\_(*_*)_/Â¯");
  TCase *tc = tcase_create("");
  SRunner *sr = srunner_create(s);
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_s21_create_matrix);
  tcase_add_test(tc, test_s21_remove_matrix);
  tcase_add_test(tc, test_s21_eq_matrix);
  tcase_add_test(tc, SUM_RETURN_CODE);
  tcase_add_test(tc, SUM_FUNCTIONAL);
  tcase_add_test(tc, SUB_RETURN_CODE);
  tcase_add_test(tc, SUB_FUNCTIONAL);
  tcase_add_test(tc, MULT_N_RETURN_CODE);
  tcase_add_test(tc, MULT_N_FUNCTIONAL);
  tcase_add_test(tc, MULT_MATRIX_RETURN_CODE);
  tcase_add_test(tc, MULT_MATRIX_FUNCTIONAL);
  tcase_add_test(tc, TRANSPOSE_RETURN_CODE);
  tcase_add_test(tc, TRANSPOSE_FUNCTIONAL);
  tcase_add_test(tc, DETERMINANT_RETURN_CODE);
  tcase_add_test(tc, DETERMINANT_FUNCTIONAL);
  tcase_add_test(tc, CALC_COMPLEMENTS_RETURN_CODE);
  tcase_add_test(tc, CALC_COMPLEMENTS_FUNCTIONAL);
  tcase_add_test(tc, INVERSE_RETURN_CODE);
  tcase_add_test(tc, INVERSE_FUNCTIONAL);
  srunner_run_all(sr, CK_VERBOSE);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf;
}

// заполнение матрицы
void fill_matrix(matrix_t *A) {
  if (A->rows > 0 && A->columns > 0) {
    double f = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = f;
        f++;
      }
    }
  }
}

// заполнение матрицы
void fill_matrix_1(matrix_t *A, double n) {
  if (A->rows > 0 && A->columns > 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = n;
        n++;
      }
    }
  }
}

// заполнение матрицы числом
void fill_matrix_num(matrix_t *A, double n) {
  if (A->rows > 0 && A->columns > 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = n;
      }
    }
  }
}

// Создание единичной матрицы
matrix_t create_identity_matrix(int n) {
    int rows = n;
    int columns = n;
  matrix_t identity_matrix;
  s21_create_matrix(rows, columns, &identity_matrix);
  if (rows > 0 && columns > 0 && rows == columns) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (i == j) {
          identity_matrix.matrix[i][j] = 1;
        }
      }
    }
  } else {
  }
  return identity_matrix;
}

// // Печать матрицы
// void print_matrix(matrix_t *A) {
//   printf("\n");
//   if (A->rows > 0 && A->columns > 0) {
//     for (int i = 0; i < A->rows; i++) {
//       for (int j = 0; j < A->columns; j++) {
//         if (j != 0) printf("\t");
//         printf("%.8f", A->matrix[i][j]);
//       }
//       printf("\n");
//     }
//   }
// }

// Заполнение матрицы массивом
void fill_matrix_array(matrix_t *A, double *arr) {
  if (A->rows > 0 && A->columns > 0) {
    int it = 0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = arr[it];
        it++;
      }
    }
  }
}
