all: main

main: main.o BST.o
	g++ main.o BST.o -o main

main.o: main.cpp
	g++ -c main.cpp

BST.o: BST.cpp BST.h
	g++ -c BST.cpp

clean:
	rm main *.o 