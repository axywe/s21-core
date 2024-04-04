#include "tests.h"

START_TEST(TEST_1) {
  double result;
  char str[BUFFER] = "--(-3)";
  result = smartCalc(str);
  ck_assert_int_eq(-3.0, result);
}
END_TEST

START_TEST(TEST_2) {
  double result;
  char str[BUFFER] = "3 + 4 * 2.0 / (1 - 5)^(32 % 26)";
  result = smartCalc(str);
  ck_assert_float_eq(3 + 4 * 2.0 / pow(1 - 5, fmod(32, 26)), result);
}
END_TEST

START_TEST(TEST_3) {
  double result;
  char str[BUFFER] = "(2+7)/(1+3)-4*(6-2)+t(1)";
  result = smartCalc(str);
  ck_assert_float_eq((2.0 + 7) / (1 + 3) - 4 * (6 - 2) + tan(1), result);
}
END_TEST

START_TEST(TEST_4) {
  double result;
  char str[BUFFER] = "s(c(l(n(f(0)))))";
  result = smartCalc(str);
  ck_assert_float_eq(sin(cos(log10(log(acos(0))))), result);
}
END_TEST

START_TEST(TEST_5) {
  double result;
  char str[BUFFER] = "s(1) + (-s(1)) + 1 % 2";
  result = smartCalc(str);
  ck_assert_float_eq(sin(1) + (-sin(1) + 1 % 2), result);
}
END_TEST

// START_TEST(TEST_6) {
//   double result, result_true;
//   char str[BUFFER] = "n(1.2%0.00345+q(3.1415*l(-0.12300001)))";
//   result = isnan(smartCalc(str));
//   result_true =
//       isnan(log(fmod(1.2, 0.00345) + sqrt(3.1415 * log10(-0.12300001))));
//   ck_assert_float_eq(result, result_true);
// }
// END_TEST

// START_TEST(TEST_7) {
//   double result;
//   char str[BUFFER] = "2..2";
//   result = smartCalc(str);
//   ck_assert_float_eq(isnan(result), 1);
// }
// END_TEST

Suite *suite_smartcalc(void) {
  Suite *s = suite_create("suite_smartcalc");
  TCase *tc = tcase_create("suite_smartcalc");

  tcase_add_test(tc, TEST_1);
  tcase_add_test(tc, TEST_2);
  tcase_add_test(tc, TEST_3);
  tcase_add_test(tc, TEST_4);
  tcase_add_test(tc, TEST_5);
  suite_add_tcase(s, tc);
  return s;
}

// START_TEST(several_another_functions) {
//   char lexeme[256] = "ln(1.2mod0.00345+sqrt(3.1415*(-log(0.12300001))))";
//   double result = 0., expected_result = 0.;
//   int error = 0;

//   error = calculate(lexeme, &result, 0.);
//   expected_result =
//       log(fmod(1.2, 0.00345) + sqrt(3.1415 * (-log10(0.12300001))));
//   ck_assert_int_eq(0, error);
//   ck_assert_ldouble_eq_tol(result, expected_result, 0.0000001);

//   sprintf(lexeme,
//           "-ln(1.2mod(sin(0.005)*0.00345)+sqrt(3.1415*(-log(0.12300001))))");
//   error = calculate(lexeme, &result, 0.);
//   expected_result = -log(fmod(1.2, sin(0.005) * 0.00345) +
//                          sqrt(3.1415 * (-log10(0.12300001))));
//   ck_assert_int_eq(0, error);
//   ck_assert_ldouble_eq_tol(result, expected_result, 0.0000001);
// }
// END_TEST

void run_tests(void) {
  Suite *list_cases[] = {suite_smartcalc(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  printf("%s%d%s", "TEST ", counter_testcase, "\n");
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_tests();
  return 0;
}