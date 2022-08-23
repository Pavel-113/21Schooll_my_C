#include "s21_string.h"
#include <stdio.h>

// _____________part1__________________

s21_size_t s21_strlen(const char *str) {
    s21_size_t length = 0;
    while (*(str + length)) {
        length++;
    }
    return length;
}

char *s21_strchr(const char* str, int c) {
    char* str1 = (char*) str;
    s21_size_t i = 0;
        char* p = s21_NULL;
        while (*(str1 + i) != '\0' && *(str1 + i) != c) {
            i++;
        }
        if (*(str1 + i) == c) {
            p = (char*)(str1 + i);
        }
        return p;
    }

char *s21_strrchr(const char *str, int c) {
    char* str1 = (char*) str;
    int l = s21_strlen(str) - 1;
    char* p = s21_NULL;
    while (l > 0 && *(str1 + l) != c) {
        l--;
    }
    if (*(str1 + l) == c) {
        p = (str1 + l);
    }
    return p;
}

void *s21_memchr(const void *str, int c, int n) {
    char *str1 = (char*) str;
    int ptr = 0;
    char *p = s21_NULL;
    while (*(str1 + ptr) != c && ptr != n - 1) {
        ptr++;
    }
    if (n != 0 && *(str1 + ptr) == c) {
        p = (char *) (str1 + ptr);
    }
    return p;
}

int s21_strcmp(const char* str1, const char* str2) {
    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
    int result = 0;
    while (*str1 && *str1 == *str2 && n > 0) {
        n--;
        str1++;
        str2++;
    }
    if (n != 0) result = (*str1 - *str2);
    return result;
}

char *s21_strcpy(char* dest, const char* src) {
    s21_size_t i = 0;
    do {
        *(dest + i) = *(src + i);
        i++;
    } while (*(dest + i - 1) != '\0');
    return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t ptr = 0;
    do {
        *(dest + ptr) = *(src + ptr);
        ptr++;
    } while (*(dest + ptr - 1) != '\0' && ptr != n);
    return dest;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    s21_size_t flag = 0;
    char *strg1 = (char*)str1;
    char *strg2 = (char*)str2;
    char *p = s21_NULL;
    while (flag != 1 && *strg1) {
        s21_size_t i = 0;
        while (*(strg2 + i)) {
            if (*strg1 == *(strg2 + i)) {
                p = (char*)(strg1);
            }
            i++;
        }
        if (p != s21_NULL) {
            flag = 1;
        }
        strg1++;
    }
    return p;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char* hstack = (char*) haystack;
    char* needl = (char*) needle;
    int len = s21_strlen(needl);
    char* p = s21_NULL;
    if (len == 0) {
        p = hstack;
    } else {
    for (int i = 0; *(hstack + i) != '\0'; i++) {
        int j = i;
        int t = 0;
        while (*(needl + t) != '\0' && *(hstack + j) == *(needl + t)) {
            j++;
            t++;
        }
        if (t > 0 && *(needl + t) == '\0') {
            p = hstack + i;
            break;
        }
    }
    }
    return p;
}

char *s21_strcat(char* dest, const char* src) {
    s21_size_t i = 0;
    while (*(dest + i) != '\0') {
        i++;
    }
    s21_size_t j = 0;
    do {
        *(dest + i) = *(src + j);
        i++;
        j++;
    } while (*(src + j - 1) != '\0');
             return dest;
}

char *s21_strncat(char* dest, const char* src, s21_size_t n) {
    s21_size_t i = 0;
    while (*(dest + i) != '\0') {
        i++;
    }
    s21_size_t j = 0;
    do {
        *(dest + i) = *(src + j);
        i++;
        j++;
    } while (*(src + j - 1) != '\0' && j < n);
             return dest;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t ptr = 0;
  s21_size_t result = 0;
  const char *str = str1;
  while (*(str + ptr)) {
    if ((char *)(str + ptr) == s21_strpbrk(str + ptr, str2))
      result++;
    else
      break;
    ptr++;
  }
  return result;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t ptr = 0;
  s21_size_t res = 0;
  const char *str = str1;
  char *pbrk = s21_strpbrk(str1, str2);
  while (*(str + ptr) && (char *)(str + ptr) != pbrk) {
    res++;
    ptr++;
  }
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last = 0;
  char *result = s21_NULL;
  if (str) {
    last = str;
  }
  if ((last != 0) && (*last != 0)) {
    char *c = last;
    while (s21_strchr(delim, *c)) {
      ++c;
    }
    if (*c != 0) {
      char *start = c;
      while (*c && (s21_strchr(delim, *c) == 0)) {
        ++c;
      }
      if (*c == 0) {
        last = c;
        result = start;
      } else {
        *c = 0;
        last = c + 1;
        result = start;
      }
    }
  }
  return result;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    char *str1 = (char*) str;
    s21_size_t i = 0;
    while (n-- > 0) {
        *(str1 + i) = c;
        i++;
    }
    return str1;
}

void *s21_memmove(void* dest, const void* src, s21_size_t n) {
    s21_size_t i = 0;
    char *dest1 = (char*) dest;
    char *src1 = (char*) src;
    if (dest < src) {
        while (i < n) {
            *(dest1 + i) = *(src1 + i);
            i++;
        }
    } else {
        while (n > 0) {
            *(dest1 + n - 1) = *(src1 + n - 1);
            n--;
        }
    }
    return dest1;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int result = 0;
    char *strg1 = (char*) str1;
    char *strg2 = (char*) str2;
    while (*strg1 == *strg2 && n > 1) {
        n--;
        strg1++;
        strg2++;
    }
    if (n != 0) result = (*strg1 - *strg2);
    return result;
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
    char *dest1 = (char*) dest;
    s21_size_t i = 0;
    do {
        *(dest1 + i) = *((char*)src + i);
        i++;
    } while (i < n);
    return dest1;
}

// _____________part3__________________

void *s21_to_upper(const char *str) {
  s21_size_t ptr = 0;
  int dx = 'A' - 'a';
  int i = s21_strlen(str);
  char *str_new = (char *)calloc(i, sizeof(char));
  while (*(str + ptr)) {
    if (*(str + ptr) >= 'a' && *(str + ptr) <= 'z') {
      *(str_new + ptr) = *(str + ptr) + dx;
    } else {
      *(str_new + ptr) = *(str + ptr);
    }
    ptr++;
  }
  return str_new;
}

void *s21_to_lower(const char *str) {
  s21_size_t ptr = 0;
  int dx = 'A' - 'a';
  int i = s21_strlen(str);
  char *str_new = (char *)calloc(i, sizeof(char));
  while (*(str + ptr)) {
    if (*(str + ptr) >= 'A' && *(str + ptr) <= 'Z') {
      *(str_new + ptr) = *(str + ptr) - dx;
    } else {
      *(str_new + ptr) = *(str + ptr);
    }
    ptr++;
  }
  return str_new;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    s21_size_t flag = 0;
    char * s;
    s21_size_t size_string = s21_strlen(str) + s21_strlen(src);
    if (size_string < 1 || start_index > s21_strlen(src)) flag = 1;
    if (flag == 0) {
        s = (char*)calloc(size_string, sizeof(char));
        s21_strncpy(s, src, start_index);
        s21_strcpy((s + start_index), str);
        s21_strcpy((s + start_index + s21_strlen(str)), (src + start_index));
    } else {
        s = s21_NULL;
    }
    return s;
}

void *s21_trim(const char *src, const char *trim_chars) {
  const char *str1 = (char *)src;
  const char *ch = (char *)trim_chars;
  char default_chars[] = "\n\r\t ";
  int n = s21_strlen(src);
  int k = s21_strlen(trim_chars);
  if (k == 0) {
    ch = default_chars;
  }
  char *result;
  if (n > 0) {
    int i = 0;
    while (*(str1 + i) && s21_strchr(ch, *(str1 + i))) {
      i++;
    }
    while (s21_strchr(ch, *(str1 + n))) {
      n--;
    }
    if (n - i < 0) {
      result = (char *)calloc(1, sizeof(char));
      *result = '\0';
    } else {
      char *str = (char *)calloc(n - i, sizeof(char));
      str = s21_strncpy(str, (str1 + i), n - i + 1);
      str[n - i + 1] = '\0';
      result = str;
    }
  } else {
    result = (char *)calloc(1, sizeof(char));
    *result = '\0';
  }
  return result;
}

char *s21_strerror(int errnum) {
    char *res;
#ifdef OS_Mac
    int max = 107;
    char* errMessage = "Unknown error:";
#else
    int max = 134;
    char* errMessage = "Unknown error";
#endif
    if ((errnum >= 0) && (errnum < max)) {
#ifdef OS_Mac
    const char* a[107] = APPLE;
#else
    const char* a[134] = LINUX;
#endif
    res = (char *)a[errnum];
    } else {
        static char buff[MAX_STR];
        sprintf(buff, "%s %d", errMessage, errnum);
        res = buff;
    }
    return res;
}

// _____________part2__________________

int s21_sprintf(char * str, const char * format, ...);
int parse(const char *format, list **head);
struct_form parse_specificator(char *specifiers);
char *specifier_case(char *format, struct_form p, va_list args);
char *print_integer_d_i(char *str, long int i, struct_form p);
char *print_integer_u(char *str, unsigned long int i, struct_form p);
char *print_float(char *str, double f, struct_form p);
char *print_char(char *str, char *s, struct_form p);
char *get_formating(char *str, char *buff, struct_form p, int flag_minus, int flag_u);
int check_format(char* frm_tmp_ptr);
char *fill_symbol(char * str, char space, int numb);
void to_null(struct_form * p);
struct_form add_struct(int width, int precision, char *length, char *specifier, char *str_tmp);
list *pop_list(list **head, struct_form * p);
list *list_free(list **head);
list *add_list(list * head, struct_form d);

int s21_sprintf(char *str, const char * format, ...) {
    char *str_ptr = str;
    list *head = s21_NULL;
    parse(format, &head);
    va_list args;
    va_start(args, format);
    while (head != s21_NULL) {
        struct_form p;
        pop_list(&head, &p);
        if (p.is_str == 1) {
            char *ptr = p.str_tmp;
            while (*ptr) {
               *str = *ptr;
                ptr++;
                str++;
            }
        } else if (p.is_str == -1) {
            char * ptr = p.str_tmp;
            *str = '%';
            str++;
            while (*ptr) {
               *str = *ptr;
                ptr++;
                str++;
            }
        } else {
            str = specifier_case(str, p, args);
        }
    }
    va_end(args);
    *str = '\0';
    list_free(&head);
    return (int)(str - str_ptr);
}

int parse(const char *format , list ** head) {
    int error_flag = 0;
    while (*format) {
        struct_form p;
        to_null(&p);
        char frm_tmp[MAX_STR] = {'\0'};
        char *frm_tmp_ptr = frm_tmp;
        char str_tmp[MAX_STR] = {'\0'};
        char *str_tmp_ptr = str_tmp;
        int i = 0;
        int j = 0;

        if (s21_strchr("%", *format) != s21_NULL) {
            format++;
            if (s21_strchr("%", *format) != s21_NULL) {
                format++;
                str_tmp_ptr[j] = '%';
                j++;
                str_tmp_ptr[j] = '\0';
                s21_strcpy(p.str_tmp, str_tmp_ptr);
                p.is_str = 1;
                *head = add_list(*head, p);
            } else {
                while (*format && s21_strchr(IS_SPECIFIERS, *format)  == s21_NULL) {
                    frm_tmp_ptr[i] = *format;
                    i++;
                    format++;
                }
                frm_tmp_ptr[i] = *format;
                i++;
                frm_tmp_ptr[i] = '\0';
                format++;
                int check = (check_format(frm_tmp_ptr) != 0);
                if (check == 1) {
                    p.is_str = -1;
                    s21_strcpy(p.str_tmp, frm_tmp_ptr);
                    *head = add_list(*head, p);
                } else {
                p = parse_specificator(frm_tmp_ptr);
                *head = add_list(*head, p);
                }
            }
        } else {
            while (*format && s21_strchr("%", *format) == s21_NULL) {
                str_tmp_ptr[j] = *format;
                j++;
                format++;
                }
            str_tmp_ptr[j] = '\0';
            s21_strcpy(p.str_tmp, str_tmp_ptr);
            p.is_str = 1;
            *head = add_list(*head, p);
        }
    }
    return error_flag;
}

struct_form parse_specificator(char *specifiers) {
    int is_width = 0;
    int is_precision = 0;
    struct_form p;
    to_null(&p);
    s21_strcpy(p.str_tmp, specifiers);
    if (*specifiers) {
        while (*specifiers && s21_strchr(IS_FLAGS, *specifiers) != s21_NULL) {
            if (*specifiers == '-') {
                p.flag.minus = 1;
            } else if (*specifiers == '+') {
                p.flag.plus = 1;
            } else if (*specifiers == ' ') {
                p.flag.space = 1;
            } else {
                break;
            }
            specifiers++;
        }
        while (s21_strchr(IS_LENGTH_DESCRIPTION, *specifiers) == s21_NULL && *specifiers != '.' &&
               s21_strchr(IS_WIDTH_DESCRIPTION, *specifiers) != s21_NULL) {
            is_width++;
            p.width = p.width * 10 + (*specifiers - '0');
            specifiers++;
        }
        if (*specifiers == '.') {
            specifiers++;
            while (*specifiers == '.') {
                specifiers++;
            }
            while (s21_strchr(IS_LENGTH_DESCRIPTION, *specifiers) == s21_NULL &&
                   s21_strchr(IS_WIDTH_DESCRIPTION, *specifiers) != s21_NULL) {
                is_precision++;
                p.precision = p.precision*10 + (*specifiers - '0');
                specifiers++;
            }
        } else {
            p.precision = -1;
        }
        while (s21_strchr(IS_LENGTH_DESCRIPTION, *specifiers) != s21_NULL) {
            p.length = *specifiers;
            specifiers++;
        }
        if (s21_strchr(IS_SPECIFIERS, *specifiers) != s21_NULL) {
            p.specifier = *specifiers;
        } else {
            p.specifier = 'X';
        }
    }
    return p;
}

char *specifier_case(char *str, struct_form p, va_list args) {
    long int i = 0;
    double f = 0.0;
    char c = '\0';
    char *s = s21_NULL;
    unsigned long int u = 0;
    switch (p.specifier) {
        case 'c':
            c = va_arg(args, int);
            char strg[2];
            strg[0] = c;
            strg[1] = '\0';
            str = print_char(str, strg, p);
            break;
        case 'i':
        case 'd':
            if (p.length != 'l') {
                i = va_arg(args, int);
            }
            if (p.length == 'l') {
                i = va_arg(args, long int);
            }
            str = print_integer_d_i(str, i, p);
            break;
        case 'f':
            f = va_arg(args, double);
            str = print_float(str, f, p);
            break;
        case 's':
            s = va_arg(args, char *);
            str = print_char(str, s, p);
            break;
        case 'u':
            if (p.length != 'l') {
                u = va_arg(args, unsigned int);
            }
            if (p.length == 'l') {
                u = va_arg(args, unsigned long int);
            }
            str = print_integer_u(str, u, p);
            break;
        }
    return str;
}

char *print_integer_d_i(char *str, long int i, struct_form p) {
    int flag_u = 0;
    if (p.length == 'h') i = (short)i;
    int flag_minus = 0;
    char buff_tmp[MAX_STR] = {0};
    if (i < 0) {
        i *= -1;
        flag_minus = 1;
    }
    char buff_int[MAX_STR] = {0};
    int rank_s = 0;
    long int tmp_i = i;
    while (tmp_i != 0) {
        tmp_i /= 10;
        rank_s++;
    }
    int k = 0;
    if (i == 0) {
        buff_tmp[0] = '0';
    } else {
    while (i != 0) {
        buff_int[k] = i % 10 + '0';
        i /= 10;
        k++;
    }
    k--;
    int c = 0;
    while (k >= 0) {
        buff_tmp[c] = buff_int[k];
        k--;
        c++;
    }
    }
    str = get_formating(str, buff_tmp, p, flag_minus, flag_u);
    return str;
}

char *print_integer_u(char *str, unsigned long int i, struct_form p) {
    int flag_u = 1;
    if (p.length == 'h') i = (unsigned short)i;
    int flag_minus = 0;
    char buff_tmp[MAX_STR] = {0};
    char buff_int[MAX_STR] = {0};
    int rank_s = 0;
    long int tmp_i = i;
    while (tmp_i != 0) {
        tmp_i /= 10;
        rank_s++;
    }
    int k = 0;
    if (i == 0) {
        buff_tmp[0] = '0';
    } else {
        while (i != 0) {
            buff_int[k] = i % 10 + '0';
            i /= 10;
            k++;
        }
        k--;
        int c = 0;
        while (k >=0) {
            buff_tmp[c] = buff_int[k];
            k--;
            c++;
        }
    }
    p.flag.space = 0;
    str = get_formating(str, buff_tmp, p, flag_minus, flag_u);
    return str;
}

char *print_float(char *str, double f, struct_form p) {
    int flag_u = -1;
    int flag_minus = 0;
    char buff[MAX_STR] = {'\0'};
    char *buff1 = buff;
    char *point = ".";
    int point_pos;
    int sign = 0;
    int len = 0;

    if (p.precision == -1) p.precision = 6;
    if (f != f) {
        s21_strcpy(buff, "nan");
    } else {
        buff1 = fcvt(f, p.precision + 1, &point_pos, &sign);
        if (s21_strncmp(buff1, "inf", 3) == 0) {
        s21_strcpy(buff, "inf");
         s21_strcat(buff, "\0");
          p.precision = -1;
        } else {
    buff1 = fcvt(f, p.precision > 0 ? p.precision : 1, &point_pos, &sign);
    len = s21_strlen(buff1);
    char buff_zero[MAX_STR] = "0";
    if (point_pos >= 1) {
       s21_strncpy(buff, buff1, point_pos);
    } else {
        buff[0] = '0';
        buff[1] = '\0';
    }
    int zero_flag = 0;
        if (point_pos < 0) {
          int zero_count = p.precision;
          while (zero_flag != zero_count) {
            buff_zero[zero_flag] = '0';
            zero_flag++;
          }
        }
    if (p.precision > 0) {
        s21_strcat(buff, point);
        if (zero_flag && p.precision > 0) {
            s21_strcat(buff, buff_zero);
        } else if (p.precision > 0) {
            s21_strcat(buff, buff1 + point_pos);
        }
        len = s21_strlen(buff);
        buff[len] = '\0';
        }
    }
    if (f < 0) {
        flag_minus = 1;
    }
    if (f == 0) {
      char buff2[4];
      gcvt(f, 10, buff2);
      if (buff2[0] == '-') flag_minus = 1;
    }
    p.precision = -1;
    }
    str = get_formating(str, buff, p, flag_minus, flag_u);
    *(str + 1) = '\0';
    return str;
}

char *print_char(char * str, char * s, struct_form p) {
        int l = s21_strlen(s);
        if (p.precision != -1 && p.precision < l) {
            l = p.precision;
        }
        if (!p.flag.minus) {
            if (p.width > l) {
                str = fill_symbol(str, ' ', p.width - l);
            }
        }
        for (int i = 0; i < l && *s; i++) {
           *str = *s;
            str++;
            s++;
        }
        if (p.flag.minus) {
            if (p.width > l) {
                str = fill_symbol(str, ' ', p.width - l);
            }
        }
    *str = '\0';
    return str;
}

char *get_formating(char *str, char *buff, struct_form p, int flag_minus, int flag_u) {
    int rank_s = s21_strlen(buff);
    if (!p.flag.minus) {
        if (p.precision != -1 && p.width > p.precision) {
            int l = p.width - p.precision;
            if (p.precision < rank_s) l = p.width - rank_s;
            if ((flag_u != 1 && flag_minus) || (p.flag.plus && !flag_minus)) l--;
            if (p.flag.space) l--;
            str = fill_symbol(str, ' ', l);
            if (flag_u == 1 && p.flag.plus && p.width > rank_s) {
            str = fill_symbol(str, ' ', 1);
            }
        }
        if (p.precision == -1) {
            if (p.flag.plus && !flag_minus && flag_u != 1) rank_s++;
            if (p.width > rank_s) {
                int l = p.width - rank_s;
                if (p.flag.space) l--;
                if (flag_minus) l--;
                if (p.flag.space && p.flag.plus && !flag_minus) {
                    l++;
                }
                str = fill_symbol(str, ' ', l);
            }
        }
        if (p.flag.space && flag_u != 1) {
            if (!flag_minus) {
                if (p.precision == -1) {
                    str = fill_symbol(str, ' ', 1);
                    if (flag_u == -1 && p.flag.plus) {
                        str--;
                    }
                }
                if (p.precision >= 0 && p.width >= 0) {
                    str = fill_symbol(str, ' ', 1);
                }
            } else {
                if (p.precision >= 0 && p.width > p.precision) {
                    str = fill_symbol(str, ' ', 1);
                }
                if (p.precision == -1 && p.width > rank_s) {
                    str = fill_symbol(str, ' ', 1);
                }
            }
        }
    } else {
        if (p.flag.space) {
            if (p.precision >= 0 && !flag_minus) {
                str = fill_symbol(str, ' ', 1);
            }
            if (flag_u == -1 && !flag_minus && !p.flag.plus) {
                str = fill_symbol(str, ' ', 1);
            }
        }
    }
    if (!p.flag.minus && (flag_minus && p.flag.space) || (p.flag.plus && p.flag.space)) {
        if (p.width == rank_s +1) {
            str--;
        }
    }
    if (p.flag.plus && !flag_minus && !p.flag.minus &&
        p.flag.space && (p.width == 0) && flag_u != 1) str--;
    if (p.flag.plus && !flag_minus && flag_u != 1) str = fill_symbol(str, '+', 1);
    if (flag_minus == 1) str = fill_symbol(str, '-', 1);
    if (p.precision != -1) {
        if (p.width > rank_s || p.precision > rank_s) {
            int l = p.width - rank_s;
            if (p.precision != -1) l = p.precision - rank_s;
            if (flag_minus && p.width > 0 && p.precision == -1) l--;
            str = fill_symbol(str, '0', l);
            if (l > 0) rank_s += l;
        }
    }
    if (buff[0] == '0' && flag_u != -1) {
        if (p.precision == 0) {
            buff[0] = '\0';
        }
        if (p.precision == 0 && p.width > p.precision) {
            str = fill_symbol(str, ' ', 1);
        }
    }
    int k = 0;
    while (buff[k] != '\0') {
        *str = buff[k];
        k++;
        str++;
    }
    if (p.flag.minus && p.width > rank_s) {
        int l = p.width - rank_s;
        if ((flag_minus || p.flag.space || p.flag.plus) && flag_u != 1) l--;
        str = fill_symbol(str, ' ', l);
    }
    return str;
}


int check_format(char *frm_tmp_ptr) {
    int flag = 0;
    while (*frm_tmp_ptr) {
        if (s21_strchr(IS_RIGHT_DESCRIPTION, *frm_tmp_ptr) == s21_NULL) {
            flag = 1;
        }
        frm_tmp_ptr++;
    }
    return flag;
}

char *fill_symbol(char * str, char space, int numb) {
    while (numb > 0) {
       *str = space;
        str++;
        numb--;
    }
    return str;
}

void to_null(struct_form * p) {
    p->is_str = 0;
    p->flag.minus = 0;
    p->flag.plus = 0;
    p->flag.space = 0;
    p->length = 'X';
    p->width = 0;
    p->precision = 0;
    p->specifier = 'X';
    p->str_tmp[0] = '\0';
}

struct_form add_struct(int width, int precision, char *length, char *specifier, char *str_tmp) {
    struct_form p;
    p.width = width;
    p.precision = precision;
    char * ptr = p.str_tmp;

    while (*str_tmp) {
        *ptr = *str_tmp;
        str_tmp++;
        ptr++;
    }
    *ptr = '\0';

    ptr = &p.length;
    while (*length) {
        *ptr = *length;
        ptr++;
        length++;
    }
    *ptr = '\0';

    ptr = &p.specifier;
    while (*specifier) {
        *ptr = *specifier;
        ptr++;
        specifier++;
    }
    *ptr = '\0';

    return p;
}

list* add_list(list * head, struct_form d) {
    list * p = (list *) malloc (sizeof (list ));
    p->data = d;
    p->next = NULL;
    if (head == NULL) {
        head = p;
    } else {
        list * ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = p;
    }
    return head;
}

list *pop_list(list **head, struct_form * p) {
    if (*head != NULL) {
        *p = (*head) -> data;
        list * tmp = *head;
        *head = (*head) -> next;
        free(tmp);
    }
    return *head;
}

list *list_free(list **head) {
  list *p = *head;
  while (p != NULL) {
    free(p);
    p = p->next;
  }
  *head = NULL;
  return *head;
}
