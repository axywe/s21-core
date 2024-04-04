#include "s21_math.h"

long double s21_cos(double x) {
    x = s21_fmod(x, 2 * S21_PI);
    
    long double sin = s21_sin(x);

    long double cos = s21_sqrt(1 - sin * sin);

    // Я максимально не уверен в том, насколько это правильно
    if ((x > S21_PI / 2 && x < 3 * S21_PI / 2)) {
        cos = -cos;
    }

    return cos;
}