#include <stdio.h>
#include <string.h>

void main() {
    FILE *f1 = fopen("file1", "r");
    FILE *f2 = fopen("file2", "r");
    int ch1 = 0;
    int ch2 = 0;
    int str = 1;
    int flag_err = 0;

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
    if (flag_err == 0) {
        printf("SUCCESS\n");
    } else {
        printf("ERROR\n");
    }
    fclose(f1);
    fclose(f2);
}
