#include "s21_math.h"

long double s21_pow(double base, double exp){
    // fix exp
    long double result = (long double)base;
    for(int i=0;i<exp;i++){
        result *= base;
    }
    return result;
}