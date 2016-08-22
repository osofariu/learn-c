SHELL = /bin/sh
CFLAGS=-Wall -g
.SUFFIXES:
.SUFFIXES: .c .o

ARGS ?= 123

valgrind: hello
	valgrind --track-origins=yes ./hello ${ARGS}

run: hello
	./hello ${ARGS}

hello: hello.o 
	$(CC) -o hello hello.o 

hello.o: hello.c
	$(CC) -I. -c hello.c

clean:
	rm -f hello hello.o
