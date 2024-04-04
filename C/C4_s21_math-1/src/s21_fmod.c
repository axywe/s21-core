#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double answer = 0;
  if (x == 0.0 && y != 0) {
    answer = 0.0;
  } else {
    if (x < 0 || y < 0)
      answer = -s21_abs(x / y);
    else
      answer = s21_abs(x / y);
    answer = x - answer * y;
  }
  return answer;
}