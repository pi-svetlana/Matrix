CC=g++
UNAME= $(shell uname -s)
CFLAG=-Wall -Werror -Wextra -std=c++17 -lstdc++
LIB_FLAG=ar rvs
CFLAGS_TEST= -lgtest -lgtest_main -pthread

all: matrix_oop.a

matrix_oop.o:
	$(CC) $(CFLAG) -c *.cc

matrix_oop.a: matrix_oop.o
	$(LIB_FLAG) matrix_oop.a *.o
	rm -f ./*.o

tests: matrix_oop.a
	$(CC) -g *.cc ../tests/tests.cc $(CFLAGS_TEST) -L /usr/local/lib -o matrix_test
	clear
	./matrix_test

leaks: test
ifeq ($(shell uname -s), Linux)
	valgrind --leak-check=full --track-origins=yes --undef-value-errors=yes ./matrix_test
else
	CK_FORK=no leaks --atExit -- ./matrix_test
endif

test.o:
	$(CC) $(CFLAGS) -c ../tests/tests.cc -o test.o

gcov_report: test.o
	$(CC) test.o matrix_oop.cc $(CFLAGS_TEST) --coverage -o test -lgtest
	./test
	gcovr -r . --html --html-details -f ".+\.cc" -o gcov_report.html
ifeq ($(shell uname -s), Linux)
	xdg-open gcov_report.html
else
	open gcov_report.html
endif

clang-check:
	clang-format -n --style=Google *.cc *.h ../tests/*.cc

clang-format:
	clang-format -i --style=Google *.cc *.h ../tests/*.cc

clean:
	rm -f *.o *.a test matrix_test *.txt
	rm -f *.out *.gcda *.gcno *.info
	rm -rf *.dSYM report gcov*