CC = gcc
CFLAGS = -Wall -std=c17

collatz:
	$(CC) $(CFLAGS) -c collatz.c
static: collatz
	ar rc libcollatz.a collatz.o
	$(CC) $(CFLAGS) -c main.c
	$(CC) main.o libcollatz.a -o main
	./main
shared: main.c collatz.c
	$(CC) -fPIC -c collatz.c
	$(CC) -shared -Wl,-soname,libcollatz.so.1 -o libcollatz.so.1.0.1 collatz.o -lc
	ln -s libcollatz.so.1.0.1 libcollatz.so.1
	ln -s libcollatz.so.1 libcollatz.so
	$(CC) main.c -L./ -lcollatz -Wl,-rpath,. -o main
	./main
dynamic: main.c libcollatz_dynamic.so
	$(CC) $(CFLAGS) main.c -L./ -lcollatz_dynamic -o main
	LD_LIBRARY_PATH=. ./main
libcollatz_dynamic.so: collatz.c
	$(CC) $(CFLAGS) -shared -o libcollatz_dynamic.so collatz.c
clean:
	rm -f *.o *.a *.so*
	rm -f main
