CC = gcc
CFLAGS = -Wall -std=c17

.PHONY: all clean

all: program1 program2

program1: zad1.o
	$(CC) $(CFLAGS) -o main1 zad1.o -lm

program2: zad2.o
	$(CC) $(CFLAGS) -o main2 zad2.o -lm

zad1.o: zad1.c
	$(CC) $(CFLAGS) -c zad1.c

zad2.o: zad2.c
	$(CC) $(CFLAGS) -c zad2.c

clean:
	rm -f main1 main2 zad1.o zad2.o
