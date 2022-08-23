.PHONY: all clean tests check valgrind_check gcov_report dvi dist rebuild install uninstall 
CC=gcc
FLAGS =-std=c11
#LDFLAGS=-Wall -Wextra -Werror 
LIBFLAGS=`pkg-config --cflags --libs check` -lm
CFILES= s21_calc.c parser.c stack.c notacion.c test.c
QDIR= SmartCalc
DDIR= SmartCalc_1.0
.PHONY: install clean all

all: clean tests install
	./$(QDIR)/qt_calculator.app/Contents/MacOS/qt_calculator
	
tests:
	$(CC) $(LDFLAGS) $(CFLAGS) $(CFILES) -o calc.o $(LIBFLAGS)
	./calc.o

clean:
	rm -rf *.o *.out *.cfg *.tar report manual

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	rm -rf *.o *.out *.cfg

leaks:
	$(CC) $(LDFLAGS) $(CFLAGS) $(CFILES) -o calc.o $(LIBFLAGS) 
	./calc.o
	CK_FORK=no leaks --atExit -- ./calc.o
	
valgrind_check:  
	$(CC) -O0 -g $(CFILES) -o $(LIBFLAGS)
	valgrind --leak-check=full --track-origins=yes ./parser.o -n file
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./parser.o -n file

install:
	mkdir $(QDIR)
	cd $(QDIR); qmake ../qt_project/qt_calculator/qt_calculator.pro
	cd $(QDIR); make
	cd $(QDIR); make clean

uninstall: 
	rm -r $(QDIR)

dist:
	mkdir $(DDIR)
	mkdir $(DDIR)/qt_project
	cp *.c *.h Makefile $(DDIR)
	cp -R qt_project $(DDIR)
	tar --totals -cvf $(DDIR).tar $(DDIR)
	rm -rf $(DDIR)

gcov_report: 
	$(CC) --coverage $(LDFLAGS) $(CFILES) -o calc.o $(LIBFLAGS)
	./calc.o
	lcov -o calc.info -c -d ./ --no-external
	genhtml -o report calc.info
	open report/index.html
	rm -rf *.gcno *.gcda *.info

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html