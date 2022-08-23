#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s21_grep.h"

int main(int argc, char *argv[]) {
  FILE *fp;
  null_option();
  char *estr;
  char buff[MAX_SIZE];
  int count_arg = 1;
  int pattern_swich = 0;
  char pattern[MAX_SIZE] = {'\0'};
  char file_pattern[MAX_SIZE] = {'\0'};
  char *ptr_file_pattern = file_pattern;
  char file_name[MAX_SIZE] = {'\0'};
  char *ptr_file = file_name;
  pcre *re;
  int options = 0;
  const char *error;
  int erroffset;
  char stick[MIN_SIZE] = "|";
  int file_count = 0;
  int ferror = 0;
  while (count_arg < argc && ferror == 0) {
    int len = strlen(argv[count_arg]);
    if (*argv[count_arg] == '-') {
      argv[count_arg]++;
      while (*argv[count_arg]) {
        char *option;
        if ((option = strchr(OPTIONS, *argv[count_arg])) != NULL) {
          option_case(*option);
        } else if (((option = strchr(EF, *argv[count_arg])) != NULL)) {
          option_case(*option);
          if (*argv[count_arg] == 'e') {
            if (len > 2) {
              argv[count_arg]++;
              if (pattern[0]) strncat(pattern, stick, strlen(stick));
              strncat(pattern, argv[count_arg], strlen(argv[count_arg]));
              break;
            } else {
              if (count_arg + 1 < argc) {
                count_arg++;
                if (pattern[0]) strncat(pattern, stick, strlen(stick));
                strncat(pattern, argv[count_arg], strlen(argv[count_arg]));
                break;
              } else {
              }
            }
          } else {
            if (count_arg + 1 <= argc) {
              count_arg++;
              memcpy(ptr_file_pattern, argv[count_arg], strlen(argv[count_arg]) + 1);
              fp = fopen(ptr_file_pattern, "r");
              while (1) {
                estr = fgets(buff, sizeof(buff), fp);
                squeeze(buff, '\n');
                if (buff[strlen(buff) - 1] == '\n') {
                  buff[strlen(buff)] = '\0';
                }
                if (estr == NULL) {
                  if (feof(fp) != 0) {
                    break;
                  } else {
                    break;
                  }
                }
                if (pattern[0]) strncat(pattern, stick, strlen(stick));
                strncat(pattern, buff, strlen(buff));
              }
              fclose(fp);
              pattern_swich = 1;
              break;
            } else {
              fprintf(stderr, "WARNING! enter the file name\n");
              ferror = 1;
            }
          }
        } else {
          fprintf(stderr, "grep: invalid option -- %c\n", *argv[count_arg]);
          fprintf(stderr, "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n");
          fprintf(stderr, "\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
          fprintf(stderr, "\t[--context[=num]] [--directories=action] [--label] [--line-buffered]\n");
          fprintf(stderr, "\t[--null] [pattern] [file ...]\n");
          ferror = 1;
          break;
        }
        argv[count_arg]++;
      }
    } else {
      if (pattern_swich == 0 && grep.data_e == 0) {
        strncat(pattern, argv[count_arg], strlen(argv[count_arg]));
        pattern_swich = 1;
      } else {
        if (argv[count_arg + 1]) file_count = 1;
        memcpy(ptr_file, argv[count_arg], strlen(argv[count_arg]) + 1);
        if (grep.data_i == 1) {
          char option_i[MIN_SIZE] = "(?i)";
          char *ptr_option_i = option_i;
          strncat(ptr_option_i, pattern, strlen(pattern));
          strncpy(pattern, option_i, strlen(option_i));
        }
        fp = fopen(file_name, "r");
        if (fp == NULL) {
          if (!grep.data_s)
            fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
          return 0;
        }
        re = pcre_compile((char *)pattern, options, &error, &erroffset, NULL);
        if (!re) {
          printf("Failed\n");
        } else {
          int ovector[30] = {0};
          int number = 1;
          int count_c = 0;
          int count_vc = 0;
          int count = 0;
          while (1) {
            count = 0;
            estr = fgets(buff, sizeof(buff), fp);
            if (estr == NULL) {
              if (feof(fp) != 0) {
                break;
              } else {
                break;
              }
            }
            count = pcre_exec(re, NULL, (char *)buff, strlen(buff), 0, 0,
                              ovector, 30);
            squeeze(buff, '\n');
            if (count <= 0) {
              count_vc++;
              inverts(file_count, file_name, number, buff);
            } else {
              count_c++;
              search(file_count, file_name, number, buff);
              search_o(re, file_count, count, count_c, file_name, number, buff, ovector);
            }
            number++;
          }
          opt_cl(file_count, count_c, count_vc, file_name);
        }
        fclose(fp);
        pcre_free((void *) re);
      }
    }
    count_arg++;
  }
  return 0;
}

void inverts(int file_count, char *file_name, int number, char *buff) {
  if (file_count == 1) {
    if (grep.data_v && !grep.data_c && !grep.data_l && !grep.data_o) {
      if (!grep.data_h) printf("%s:", file_name);
      if (grep.data_n) printf("%d:", number);
      if (!grep.data_c) printf("%s\n", buff);
    }
  } else {
    if (grep.data_v && !grep.data_c && !grep.data_l && !grep.data_o) {
      if (grep.data_n) printf("%d:", number);
      printf("%s\n", buff);
    }
  }
}

void search(int file_count, char *file_name, int number, char *buff) {
  if (file_count == 1) {
    if (!grep.data_v && !grep.data_c && !grep.data_l && !grep.data_o) {
      if (!grep.data_h) printf("%s:", file_name);
      if (grep.data_n) printf("%d:", number);
      if (!grep.data_c) printf("%s\n", buff);
    }
  } else {
    if (!grep.data_v && !grep.data_c && !grep.data_l && !grep.data_o) {
      if (grep.data_n) printf("%d:", number);
      printf("%s\n", buff);
    }
  }
}

void search_o(pcre *re, int file_count, int count, int count_c,
          char *file_name, int number, char *buff, int *ovector) {
  for (int c = 0; c < 2 * count; c += 2) {
    if (ovector[c] < 0) {
      // printf("<unset>\n");
    } else {
        if (grep.data_o) {
        if (grep.data_c) printf("%d\n", count_c);
        if (grep.data_l) printf("%s\n", file_name);
        if (!grep.data_h && file_count == 1) printf("%s:", file_name);
        if (grep.data_n && !grep.data_l && !grep.data_c) printf("%d:", number);
        if (!grep.data_l && !grep.data_c) {
          while (count > 0) {
            for (int i = ovector[c]; i < ovector[c + 1]; i++) {
              printf("%c", buff[i]);
            }
            printf("\n");
            count = pcre_exec(re, NULL, (char *)buff, strlen(buff),
                                          ovector[1], 0, ovector, 30);
          }
        }
      }
    }
  }
}

void opt_cl(int file_count, int count_c, int count_vc, char *file_name) {
  if (file_count == 1) {
    if (grep.data_c && !grep.data_o) {
      if (!grep.data_v) {
        printf("%s:%d\n", file_name, count_c);
      } else {
        printf("%s:%d\n", file_name, count_vc);
      }
    }
    if (grep.data_l && !grep.data_o && count_c > 0) printf("%s\n", file_name);
  } else {
    if (grep.data_c && !grep.data_o) {
      if (!grep.data_v) {
        printf("%d\n", count_c);
      } else {
        printf("%d\n", count_vc);
      }
    }
    if (grep.data_l && !grep.data_o && count_c > 0) printf("%s\n", file_name);
  }
}

void option_case(char a) {
  switch (a) {
    case 'e':
      grep.data_e = 1;
      break;
    case 'i':
      grep.data_i = 1;
      break;
    case 'v':
      grep.data_v = 1;
      break;
    case 'c':
      grep.data_c = 1;
      break;
    case 'l':
      grep.data_l = 1;
      break;
    case 'n':
      grep.data_n = 1;
      break;
    case 'h':
      grep.data_h = 1;
      break;
    case 's':
      grep.data_s = 1;
      break;
    case 'f':
      grep.data_f = 1;
      break;
    case 'o':
      grep.data_o = 1;
      break;
  }
}

void null_option() {
  grep.data_e = 0;
  grep.data_i = 0;
  grep.data_v = 0;
  grep.data_c = 0;
  grep.data_l = 0;
  grep.data_n = 0;
  grep.data_h = 0;
  grep.data_s = 0;
  grep.data_f = 0;
  grep.data_o = 0;
}

void squeeze(char s[], int c) {
  int i, j;
  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c) s[j++] = s[i];
  s[j] = '\0';
}
