#include "s21_calc.h"

void push(stack_Node_s **head, data_symbol value) {
  stack_Node_s *tmp = malloc(sizeof(stack_Node_s));
  if (tmp == NULL) {
    printf("push error\n");
    exit(STACK_OVERFLOW);
  }
  tmp->next = *head;
  tmp->value = value;
  *head = tmp;
}

data_symbol pop(stack_Node_s **head) {
  stack_Node_s *out;
  data_symbol value;
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
  return value;
}

stack_Node_s *clean_Node(stack_Node_s **head) {
  while (*head != NULL) {
    stack_Node_s *out = *head;
    *head = (*head)->next;
    free(out);
  }
  *head = NULL;
  return *head;
}

void push_Back(stack_Node_s **head, data_symbol value) {
  stack_Node_s *tmp = malloc(sizeof(stack_Node_s));
  tmp->value = value;
  tmp->next = NULL;
  if (*head == NULL) {
    *head = tmp;
  } else {
    stack_Node_s *ptr = *head;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = tmp;
  }
}

void revers(stack_Node_s **tmp, stack_Node_s **head) {
  while (*head != NULL) {
    push(tmp, pop(head));
  }
}

// void print_Node_s_data(data_symbol data) {
//   switch (data.data_type) {
//     case NUMBERS:
//       printf("%.2f", data.value);
//       break;
//     case OPERATION:
//       if (data.operation == 'm') {
//         printf("mod");
//       } else {
//         printf("%c", data.operation);
//       }
//       break;
//     case FUNCTIONS:
//       switch (data.operation) {
//         case 'c':
//           printf("cos");
//           break;
//         case 's':
//           printf("sin");
//           break;
//         case 't':
//           printf("tan");
//           break;
//         case 'o':
//           printf("acos");
//           break;
//         case 'i':
//           printf("asin");
//           break;
//         case 'a':
//           printf("atan");
//           break;
//         case 'q':
//           printf("sqrt");
//           break;
//         case 'n':
//           printf("ln");
//           break;
//         case 'g':
//           printf("log");
//           break;
//       }
//       break;
//     case VARIABLE:
//       printf("%c", data.operation);
//     default:
//       break;
//   }
// }

// void printStack(const stack_Node_s *head) {
//   while (head) {
//     print_Node_s_data(head->value);
//     printf(" \t\t#%d", head->value.priority);
//     printf(" \t\t#%c", head->value.operation);
//     printf(" \t\t#%.2f", head->value.value);
//     printf("\n");
//     head = head->next;
//   }
// }
