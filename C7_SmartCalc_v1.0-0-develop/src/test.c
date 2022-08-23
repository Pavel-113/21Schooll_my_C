#include <check.h>

#include "s21_calc.h"

START_TEST(case_1) {
  char expression[255] = "499.1 + 500.9";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 1000.0, 1e-7);
}
END_TEST

START_TEST(case_2) {
  char expression[255] = "-0.5*x+(-1*(-x)+2)";
  double x = 1;
  double result = get_result(expression, x);
  ck_assert_double_eq_tol(result, 2.5, 1e-7);
}
END_TEST

START_TEST(case_3) {
  char expression[255] = "-0.9 + (-770.1)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -771.0, 1e-7);
}
END_TEST

START_TEST(case_4) {
  char expression[255] = "-2.12345 - 10.000003";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -12.123453, 1e-7);
}
END_TEST

START_TEST(case_5) {
  char expression[255] = "-2.78941 - (-95.258964)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 92.469554, 1e-7);
}
END_TEST

START_TEST(case_6) {
  char expression[255] = "10000 - (-2249.654684)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 12249.654684, 1e-7);
}
END_TEST

START_TEST(case_7) {
  char expression[255] = "123.4 * 567.8";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 70066.52, 1e-7);
}
END_TEST

START_TEST(case_8) {
  char expression[255] = "-1.2 * (-345.6)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 414.72, 1e-7);
}
END_TEST

START_TEST(case_9) {
  char expression[255] = "-2.7984651 * 10000000";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -27984651, 1e-7);
}
END_TEST

START_TEST(case_10) {
  char expression[255] = "10 mod 3";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 1, 1e-7);
}
END_TEST

START_TEST(case_11) {
  char expression[255] = "25 / 5";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 5, 1e-7);
}
END_TEST

START_TEST(case_12) {
  char expression[255] = "2^9";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 512, 1e-7);
}
END_TEST

START_TEST(case_13) {
  char expression[255] = "cos(1)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.5403023, 1e-7);
}
END_TEST

START_TEST(case_14) {
  char expression[255] = "cos(30)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.1542514, 1e-7);
}
END_TEST

START_TEST(case_15) {
  char expression[255] = "sin(45)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.8509035, 1e-7);
}
END_TEST

START_TEST(case_16) {
  char expression[255] = "tan(90)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -1.9952004, 1e-7);
}
END_TEST

START_TEST(case_17) {
  char expression[255] = "acos(-0.3)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 1.8754889, 1e-7);
}
END_TEST

START_TEST(case_18) {
  char expression[255] = "asin(0.5)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.5235987, 1e-7);
}
END_TEST

START_TEST(case_19) {
  char expression[255] = "atan(1)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.7853981, 1e-7);
}
END_TEST

START_TEST(case_20) {
  char expression[255] = "sqrt(25)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 5, 1e-7);
}
END_TEST

START_TEST(case_21) {
  char expression[255] = "ln(99)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 4.5951198, 1e-7);
}
END_TEST

START_TEST(case_22) {
  char expression[255] = "log(100)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 2, 1e-7);
}
END_TEST

START_TEST(case_23) {
  char expression[255] = "sin(x)^2+cos(x)^2";
  double x = 1;
  double result = get_result(expression, x);
  ck_assert_double_eq_tol(result, 1.0, 1e-7);
}
END_TEST

START_TEST(case_24) {
  char expression[255] =
      "(-0.5 - 0.375) / 1/8 - (-9.125 * (-0.21)) + (345000125 - 315752568) / "
      "(-458.3258)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -63815.9261298, 1e-7);
}
END_TEST

START_TEST(case_25) {
  char expression[255] = "(17*1/5*0.125-(2*32/45-1/7/60))*(11/40/4*7/12+2.64)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -2.66627823247, 1e-7);
}
END_TEST

START_TEST(case_26) {
  char expression[255] = "log(2) + (-1/2) * log(8) - ln(4 * sqrt(8))";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -2.57653012979, 1e-7);
}
END_TEST
START_TEST(case_27) {
  char expression[255] =
      "(cos(70)+cos(50))*(cos(310)+cos(290))-(sin(-40)+sin(-60))";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.49956901475, 1e-7);
}

START_TEST(case_28) {
  char expression[255] = "sin(cos(ln(sqrt(4))))";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.69558863622, 1e-7);
}
END_TEST

START_TEST(case_29) {
  char expression[255] = "-2.0/(-6.0)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.33333333, 1e-7);
}
END_TEST

START_TEST(case_30) {
  char expression[255] =
      "tan(-85)*tan(15)+asin(0.8)-acos(1)/"
      "atan(0.5)+acos(-0.3)+asin(-0.7)*atan(-0.5)";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 3.31540708, 1e-7);
}
END_TEST

START_TEST(case_31) {
  char expression[255] = "(2^8 + 2^(-5))*(sqrt(144)/(-2))";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, -1536.1875, 1e-7);
}
END_TEST

START_TEST(case_32) {
  char expression[255] =
      "((4.625-13/18*9/26) / 2*0.25 +2*0.5 / 1.25 / 6*3/4) / 53/68";
  double result = get_result(expression, 0);
  ck_assert_double_eq_tol(result, 0.00017948806, 1e-7);
}
END_TEST

START_TEST(case_33) {
  char expression[255] = "(x^2+x^3+x^4+x^5+x^6+x^7+x^8+x^9)*5/(sqrt(900))";
  double x = 2;
  double result = get_result(expression, x);
  ck_assert_double_eq_tol(result, 170.0, 1e-7);
}
END_TEST

START_TEST(case_34) {
  char expression[255] = "(x^  e";
  double x = 2;
  double result = get_result(expression, x);
  ck_assert_double_nan(result);
}
END_TEST

START_TEST(case_35) {
  char expression[255] = "sin((((()()()()91)";
  double result = get_result(expression, 0);
  ck_assert_double_nan(result);
}
END_TEST


Suite *smartcalc_test() {
  Suite *s = suite_create("Calculator tests");
  TCase *tc_1 = tcase_create("calc tests");

  suite_add_tcase(s, tc_1);
  tcase_add_test(tc_1, case_1);
  tcase_add_test(tc_1, case_2);
  tcase_add_test(tc_1, case_3);
  tcase_add_test(tc_1, case_4);
  tcase_add_test(tc_1, case_5);
  tcase_add_test(tc_1, case_6);
  tcase_add_test(tc_1, case_7);
  tcase_add_test(tc_1, case_8);
  tcase_add_test(tc_1, case_9);
  tcase_add_test(tc_1, case_10);
  tcase_add_test(tc_1, case_11);
  tcase_add_test(tc_1, case_12);
  tcase_add_test(tc_1, case_13);
  tcase_add_test(tc_1, case_14);
  tcase_add_test(tc_1, case_15);
  tcase_add_test(tc_1, case_16);
  tcase_add_test(tc_1, case_17);
  tcase_add_test(tc_1, case_18);
  tcase_add_test(tc_1, case_19);
  tcase_add_test(tc_1, case_20);
  tcase_add_test(tc_1, case_21);
  tcase_add_test(tc_1, case_22);
  tcase_add_test(tc_1, case_23);
  tcase_add_test(tc_1, case_24);
  tcase_add_test(tc_1, case_25);
  tcase_add_test(tc_1, case_26);
  tcase_add_test(tc_1, case_27);
  tcase_add_test(tc_1, case_28);
  tcase_add_test(tc_1, case_29);
  tcase_add_test(tc_1, case_30);
  tcase_add_test(tc_1, case_31);
  tcase_add_test(tc_1, case_32);
  tcase_add_test(tc_1, case_33);
  tcase_add_test(tc_1, case_34);
  tcase_add_test(tc_1, case_35);

  return s;
}

int main(void) {
  int nf = 0;
  Suite *s = smartcalc_test();

  SRunner *sr1 = srunner_create(s);

  srunner_run_all(sr1, CK_VERBOSE);  // CK_VERBOSE
  nf += srunner_ntests_failed(sr1);
  srunner_free(sr1);

  return nf == 0 ? 0 : 1;
}
