all: proj2.o
	g++ -std=c++11 -g -pthread -o proj2 proj2.o 

proj2.o: proj2.cpp utilities.cpp 
	g++ -std=c++11 -Wall -g -O2 -c -pthread proj2.cpp

clean:
	rm -rf proj2 *.o

