#include "s21_math.h"

long double s21_sin(double x)
{
    long double answer = 0;
    long double i = 1;
    long double sin = s21_fmod(x, 2 * S21_PI);
    long double q = sin;

    while (s21_fabs(q) > S21_EPS)
    {
        answer = answer + q;
        q = (-1) * q * (sin * sin) / ((2 * i + 1) * (2 * i));
        i++;
    }
    return answer;
}