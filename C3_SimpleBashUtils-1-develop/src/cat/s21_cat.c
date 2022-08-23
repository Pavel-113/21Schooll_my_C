#include <stdio.h>
#include <string.h>
#include "s21_cat.h"

int main(int argc, char *argv[]) {
    char GNU[6][20] = {"--show-all", "--number-nonblank", "--show-ends",
                    "--number", "--squeeze-blank", "--show-nonprinting"};
    int GNU_SUCESS = 0;
    FILE *fp;
    to_null();
    int ferror = 0;
    int file_found = 0;
    int argcount = 1;
    int ch;
    while (argcount < argc && ferror == 0) {
        int len = strlen(argv[argcount]);
        if (argv[argcount][0] == '-'  && file_found == 0) {
            if (argv[argcount][1] == '-') {
                int i = 0;
                while (i < 6) {
                    if (strcmp(argv[argcount], "--show-all") == 0) parse('A');
                    if (strcmp(argv[argcount], "--number-nonblank") == 0) parse('b');
                    if (strcmp(argv[argcount], "--show-ends") == 0) parse('E');
                    if (strcmp(argv[argcount], "--number") == 0) parse('n');
                    if (strcmp(argv[argcount], "--squeeze-blank") == 0) parse('s');
                    if (strcmp(argv[argcount], "--show-nonprinting") == 0) parse('v');
                    if (strcmp(argv[argcount], GNU[i]) == 0) {
                        GNU_SUCESS = 1;
                        break;
                    }
                    i++;
                }
                if (!GNU_SUCESS) {
                    ferror = -1;
                    fprintf(stderr, "cat: invalid option -- '%s'\n", argv[argcount]);
                    fprintf(stderr, "Try 'cat --help' for more information.\n");
                    break;
                }
            } else {
                char *option;
                int count = 1;
                while (count < len) {
                    if ((option = strchr(OPTIONS, argv[argcount][count])) != NULL)  {
                        parse(*option);
                    } else {
                        fprintf(stderr, "cat: invalid option -- '%c'\n", argv[argcount][count]);
                        fprintf(stderr, "Try 'cat --help' for more information.\n");
                        ferror = -1;
                        break;
                    }
                    count++;
                }
            }
        } else {
            file_found = 0;
        }
        argcount++;
        GNU_SUCESS = 0;
    }
    if (ferror != -1) {
        argcount = 1;
        int strnum = 1;
        int fopensuc = 0;
        int checkEND = 0;
        int fch;
        while (argcount < argc) {
            if (argv[argcount][0] != '-') {
                char *file_name = argv[argcount];
                fp = fopen(file_name, "r");
                if (fp == NULL) {
                    fprintf(stderr, "cat: %s: No such file or directory\n", file_name);
                } else {
                    fopensuc++;
                    ch = getc(fp);
                    if (feof(fp) != 0) {
                        // printf ("файл то пустой!\n");
                    } else {
                        if (fopensuc == 1) {
                            if (cat.data_n == 1) printf("%6d\t", strnum);
                            if (cat.data_b == 1 && ch == '\n') strnum = 0;
                            if (cat.data_b == 1 && ch != '\n') printf("%6d\t", strnum);
                        } else {
                            if (cat.data_n == 1 && fch == EOF) {
                                if (checkEND == 1) {
                                    printf("%6d\t", strnum);
                                } else {
                                    strnum--;
                                }
                            }
                            if (cat.data_b == 1 && fch == EOF) {
                                if (checkEND == 1) {
                                    if (ch != '\n') {
                                        strnum++;
                                        printf("%6d\t", strnum);
                                    }
                                } else {
                                }
                            }
                        }
                        if (cat.data_E == 1 && ch == '\n') printf("$");
                        if (cat.data_T == 1) ch = print_TAB(fp, ch);
                        printf("%c", ch);
                        while ((fch = getc(fp)) != EOF) {
                            if (!cat.data_b && ch == '\n') {
                                strnum++;
                            } else {
                                if (ch == '\n' && ch != fch) strnum++;
                            }
                            if (cat.data_s == 1) fch = print_s(fp, ch, fch);
                            if (cat.data_n == 1 || cat.data_b == 1) print_number(ch, fch, strnum);
                            if (cat.data_E == 1) print_LFD(fch);
                            if (cat.data_T == 1) fch = print_TAB(fp, fch);
                            ch = fch;
                            print_file(fch);
                        }
                        checkEND = 0;
                        checkEND = checkEnter(fp, fch, checkEND);
                        if (cat.data_n == 1 && cat.data_b == 0) strnum++;
                        fclose(fp);
                    }
                }
            }
            argcount++;
        }
    }
    return 0;
}

void to_null() {
    cat.data_v = 0;
    cat.data_E = 0;
    cat.data_T = 0;
    cat.data_b = 0;
    cat.data_s = 0;
    cat.data_n = 0;
}

int parse(char ach) {
    switch (ach) {
        case 'A':
            cat.data_v = 1;
            cat.data_E = 1;
            cat.data_T = 1;
            break;
        case 'b':
            cat.data_b = 1;
            break;
        case 'e':
            cat.data_v = 1;
            cat.data_E = 1;
            break;
        case 'E':
            cat.data_E = 1;
            break;
        case 'n':
            cat.data_n = 1;
            break;
        case 't':
            cat.data_v = 1;
            cat.data_T = 1;
            break;
        case 's':
            cat.data_s = 1;
            break;
        case 'T':
            cat.data_T = 1;
            break;
        case 'v':
            cat.data_v = 1;
            break;
    }
    return 0;
}

char print_s(FILE *fp, char a, char b) {
    if (a == '\n' && b == '\n') {
        int flag  = 0;
        long int i = ftell(fp);
        if (i == 2) {
        flag = 1;
        }
        while (b == '\n') {
            i = ftell(fp);
            b = getc(fp);
        }
        if (flag == 0) {
        fseek(fp, i - 1, SEEK_SET);
        b = getc(fp);
        }
    }
    return b;
}

char print_TAB(FILE *fp, char a) {
    while (a == '\t') {
        printf("^I");
        a = getc(fp);
    }
    return a;
}

void print_LFD(char a) {
    if (a == '\n') {
        printf("$");
    }
}

void print_number(char a, char b, int strnum) {
    if (cat.data_b == 0 && a == '\n') {
        printf("%6d\t", strnum);
    } else if (a == '\n' && a != b) {
        printf("%6d\t", strnum);
    }
}

void print_file(int a) {
    putchar(a);
}

int checkEnter(FILE *fp, int fch, int checkEND) {
    if (fch == EOF) {
        fseek(fp, -1, SEEK_END);
        fch = getc(fp);
        if (fch == '\n') {
            checkEND = 1;
        }
    }
    fseek(fp, 1, SEEK_END);
    fch = getc(fp);
    return checkEND;
}
