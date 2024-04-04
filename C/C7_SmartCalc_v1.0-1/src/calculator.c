#ifdef __cplusplus
extern "C" {
#endif

#include "calculator.h"

int isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
         ch == '%';
}

int isFunctionOrBracket(char ch) { return isalpha(ch) || ch == '('; }

int precedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '^':
      return 3;
    default:
      return -1;
  }
}

int isPartOfNumber(char ch) { return isdigit(ch) || ch == '.'; }

int infixToPostfix(char* expr, char* output) {
  Stack operators;
  initStack(&operators);
  int j = 0;
  int wasOperator =
      1;  // Assume starting with an operator (for unary minus at the start)

  for (int i = 0; expr[i]; i++) {
    if (isPartOfNumber(expr[i])) {
      wasOperator = 0;
      while (isPartOfNumber(expr[i])) {
        output[j++] = expr[i++];
      }
      output[j++] = ' ';  // Add a space to separate numbers
      i--;                // Adjust for the increment in the loop
    } else if (isFunctionOrBracket(expr[i])) {
      wasOperator = 1;
      push(&operators, expr[i]);
    } else if (expr[i] == ',') {
      while (!isEmpty(&operators) && peek(&operators) != '(') {
        output[j++] = pop(&operators);
        output[j++] = ' ';  // Add a space for clarity
      }
    } else if (isOperator(expr[i])) {
      if (expr[i] == '-' && wasOperator) {
        // Handle unary minus
        push(&operators, 'u');  // Use 'u' to represent unary minus
      } else {
        while (!isEmpty(&operators) && isOperator(peek(&operators)) &&
               (precedence(peek(&operators)) >= precedence(expr[i]))) {
          output[j++] = pop(&operators);
          output[j++] = ' ';  // Add a space for clarity
        }
        push(&operators, expr[i]);
      }
      wasOperator = 1;
    } else if (expr[i] == ')') {
      while (!isEmpty(&operators) && peek(&operators) != '(') {
        output[j++] = pop(&operators);
        output[j++] = ' ';  // Add a space for clarity
      }
      pop(&operators);  // Remove '(' from stack
      if (!isEmpty(&operators) && isalpha(peek(&operators))) {
        output[j++] = pop(&operators);  // Pop function
        output[j++] = ' ';              // Add a space for clarity
      }
      wasOperator = 0;  // Closing bracket is not an operator, allows for unary
                        // minus after ")"
    }
  }

  while (!isEmpty(&operators)) {
    if (peek(&operators) == '(' || peek(&operators) == ')') {
      printf("Error: Mismatched parentheses\n");
      return FAILURE;
    }
    output[j++] = pop(&operators);
    output[j++] = ' ';  // Add a space for clarity
  }

  if (j > 0 && output[j - 1] == ' ') {
    output[j - 1] = '\0';  // Remove the last space and end the string
  } else {
    output[j] = '\0';  // Null-terminate the output string
  }
  return SUCCESS;
}

double calculatePostfix(char* postfix) {
  double stack[1000];
  int top = -1;
  char* token = strtok(postfix, " ");
  double a, b;

  while (token != NULL) {
    if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
      stack[++top] = atof(token);
    } else {
      switch (token[0]) {
        case '+':
          b = stack[top--];
          a = stack[top--];
          stack[++top] = a + b;
          break;
        case '-':
          b = stack[top--];
          a = stack[top--];
          stack[++top] = a - b;
          break;
        case '*':
          b = stack[top--];
          a = stack[top--];
          stack[++top] = a * b;
          break;
        case '/':
          b = stack[top--];
          a = stack[top--];
          if (b == 0)
            return -2000000000;  // Error handling for division by zero
          stack[++top] = a / b;
          break;
        case '^':
          b = stack[top--];
          a = stack[top--];
          stack[++top] = pow(a, b);
          break;
        case '%':
          b = stack[top--];
          a = stack[top--];
          stack[++top] = (int)a % (int)b;
          break;
        case 's':
          // sin(cos(tan(asin(acos(atan(ln(log10(sqrt(^(()
          // s = sin, c = cos, t = tan, n = ln, q = sqrt, l = log10, d = asin, f
          // = acos, g = atan
          stack[top] = sin(stack[top]);
          break;
        case 'c':
          stack[top] = cos(stack[top]);
          break;
        case 't':
          stack[top] = tan(stack[top]);
          break;
        case 'n':
          stack[top] = log(stack[top]);
          break;
        case 'q':
          stack[top] = sqrt(stack[top]);
          break;
        case 'l':
          stack[top] = log10(stack[top]);
          break;
        case 'd':
          stack[top] = asin(stack[top]);
          break;
        case 'f':
          stack[top] = acos(stack[top]);
          break;
        case 'g':
          stack[top] = atan(stack[top]);
          break;
        case 'u':
          stack[top] = -stack[top];
          break;
        default:  // Error handling for unknown operator
          return -2000000001;
      }
    }
    token = strtok(NULL, " ");
  }
  return stack[top];
}

double smartCalc(char* expr) {
  char output[MAX_EXPR_LENGTH];
  int res = infixToPostfix(expr, output);
  double result = calculatePostfix(output);
  return result;
}

// int main() {
//     char expr[MAX_EXPR_LENGTH] = "3 + 4 * 2.0 / (1 - 5)^(32 % 26)";
//     char output[MAX_EXPR_LENGTH];

//     int res = infixToPostfix(expr, output);
//     if(res != SUCCESS){
//         return res;
//     }
//     printf("Postfix: %s\n", output);
//     double result = calculatePostfix(output);
//     if(result == -2000000001){
//         printf("Error: Invalid expression\n");
//         return FAILURE;
//     }else if(result == -2000000000){
//         printf("Error: Division by zero\n");
//         return FAILURE;
//     }
//     printf("Result: %s = %lf. Real result - %lf.\n", expr, result, 3 + 4
//     * 2.0 / pow(1 - 5, fmod(32, 26)));

//     return 0;
// }

#ifdef __cplusplus
}
#endif
