countdown: countdown.c
	gcc -c countdown countdown.c
all: countdown.o
	gcc -o countdown countdown.c
clean:
	rm countdown countdown.o

