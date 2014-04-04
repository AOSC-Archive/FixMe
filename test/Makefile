CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: segfault

segfault:
	$(CC) -o segfault.o -c $(CFLAGS) $(CPPPATH) segfault.c         
	$(CC) -o segfault segfault.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o segfault
