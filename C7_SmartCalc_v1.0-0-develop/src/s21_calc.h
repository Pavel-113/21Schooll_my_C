#ifndef SRC_S21_CALC_H_
#define SRC_S21_CALC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

// setlocale( LC_ALL, "en-US" );

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102

#define SET_NUM "0123456789."
#define SET_SIGN "+-*/^()"
#define SET_TRIG "sincotaqrlg"

#define ERROR 1
#define STR_MAX 256

typedef enum {
  NUMBERS = 0,
  OPERATION = 1,
  FUNCTIONS = 2,
  VARIABLE = 3
} symbol_type;

typedef struct data_symbol {
  double value;
  char operation;
  int priority;
  symbol_type data_type;
} data_symbol;

typedef struct node_tag {
  data_symbol value;
  struct node_tag *next;
} stack_Node_s;

void push(stack_Node_s **head, data_symbol value);
data_symbol pop(stack_Node_s **head);
data_symbol peek(const stack_Node_s *head);
size_t getSize(const stack_Node_s *head);
stack_Node_s *clean_Node(stack_Node_s **head);
void push_Back(stack_Node_s **head, data_symbol value);
void revers(stack_Node_s **tmp, stack_Node_s **head);
void print_Node_s_data(data_symbol data);
void printStack(const stack_Node_s *head);

int get_priority(data_symbol tmp);
char to_struct(char *func, int *flag_err);
int parse_function(char *str, int *i, stack_Node_s **head, int flag_err, int flag_unary);
int parse_operation(const char *str, int *i, int *bracket, stack_Node_s **head, int flag_err);
void parse_number(char *str, int *i, int flag_unary, stack_Node_s **head);
void parse_variable(int *i, stack_Node_s **head, int flag_unary);
void parse_mod(int *i, stack_Node_s **head);
int parser(stack_Node_s **head, char *str);

stack_Node_s *get_polish(stack_Node_s *head);

double calc_function(double n, char func);
double calc_operation(double n1, double n2, char oper);
double expression_calc(stack_Node_s *input_stack, double x, int *flag_err);
double get_result(char *str, double x);

#endif  // SRC_S21_CALC_H_
