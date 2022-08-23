#include "s21_calc.h"

stack_Node_s *get_polish(stack_Node_s *head) {
  stack_Node_s *out_stack = NULL;
  stack_Node_s *revers_stack = NULL;
  stack_Node_s *tmp = NULL;
  while (head != NULL) {
  data_symbol upper = pop(&head);
    if (upper.data_type == NUMBERS || upper.data_type == VARIABLE) {
      push(&out_stack, upper);
    } else if (upper.data_type == FUNCTIONS) {
      push(&tmp, upper);


    } else if (upper.data_type == OPERATION && upper.priority >= 0) {
      if (tmp != NULL) {
        while (tmp != NULL &&
               tmp->value.priority >= upper.priority) {
          push(&out_stack, pop(&tmp));
        }
        push(&tmp, upper);
      } else {
        push(&tmp, upper);
      }


    } else if (upper.operation == '(') {
      push(&tmp, upper);
    } else if (upper.operation == ')') {
      if (tmp != NULL) {
        while (tmp != NULL &&
               tmp->value.operation != '(') {
          push(&out_stack, pop(&tmp));
        }
        if (tmp != NULL &&
            tmp->value.operation == '(') {
                   pop(&tmp);
        }
        if (tmp != NULL &&
            tmp->value.data_type == FUNCTIONS) {
          push(&out_stack, pop(&tmp));
        }
      }
    }
  }


  while (tmp != NULL) {
    if (tmp->value.operation == '(') {
      printf("MISSING BRACKET\n");
    }
    push(&out_stack, pop(&tmp));
  }


  revers(&revers_stack, &out_stack);
  return revers_stack;
}
