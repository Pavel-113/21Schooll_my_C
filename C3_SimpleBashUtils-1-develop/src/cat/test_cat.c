#include <stdio.h>
#include <string.h>

void main() {
    FILE *f1 = fopen("file1", "r");
    FILE *f2 = fopen("file2", "r");
    int ch1 = 0;
    int ch2 = 0;
    int str = 1;
    int flag_err = 0;
    char string1[1024];
    char string2[1024];
    while (!feof(f1) && !feof(f2) && (ch1 == ch2)) {
        ch1 = fgetc(f1);
        ch2 = fgetc(f2);
        if ((ch1 == '\n') && (ch2 == '\n')) {
            str++;
        }
        if (ch1 != ch2) {
            flag_err = 1;
            break;
        }
    }
    fseek(f1, 0, SEEK_SET);
    fseek(f2, 0, SEEK_SET);
    while (str) {
        fgets(string1, 1000, f1);
        fgets(string2, 1000, f2);
        str--;
    }
    if (flag_err == 0) {
        printf("SUCCESS\n");
    } else {
        printf("ERROR\n");
        printf("  cat:%s", string1);
        printf("21cat:%s", string2);
    }
    fclose(f1);
    fclose(f2);
}
