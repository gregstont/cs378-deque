all:

clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  TestDeque

config:
	doxygen -g

TestDeque: Deque.h TestDeque.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread

