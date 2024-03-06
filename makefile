CC ?= gcc
CFLAGS ?= -Wall -std=c17 -o

.PHONY:

countdown: countdown.c
	 $(CC) $(CFLAGS) countdown countdown.c
all: countdown

clean:
	rm -f countdown

