CC = clang++
CFLAGS = -Wall -g -std=c++11

main: main.o MSMap.o utils.o
	$(CC) $(CFLAGS) -o main main.o MSMap.o utils.o

main.o: main.cpp MSMap.hpp
	$(CC) $(CFLAGS) -c main.cpp 

MSMap.o: MSMap.hpp utils.hpp
	$(CC) $(CFLAGS) -c MSMap.cpp 

utils.o: utils.hpp 
	$(CC) $(CFLAGS) -c utils.cpp 

clean: 
	rm main *.o