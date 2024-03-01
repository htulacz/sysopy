countdown: countdown.c
	cc -c countdown.c
all: countdown.o
	cc -o countdown countdown.o
clean:
	rm countdown countdown.o

