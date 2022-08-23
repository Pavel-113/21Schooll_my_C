CC=gcc
CAR=ar
CRANLIB=ranlib
LDFLAGS= -Wall -Wextra -Werror
FLAGS =-std=c11

.PHONY: all clean rebuild test check
default: all

all: clean s21_cat check test
	
s21_cat: s21_cat.c
	$(CC) $(FLAGS) $(LDFLAGS) s21_cat.c -o s21_cat

clean:
	rm -rf *.o *.out *.a s21_cat CPPLINT.cfg
test:
	bash test_cat.sh

rebuild:
	$(MAKE) clean
	$(MAKE) all

check:
	cppcheck *.h *.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	CK_FORK=no leaks --atExit -- ./s21_cat file