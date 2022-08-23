#include "s21_calc.h"

double get_result(char *str, double x) {
  setlocale(LC_ALL, "en_US.UTF-8");
  stack_Node_s *tmp = NULL;
  int flag_err = parser(&tmp, str);
  stack_Node_s *result_stack = get_polish(tmp);
  double result = expression_calc(result_stack, x, &flag_err);
  clean_Node(&result_stack);
  if (flag_err == ERROR) {result = NAN;}
  return result;
}

double expression_calc(stack_Node_s *input_stack, double x, int *flag_err) {
  stack_Node_s *calc_stack = NULL;
  stack_Node_s *ptr = input_stack;
  data_symbol res;
  double result = 0.0, num1 = 0.0, num2 = 0.0;
  while (ptr != NULL && *flag_err != ERROR) {
    switch (ptr->value.data_type) {
      case NUMBERS:
        push(&calc_stack, ptr->value);
        break;
      case VARIABLE:
        ptr->value.value = x;
        ptr->value.data_type = NUMBERS;
        push(&calc_stack, ptr->value);
        break;
      case OPERATION:
        if (calc_stack != NULL && calc_stack->value.data_type == NUMBERS) {
          num1 = pop(&calc_stack).value;
          if (calc_stack != NULL && calc_stack->value.data_type == NUMBERS) {
            num2 = pop(&calc_stack).value;
            res.data_type = NUMBERS;
            res.value = calc_operation(num1, num2, ptr->value.operation);
            push(&calc_stack, res);
          } else {
            *flag_err = ERROR;
            break;
          }
        } else {
          *flag_err = ERROR;
          break;
        }
        break;
      case FUNCTIONS:
        if (calc_stack != NULL && calc_stack->value.data_type == NUMBERS) {
          num1 = pop(&calc_stack).value;
        } else {
          *flag_err = ERROR;
          break;
        }
        res.data_type = NUMBERS;
        res.value = calc_function(num1, ptr->value.operation);
        push(&calc_stack, res);
        break;
    }
    ptr = ptr->next;
  }
  if (calc_stack != NULL && *flag_err != ERROR &&
      calc_stack->value.data_type == NUMBERS) {
    result = pop(&calc_stack).value;
    if (calc_stack != NULL) {
      *flag_err = ERROR;
    }
  } else {
    *flag_err = ERROR;
  }
  return result;
}

double calc_operation(double n1, double n2, char oper) {
  double res = 0.0;
  switch (oper) {
    case '+':
      res = n2 + n1;
      break;
    case '-':
      res = n2 - n1;
      break;
    case '*':
      res = n2 * n1;
      break;
    case '/':
      res = n2 / n1;
      break;
    case '^':
      res = pow(n2, n1);
      break;
    case 'm':
      res = fmod(n2, n1);
      break;
  }
  return res;
}

double calc_function(double n, char func) {
  double res = 0.0;
  switch (func) {
    case 'c':
      res = cos(n);
      break;
    case 's':
      res = sin(n);
      break;
    case 't':
      res = tan(n);
      break;
    case 'o':
      res = acos(n);
      break;
    case 'i':
      res = asin(n);
      break;
    case 'a':
      res = atan(n);
      break;
    case 'q':
      res = sqrt(n);
      break;
    case 'n':
      res = log(n);
      break;
    case 'g':
      res = log10(n);
      break;
  }
  return res;
}
