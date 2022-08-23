#include <check.h>
#include <string.h>
#include <stdio.h>
#include "s21_string.h"

FILE *init_file(char *path, char *testMessage);
void test_print(const char *str, const char *buff, const char *buff1);
void zero_buff(char *buff, int n);

START_TEST(strlen_check) {
    char * str = {"Hello"};
    ck_assert_int_eq(s21_strlen(str), strlen(str));
    str = "";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
    str = "g\0g";
    ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(strchr_check) {
    char * str = {"Helloe"};
    int c = 'e';
    ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
    c = 123;
    ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
    str = "";
    c = 'e';
    ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
    str = "Hello\0guy";
    c = 'u';
    ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(strrchr_check) {
    char * str = {"Helloe"};
    int c = 'e';
    ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
    c = 123;
    ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
    str = "";
    c = 'e';
    ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
    str = "H\0elloe";
    c = 'e';
    ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(strcmp_check) {
    char * str = "Hello";
    char * str2 = "Hello";
    ck_assert_int_eq(s21_strcmp(str, str2), strcmp(str, str2));
    str2 = "Helol";
    ck_assert_int_eq(s21_strcmp(str, str2), strcmp(str, str2));
    str = "";
    ck_assert_int_eq(s21_strcmp(str, str2), strcmp(str, str2));
    str = "Hello";
    str2 = "";
    ck_assert_int_eq(s21_strcmp(str, str2), strcmp(str, str2));
    str = "";
    str2 = "";
    ck_assert_int_eq(s21_strcmp(str, str2), strcmp(str, str2));
}
END_TEST

START_TEST(strncmp_check) {
    char str[70] = "Hello\0Nigga";
    char str2[70] = "Hello\0Bitch";
    s21_size_t n = 5;
    ck_assert_int_eq(s21_strncmp(str, str2, n), strncmp(str, str2, n));
    n = 6;
    ck_assert_int_eq(s21_strncmp(str, str2, n), strncmp(str, str2, n));
    n = 7;
    ck_assert_int_eq(s21_strncmp(str, str2, n), strncmp(str, str2, n));
    n = 8;
    ck_assert_int_eq(s21_strncmp(str, str2, n), strncmp(str, str2, n));
    n = 13;
    ck_assert_int_eq(s21_strncmp(str, str2, n), strncmp(str, str2, n));
    n = 0;
    ck_assert_int_eq(s21_strncmp(str, str2, n), strncmp(str, str2, n));
}
END_TEST

START_TEST(strstr_check) {
    char * str = "Dont give up";
    char * str2 = "giv";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
    str2 = "Don't";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
    str = "";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
    str = "give up";
    str2 = "";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
    str = "";
    str2 = "";
    ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(strtok_check) {
    char str[70] = "uber^flag\0polus^^fuck*luck^duck#";
    char *delim = "^";
    ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
    delim = "u";
    ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
    delim = "r*k";
    ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
    delim = "#";
    ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
    delim = "";
    ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
    delim = "b";
    ck_assert_ptr_eq(s21_strtok(str, delim), strtok(str, delim));
}
END_TEST

START_TEST(strpbrk_check) {
    char* str = "Dont give up";
    char* delim = "no";
    ck_assert_ptr_eq(s21_strpbrk(str, delim), strpbrk(str, delim));
    delim = "p";
    ck_assert_ptr_eq(s21_strpbrk(str, delim), strpbrk(str, delim));
    delim = " ";
    ck_assert_ptr_eq(s21_strpbrk(str, delim), strpbrk(str, delim));
    delim = "\0g";
    ck_assert_ptr_eq(s21_strpbrk(str, delim), strpbrk(str, delim));
    str = "";
    ck_assert_ptr_eq(s21_strpbrk(str, delim), strpbrk(str, delim));
    delim = "";
    ck_assert_ptr_eq(s21_strpbrk(str, delim), strpbrk(str, delim));
}
END_TEST

START_TEST(strspn_check) {
    char* str1 = "Dont give up";
    char* str2 = "nDo";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
    str2 = "Dot";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
    str2 = "luck";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
    str2 = "up";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
    str2 = " ";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
    str1 = "";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
    str2 = "";
    ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
}
END_TEST

START_TEST(strcspn_check) {
    char* str1 = "Dont give up";
    char* str2 = "nDo";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    str2 = "Dot";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    str2 = "luck";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    str2 = "up";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    str2 = " ";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    str1 = "";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
    str2 = "";
    ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(strcat_check) {
    char dest[70] = "Dont give up ";
    char* src = "bro";
    ck_assert_ptr_eq(s21_strcat(dest, src), strcat(dest, src));
    src = "";
    ck_assert_ptr_eq(s21_strcat(dest, src), strcat(dest, src));
    src = "\0g";
    ck_assert_ptr_eq(s21_strcat(dest, src), strcat(dest, src));
}
END_TEST

START_TEST(strncat_check) {
    char dest[70] = "Dont give up ";
    char *src = "bro";
    s21_size_t n = 3;
    ck_assert_ptr_eq(s21_strncat(dest, src, n), strncat(dest, src, n));
    n = 0;
    ck_assert_ptr_eq(s21_strncat(dest, src, n), strncat(dest, src, n));
    n = 5;
    ck_assert_ptr_eq(s21_strncat(dest, src, n), strncat(dest, src, n));
    src = "";
    ck_assert_ptr_eq(s21_strncat(dest, src, n), strncat(dest, src, n));
}
END_TEST

START_TEST(strcpy_check) {
    char dest[70] = "Dont give up ";
    char *src = "bro";
    ck_assert_ptr_eq(s21_strcpy(dest, src), strcpy(dest, src));
    src = "";
    ck_assert_ptr_eq(s21_strcpy(dest, src), strcpy(dest, src));
    src = "adkgns\0bgs;lfmpoangsd";
    ck_assert_ptr_eq(s21_strcpy(dest, src), strcpy(dest, src));
}
END_TEST

START_TEST(strncpy_check) {
    char dest[70] = "Dont give up ";
    char *src = "bro";
    s21_size_t n = 3;
    ck_assert_ptr_eq(s21_strncpy(dest, src, n), strncpy(dest, src, n));
    src = "";
    ck_assert_ptr_eq(s21_strncpy(dest, src, n), strncpy(dest, src, n));
    src = "adkgns\0bgs;lfmpoangsd";
    n = 10;
    ck_assert_ptr_eq(s21_strncpy(dest, src, n), strncpy(dest, src, n));
}
END_TEST

// mem

START_TEST(memcmp_check) {
    char *str1 = "Hello\0Nigga";
    char *str2 = "Hello\0Bro";
    s21_size_t n = 3;
    ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
    n = 8;
    ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
    n = 15;
    ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
    str1 = "";
    str2 = "";
    ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(memcpy_check) {
    char dest[70] = "Dont give \0up bro";
    char *src = "bro";
    s21_size_t n = 0;
    ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
    n = 15;
    ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
    src = "aksfnsdbfuobgsjodbfsdovbosdib";
    n = 25;
    ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
}
END_TEST

START_TEST(memmove_check) {
    char dest[70] = "Dont give \0up bro";
    char *src = "bro";
    s21_size_t n = 0;
    ck_assert_ptr_eq(s21_memmove(dest, src, n), memmove(dest, src, n));
    n = 15;
    ck_assert_ptr_eq(s21_memmove(dest, src, n), memmove(dest, src, n));
    src = "aksfnsdbfuobgsjodbfsdovbosdib";
    n = 25;
    ck_assert_ptr_eq(s21_memmove(dest, src, n), memmove(dest, src, n));
}
END_TEST

START_TEST(memchr_check) {
    char str[70] = "Dont give \0up *bro";
    int c = 'g';
    s21_size_t n = 0;
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
    n = 20;
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
    c = 'o';
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
    c = '*';
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
    c = '%';
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(memset_check) {
    char str[70] = "Dont give \0up *bro";
    int c = 'g';
    s21_size_t n = 0;
    ck_assert_ptr_eq(s21_memset(str, c, n), memset(str, c, n));
    n = 20;
    ck_assert_ptr_eq(s21_memset(str, c, n), memset(str, c, n));
    c = 'o';
    ck_assert_ptr_eq(s21_memset(str, c, n), memset(str, c, n));
    c = '*';
    ck_assert_ptr_eq(s21_memset(str, c, n), memset(str, c, n));
    c = '%';
    ck_assert_ptr_eq(s21_memset(str, c, n), memset(str, c, n));
}
END_TEST

START_TEST(to_upper_check) {
  FILE *testFile = init_file("files/testsbonus_upper.txt", "");
  while (1) {
    char buff[MAX_STR * 100] = {0};
    char str[MAX_STR * 100] = {0};
    char *estr;
    estr = fgets(buff, sizeof(buff), testFile);
    int sl = strlen(buff) - 1;
    if (buff[sl] == '\n') buff[sl] = 0;
    if (estr == NULL) {
      break;
    } else {
      estr = fgets(str, sizeof(str), testFile);
      int sk = strlen(str) - 1;
      if (str[sk] == '\n') str[sk] = 0;
      if (estr == NULL) {
        break;
      } else {
        char *ptr = s21_to_upper(buff);
        ck_assert_str_eq(ptr, str);
        free(ptr);
      }
    }
  }
  fclose(testFile);
}
END_TEST

START_TEST(to_lower_check) {
  FILE *testFile = init_file("files/testsbonus_lower.txt", "");

  while (1) {
    char buff[MAX_STR * 100] = {0};
    char str[MAX_STR * 100] = {0};
    char *estr;

    estr = fgets(buff, sizeof(buff), testFile);
    int sl = strlen(buff) - 1;
    if (buff[sl] == '\n') buff[sl] = 0;
    if (estr == NULL) {
      break;
    } else {
      estr = fgets(str, sizeof(str), testFile);
      int sk = strlen(str) - 1;
      if (str[sk] == '\n') str[sk] = 0;
      if (estr == NULL) {
        break;
      } else {
        char *ptr = s21_to_lower(buff);
        ck_assert_str_eq(ptr, str);
        free(ptr);
      }
    }
  }
  fclose(testFile);
}
END_TEST

START_TEST(insert_check) {
    char str[70] = "Dont give up";
    char *ins = "ROFL";
    char *res = "Dont gROFLive up";
    int index = 6;
    char *pnr = s21_insert(str, ins, index);
    ck_assert_str_eq(pnr, res);
    free(pnr);
}
END_TEST

START_TEST(trim_check) {
    char str[70] = "Dont give up luck duck suck";
    char *trim = "kDount cid";
    char *res = "give up luck duck s";
    char *pnr = s21_trim(str, trim);
    ck_assert_str_eq(pnr, res);
    free(pnr);
}
END_TEST

START_TEST(strerror_check) {
  int num[] = {
      118, 28, 106, 109, 132, -10, 17, 103, 5, 60, 45, 75, 22, 52, 140,
      133, 77, 93, -21, 71, -46, -1, -22, 110, -18, 30, -24, -28, 149, -6,
      52, 117, 72, 9, 77, 54, 48, 144, 8, 104, 55, 103, 30, 128, 6,
      20, 111, 133, -36, 139, 55, -32, -11, 82, 128, 19, -37, -45, 41, -37,
      -2, 144, 130, 120, 3, 57, 25, 102, 52, 83, 56, -42, 37, 136, 136,
      94, 6, 97, 77, 20, 87, -16, 38, 126, 115, 16, -4, 128, 20, 87,
      141, 67, 81, 121, 37, 134, 29, 112, 86, 132,
  };
  int n;
  for (int i = 0; i < 100; i++) {
    n = num[i];
    ck_assert_str_eq(s21_strerror(n), strerror(n));
  }
}
END_TEST

START_TEST(sprintf_f) {
  FILE *testFile = init_file("files/testsprintff.txt", "test_sprintf_F CHECK");
  while (1) {
    char str[MAX_STR] = {'\0'};
    char *estr;
    estr = fgets(str, sizeof(str), testFile);
    if (estr == NULL) break;
    double arr[] = {0.0,
                      -0.0,
                      -1.0,
                      1.0,
                      123.123123,
                      -123.123123,
                      123456789e20,
                      -123456789e20,
                      -123e-12,
                      123e-12,
                      -123456789.1101010100001,
                      123456789.1101010100001,
                      1.0123e-10,
                      1.0123e-10};
      for (int j = 0; j < 14; j++) {
        char buff1[MAX_STR] = {'\0'};
        snprintf(buff1, sizeof(buff1), str, arr[j]);
        char buff[MAX_STR] = {'\0'};
        s21_sprintf(buff, str, arr[j]);
        if (strcmp(buff, buff1) == 0) {
          printf("+");
          ck_assert_str_eq(buff, buff1);
        } else {
          test_print(str, buff1, buff);
        }
      }
    }
printf("\n");
fclose(testFile);
}
END_TEST

START_TEST(sprintf_inttype) {
  FILE *testFile =
      init_file("files/testsprintfd.txt", "test_sprintf_int CHECK");
  while (1) {
    char str[MAX_STR] = {'\0'};
    char *estr;
    char changeSpec[] = {'d', 'i', 'u'};
    estr = fgets(str, sizeof(str), testFile);
    if (estr == NULL) break;
    for (int i = 0; i < 3; i++) {
      char *ptr = str;
      while (*ptr && *ptr != changeSpec[i == 0 ? i : (i - 1)]) {
        ptr++;
      }
      if (*ptr == changeSpec[i == 0 ? i : (i - 1)]) *ptr = changeSpec[i];
      if (estr == NULL) break;
      int arr[] = {0,      -0,      -1,     1,     -1,       123,    -123,
                   123456, -123456, -72123, 72123, -1234569, 1234569};
      for (int j = 0; j < 13; j++) {
        char buff1[MAX_STR] = {'\0'};
        snprintf(buff1, sizeof(buff1), str, arr[j]);
        char buff[MAX_STR] = {'\0'};
        s21_sprintf(buff, str, arr[j]);
        if (strcmp(buff, buff1) == 0) {
          printf("+");
          ck_assert_str_eq(buff, buff1);
        } else {
          test_print(str, buff1, buff);
        }
      }
    }
  }
  printf("\n");
  fclose(testFile);
}
END_TEST

START_TEST(sprintf_s) {
  FILE *testFileS = init_file("files/testsprintfs.txt", "test_sprintf_S CHECK");
  while (1) {
    char str[MAX_STR];
    zero_buff(str, MAX_STR);
    char *estr;
    estr = fgets(str, sizeof(str), testFileS);
    if (estr == NULL) break;
    char *arr[] = {"", "str", "longlongstr", "veryyyyyyyyyyyylongstr"};
    for (int i = 0; i < 4; i++) {
      char buff1[MAX_STR] = {'\0'};
      snprintf(buff1, sizeof(buff1), str, arr[i]);
      char buff[MAX_STR] = {'\0'};
      s21_sprintf(buff, str, arr[i]);
      if (strcmp(buff, buff1) == 0) {
        ck_assert_str_eq(buff, buff1);
        printf("+");
      } else {
        test_print(str, buff, buff1);
      }
    }
  }
  printf("\n");
  fclose(testFileS);
}
END_TEST

int test_1() {
    int nf;
    Suite *s1 = suite_create("Part 1. Implementation of the string.h library functions");
    TCase *tc1_1 = tcase_create("Test string.h");
    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, strlen_check);
    tcase_add_test(tc1_1, strchr_check);
    tcase_add_test(tc1_1, strrchr_check);
    tcase_add_test(tc1_1, strcmp_check);
    tcase_add_test(tc1_1, strstr_check);
    tcase_add_test(tc1_1, strtok_check);
    tcase_add_test(tc1_1, strpbrk_check);
    tcase_add_test(tc1_1, strspn_check);
    tcase_add_test(tc1_1, strcspn_check);
    tcase_add_test(tc1_1, strcat_check);
    tcase_add_test(tc1_1, strcpy_check);
    tcase_add_test(tc1_1, strncmp_check);
    tcase_add_test(tc1_1, strncat_check);
    tcase_add_test(tc1_1, strncpy_check);
    tcase_add_test(tc1_1, memcmp_check);
    tcase_add_test(tc1_1, memcpy_check);
    tcase_add_test(tc1_1, memmove_check);
    tcase_add_test(tc1_1, memchr_check);
    tcase_add_test(tc1_1, memset_check);
    tcase_add_test(tc1_1, to_upper_check);
    tcase_add_test(tc1_1, to_lower_check);
    tcase_add_test(tc1_1, insert_check);
    tcase_add_test(tc1_1, trim_check);
    tcase_add_test(tc1_1, strerror_check);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);
    return nf;
}

int test_2() {
    int nf;
    Suite *s1 = suite_create("Part 2. Implementation of the sprintf functions");
    TCase *tc1_2 = tcase_create("Test sprintf");
    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1_2);
    tcase_add_test(tc1_2, sprintf_f);
    tcase_add_test(tc1_2, sprintf_inttype);
    tcase_add_test(tc1_2, sprintf_s);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);
    return nf;
}

int main(void) {
    int nf = 0;
    nf += test_1();
    nf += test_2();
    return 0;
}

void zero_buff(char *buff, int n) {
  for (int i = 0; i < n; i++) {
    buff[i] = 0;
  }
}

void test_print(const char *str, const char *buff, const char *buff1) {
  static int i = 0;
  if (i < 100) {
    printf("\n.________________\n%s\n", str);
    printf("s:%s\n", buff1);
    printf("m:%s\n", buff);
    printf("\n");
    i++;
  } else {
    printf("-");
  }
}

FILE *init_file(char *path, char *testMessage) {
  FILE *testFile = NULL;
  if ((testFile = fopen(path, "r")) != NULL) {
    printf("%s", testMessage);
  }
  return testFile;
}
