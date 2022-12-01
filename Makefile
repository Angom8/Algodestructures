CC = gcc -Wall -O3
OBJETS = main.o Genetic.o Graph.o List.o Cell.o Sommet.o Pile.o File.o Heap.o Ridge.o Set.o

main: $(OBJETS)
	$(CC) -o main $(OBJETS)

main.o : main.c Genetic.h
	$(CC) -c main.c
	
Genetic.o : Genetic.c Genetic.h Graph.h
	$(CC) -c Genetic.c	
	
Graph.o : Graph.c Graph.h List.h Heap.h File.h Set.h
	$(CC) -c Graph.c

Heap.o : Heap.c Heap.h Ridge.h
	$(CC) -c Heap.c
	
File.o : File.c File.h Pile.h
	$(CC) -c File.c
	
List.o : List.c List.h Cell.h
	$(CC) -c List.c
	
Pile.o : Pile.c Pile.h Sommet.h
	$(CC) -c Pile.c
	
Cell.o : Cell.c Cell.h
	$(CC) -c Cell.c
	
Sommet.o : Sommet.c Sommet.h
	$(CC) -c Sommet.c

Set.o : Set.c Set.h
	$(CC) -c Set.c
	
Ridge.o : Ridge.c Ridge.h
	$(CC) -c Ridge.c

clean:
	rm main *.o
