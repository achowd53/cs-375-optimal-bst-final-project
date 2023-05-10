all: main

main: main.o BST.o oBST.o
	g++ main.o BST.o oBST.o -o main

main.o: main.cpp
	g++ -c main.cpp

BST.o: BST.cpp BST.h
	g++ -c BST.cpp

oBST.o: oBST.cpp oBST.h
	g++ -c oBST.cpp

clean:
	rm main *.o ``