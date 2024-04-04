#include "s21_math.h"

long double s21_sqrt(double x){
  if(x == 0) return 0;
  else if(x<0) return S21_NAN;
  long double z = 1.0;
  for(int i = 1; i <= 1000; i++) {
    z -= (z*z - x) / (2*z);
  }
  return z;
}