#ifdef __cplusplus
extern "C" {
#endif

#include "calculator.h"

void initStack(Stack* s) {
  s->data = (char*)malloc(MAX_EXPR_LENGTH * sizeof(char));
  s->top = -1;
}

int isEmpty(Stack* s) { return s->top == -1; }

void push(Stack* s, char item) {
  if (s->top < (MAX_EXPR_LENGTH - 1)) {
    s->data[++s->top] = item;
  }
}

char pop(Stack* s) {
  if (!isEmpty(s)) {
    return s->data[s->top--];
  }
  return '\0';  // Return null character if stack is empty
}

char peek(Stack* s) {
  if (!isEmpty(s)) {
    return s->data[s->top];
  }
  return '\0';  // Return null character if stack is empty
}

#ifdef __cplusplus
}
#endif
