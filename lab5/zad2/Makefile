CC = gcc
CFLAGS = -Wall -std=c17

all: zad
zad:
	gcc -Wall -c catcher.c
	gcc -Wall -c sender.c
	gcc -Wall catcher catcher.o
	gcc -Wall sender sender.o

clean:
	rm -f catcher catcher.o sender sender.o

