CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC
CPPPATH	=
LIBPATH	=
LIBS	= -lsystemd-journal

all: segfault test_systemd_journal

segfault:
	$(CC) -o segfault.o -c $(CFLAGS) $(CPPPATH) segfault.c         
	$(CC) -o segfault segfault.o $(LIBPATH) $(LIBS)

test_systemd_journal:
	$(CC) -o test_systemd_journal.o -c $(CFLAGS) $(CPPPATH) test_systemd_journal.c
	$(CC) -o test_systemd_journal test_systemd_journal.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o segfault test_systemd_journal
