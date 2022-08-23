#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define OPTIONS "ivclnhso"
#define EF "ef"
#define MAX_SIZE 1024
#define MIN_SIZE 24

struct s21_grep {
  int data_e;
  int data_i;
  int data_v;
  int data_c;
  int data_l;
  int data_n;
  int data_h;
  int data_s;
  int data_f;
  int data_o;
} grep;

void option_case(char a);
void null_option();
void squeeze(char s[], int c);
void inverts(int file_count, char *file_name, int number, char *buff);
void search(int file_count, char *file_name, int number, char *buff);
void search_o(pcre *re, int file_count, int count, int count_c,
              char *file_name, int number, char *buff, int *ovector);
void opt_cl(int file_count, int count_c, int count_vc, char *file_name);


#endif  // SRC_GREP_S21_GREP_H_
