#include "s21_calc.h"

int get_priority(data_symbol tmp) {
  int priority = 0;
  switch (tmp.operation) {
    case '(':
      priority = -1;
      break;
    case ')':
      priority = -2;
      break;
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
  }
  return priority;
}

char to_struct(char *func, int *flag_err) {
  char func_code = '\0';
  if (strcmp(func, "cos") == 0) {
    func_code = 'c';
  } else if (strcmp(func, "sin") == 0) {
    func_code = 's';
  } else if (strcmp(func, "tan") == 0) {
    func_code = 't';
  } else if (strcmp(func, "acos") == 0) {
    func_code = 'o';
  } else if (strcmp(func, "asin") == 0) {
    func_code = 'i';
  } else if (strcmp(func, "atan") == 0) {
    func_code = 'a';
  } else if (strcmp(func, "sqrt") == 0) {
    func_code = 'q';
  } else if (strcmp(func, "ln") == 0) {
    func_code = 'n';
  } else if (strcmp(func, "log") == 0) {
    func_code = 'g';
  } else {
    printf("FUNCTION NAME ERROR: %s\n", func);
    *flag_err = ERROR;
  }
  return func_code;
}

data_symbol get_data(double value, int priority, char operation,
                     int data_type) {
  data_symbol tmp;
  tmp.value = value;
  tmp.priority = priority;
  tmp.operation = operation;
  tmp.data_type = data_type;
  return tmp;
}

int parse_function(char *str, int *i, stack_Node_s **head, int flag_err,
                   int flag_unary) {
  char func[256] = {"\0"};
  int j = 0;
  if (flag_unary == 1) {
    push_Back(head, get_data(-1, 0, '\0', NUMBERS));
    push_Back(head, get_data(0, 2, '*', OPERATION));
  }
  while (strchr(SET_TRIG, str[*i]) != NULL) {
    func[j] = str[*i];
    (*i)++;
    j++;
  }
  if (str[*i] == '(') {
    push_Back(head, get_data(0, 4, to_struct(func, &flag_err), FUNCTIONS));
  } else {
    flag_err = 1;
    printf("MISSING \"(\": %s\n", func);
  }
  return flag_err;
}

int parse_operation(const char *str, int *i, int *bracket, stack_Node_s **head,
                    int flag_err) {
  char sign = 0;
  if (str[*i] == '(') (*bracket)++;
  if (str[*i] == ')') (*bracket)--;
  if (*bracket < 0) {
    printf("BRACKET ARE INCORRECTLY PLACED\n");
    flag_err = ERROR;
  }
  sign = str[*i];
  (*i)++;

  data_symbol tmp = get_data(0, 0, sign, OPERATION);
  tmp.priority = get_priority(tmp);
  push_Back(head, tmp);
  return flag_err;
}

void parse_number(char *str, int *i, int flag_unary, stack_Node_s **head) {
  data_symbol tmp;
  char buff[256] = {"\0"};
  int j = 0;
  if (flag_unary == 1) {
    buff[j] = str[(*i) - 1];
    j++;
  }
  int count_dot = 0;
  while (strchr(SET_NUM, str[*i]) != NULL) {
    buff[j] = str[*i];
    if (buff[j] == '.') count_dot++;
    j++;
    (*i)++;
  }
  double res = 0.0;
  sscanf(buff, "%lf", &res);
  if (count_dot > 1) {
    res = NAN;
  }
  tmp.data_type = NUMBERS;
  tmp.value = res;
  tmp.operation = 'd';
  tmp.priority = 0;
  push_Back(head, tmp);
}

void parse_variable(int *i, stack_Node_s **head, int flag_unary) {
  if (flag_unary == 1) {
    push_Back(head, get_data(-1, 0, '\0', NUMBERS));
    push_Back(head, get_data(0, 2, '*', OPERATION));
  }
  push_Back(head, get_data(0, 0, 'x', VARIABLE));
  (*i)++;
}

void parse_mod(int *i, stack_Node_s **head) {
  (*i) += 3;
  push_Back(head, get_data(0, 3, 'm', OPERATION));
}

int parser(stack_Node_s **head, char *str) {
  int len = strlen(str) - 1;
  int i = 0;
  int bracket = 0;
  int flag_err = 0;
  while (i <= len && flag_err == 0) {
    int flag_unary = 0;
    if (strchr(" ", str[i]) != NULL) {
      i++;
    }
    if ((i == 0 && str[i] == '-') ||
        (i > 0 && str[i - 1] == '(' && str[i] == '-')) {
      i++;
      flag_unary = 1;
    }
    if ((i == 0 && str[i] == '+') ||
        (i > 0 && str[i - 1] == '(' && str[i] == '+')) {
      i++;
    }
    if (strchr(SET_NUM, str[i]) != NULL) {
      parse_number(str, &i, flag_unary, head);
    } else if (strchr(SET_SIGN, str[i]) != NULL) {
      flag_err = parse_operation(str, &i, &bracket, head, flag_err);
    } else if (strchr(SET_TRIG, str[i]) != NULL) {
      flag_err = parse_function(str, &i, head, flag_err, flag_unary);
    } else if (strchr("x", str[i]) != NULL) {
      parse_variable(&i, head, flag_unary);
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      parse_mod(&i, head);
    } else {
      flag_err = ERROR;
      printf("INCORRECT EXPRESSION\n");
    }
  }
  if (bracket != 0) {
    printf("BRACKET ARE INCORRECTLY PLACED\n");
    flag_err = ERROR;
  }
  return flag_err;
}
