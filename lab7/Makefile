CC = gcc
CFLAGS = -Wall -std=c17

all: main
main:
	gcc -Wall -c main.c
	gcc -Wall -o main main.o

posix:
	gcc -Wall -c posix.c
	gcc -Wall -o main posix.o

clean:
	rm -f main main.o posix.o

