#ifndef S21_TEST_TESTS_H_
#define S21_TEST_TESTS_H_

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "calculator.h"

#define BUFFER 256

Suite *suite_smartcalc(void);

void run_test(void);
void run_testcase(Suite *testcase);
double get_rand(double min, double max);

#endif  // S21_TEST_TESTS_H_