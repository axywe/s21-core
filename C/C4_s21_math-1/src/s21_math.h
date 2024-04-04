#include <stdio.h>

#define S21_INF __builtin_huge_valf()
#define S21_NAN __builtin_nan("")
#define S21_PI 3.1415926535897932
#define S21_E 2.7
#define S21_EPS 1.e-26


int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);