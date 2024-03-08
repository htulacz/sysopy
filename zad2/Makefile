CC = gcc
CFLAGS = -Wall -std=c17

collatz:
	$(CC) $(CFLAGS) -c collatz.c
static: collatz
	ar rc libcollatz.a collatz.o
	$(CC) $(CFLAGS) -c main.c
	$(CC) main.o libcollatz.a -o main
shared:
	$(CC) -fPIC -c collatz.c
	$(CC) -shared -Wl,-soname,libcollatz.so.1 -o libcollatz.so.1.0.1 collatz.o -lc
	ln -s libcollatz.so.1.0.1 libcollatz.so.1
	ls -s libcollatz.so.1 libcollatz.so
clean:
	rm -f *.o *.a *.so*
	rm -f main
