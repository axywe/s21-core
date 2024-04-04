#include "s21_math.h"

long double s21_floor(double x)
{
    long double answer = (long long int)x;
    return (answer <= x ? answer : answer - 1);
}