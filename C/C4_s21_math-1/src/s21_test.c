#include "s21_math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int zero = -5;
    int num = -10;
    double dnum = -1.9456451;
    printf("ABS %d: %d %d %s\n", num, s21_abs(num), abs(num), s21_abs(num)==abs(num)?"Test passed":"Test failed");
    printf("Floor %f: %Lf %f %s\n", dnum, s21_floor(dnum), floor(dnum), s21_floor(dnum)==floor(dnum)?"Test passed":"Test failed");
    printf("Sin %f : %Lf %f %s\n", dnum, s21_sin(dnum), sin(dnum), s21_sin(dnum)==sin(dnum)?"Test passed":"Test failed");
    printf("Cos %f : %Lf %f %s\n", dnum, s21_cos(dnum), cos(dnum), s21_cos(dnum)==cos(dnum)?"Test passed":"Test failed");
    printf("Sqrt %f : %Lf %f %s\n", zero, s21_sqrt(zero), sqrt(zero), s21_sqrt(zero)==sqrt(zero)?"Test passed":"Test failed");
    printf("Tan %f : %Lf %f %s\n", zero, s21_tan(zero), tan(zero), s21_tan(zero)==tan(zero)?"Test passed":"Test failed");
    return 0;
}