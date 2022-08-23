.PHONY: all clean test s21_matrix.a check gcov_report valgrind_check
CC=gcc
VG=-O0 -g
CFLAGS=-c 
LDFLAGS= -std=c11 -Wall -Wextra -Werror

default: clean all

all: s21_matrix.a check test 

test: s21_matrix.a
	$(CC) $(LDFLAGS) s21_matrix_test.c s21_matrix.a -o test  `pkg-config --cflags --libs check`
	./test

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib $@
	cp $@ lib$@
	ranlib lib$@

s21_matrix.o: s21_matrix.c 
	$(CC) $(LDFLAGS) $(CFLAGS) -o s21_matrix.o s21_matrix.c

clean:
	rm -rf a.out test vgcheck *.a *.o *.out *.cfg *.gc* *.info report CPPLINT.cfg

rebuild: clean all

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck *.h *.c
# CK_FORK=no leaks --atExit -- ./test

gcov_report: 
	$(CC) --coverage $(LDFLAGS) s21_matrix_test.c s21_matrix.c -o test `pkg-config --cflags --libs check`
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

valgrind:
	$(CC) $(VG) s21_matrix_test.c s21_matrix.c -o vgcheck `pkg-config --cflags --libs check`
	valgrind --leak-check=yes ./vgcheck
