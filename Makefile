CC = gcc

all: scanner

scanner: main.o scanner.o
	$(CC) -o scanner main.o scanner.o

main.o: main.c scanner.h
	$(CC) -c main.c

scanner.o: scanner.c scanner.h
	$(CC) -c scanner.c

clean:
	rm -f *.o scanner

