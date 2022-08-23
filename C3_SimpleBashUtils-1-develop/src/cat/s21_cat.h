#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#define OPTIONS "AbeEnstTuv"

struct s21_cat {
    int data_A;
    int data_b;
    int data_e;
    int data_E;
    int data_n;
    int data_s;
    int data_t;
    int data_T;
    int data_u;
    int data_v;
} cat;

void to_null();
int parse(char ach);
char print_s(FILE *fp, char a, char b);
char print_TAB(FILE *fp, char a);
void print_LFD(char a);
void print_number(char a, char b, int strnum);
void print_file(int a);
int checkEnter(FILE *fp, int fch, int checkEND);

#endif  // SRC_CAT_S21_CAT_H_
