CC = clang++ 
CFLAGS = -Wall -g -std=c++11

testmain: tests-main.o tests-MSMap.o ../src/MSMap.o ../src/utils.o
	$(CC) $(CFLAGS) -o testmain tests-main.o tests-MSMap.o ../src/MSMap.o ../src/utils.o

tests-main.o: tests-main.cpp catch.hpp
	$(CC) $(CFLAGS) -c tests-main.cpp

tests-MSMap.o: tests-MSMap.cpp tests-main.cpp
	$(CC) $(CFLAGS) -c tests-MSMap.cpp

clean:
	rm testmain *.o