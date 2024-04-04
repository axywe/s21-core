#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1

#define MAX_EXPR_LENGTH 256
#define OPERATOR_STACK_SIZE 100

typedef struct {
  char* data;
  int top;
} Stack;

void initStack(Stack* s);
int isEmpty(Stack* s);
void push(Stack* s, char item);
char pop(Stack* s);
char peek(Stack* s);
int precedence(char op);
int infixToPostfix(char* expr, char* output);
double calculatePostfix(char* postfix);
int isFunctionOrBracket(char c);
int isOperator(char c);
double smartCalc(char* expr);

#ifdef __cplusplus
}
#endif

#endif  // CALCULATOR_H
