all: tree
tree: LLRBTree.o main.o 
	gcc -o tree LLRBTree.o main.o

LLRBTree.o: LLRBTree.c
	gcc -o LLRBTree.o -c LLRBTree.c -W -Wall -ansi -pedantic
main.o: main.c LLRBTree.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

run:
	./tree
clean:
	rm -rf *.o teste # myfile
