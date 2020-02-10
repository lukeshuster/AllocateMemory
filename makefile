.default: output
output: main.o allocate.o
	g++ -Wall -pedantic -std=c++17 main.o allocate.o -o allocate

main.o: main.cpp
	g++ -Wall -pedantic -std=c++17 -c main.cpp

allocate.o: Allocate.cpp
	g++ -Wall -pedantic -std=c++17 -c Allocate.cpp

clean:
	rm *.o allocate