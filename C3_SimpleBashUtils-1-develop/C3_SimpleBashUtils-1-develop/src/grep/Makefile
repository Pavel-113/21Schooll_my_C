CC=gcc
CAR=ar
CRANLIB=ranlib
LDFLAGS= -Wall -Wextra -Werror
FLAGS =-std=c11
PCRE = -lpcre

.PHONY: all clean rebuild test check
default: all

all: clean s21_grep check test
	
s21_grep: s21_grep.c
	$(CC) $(FLAGS) s21_grep.c $(PCRE) -o s21_grep

clean:
	rm -rf *.o *.out *.a s21_grep CPPLINT.cfg
test:
	bash test_grep.sh

rebuild:
	$(MAKE) clean
	$(MAKE) all

check:
	cppcheck *.h *.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	CK_FORK=no leaks --atExit -- ./s21_grep -lc zz file microfile file