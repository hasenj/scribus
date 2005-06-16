SHELL = /bin/sh

ifndef BASEDIR
BASEDIR = $(DESTDIR)/usr/local
endif

ifndef DESTDIR
DESTDIR=
endif

ifndef BINDIR
BINDIR  = $(BASEDIR)/bin
endif

ifndef LIBDIR
LIBDIR  = $(BASEDIR)/lib
endif

ifndef INCDIR
INCDIR  = $(BASEDIR)/include
endif

ifndef EXESUFFIX
EXESUFFIX=
endif

CFLAGS = -g -O4 -fomit-frame-pointer -Wall -I../liblprof -L../liblprof
PROGRAM=icc2it8

all:	icc2it8

icc2it8: icc2it8.o getopt.o
	$(CC) $(CFLAGS) icc2it8.o getopt.o -o $@ -lm -llprof -llcms

install:
	cp $(PROGRAM)$(EXESUFFIX) $(DESTDIR)$(BINDIR)

icc2it8.o: icc2it8.c
getopt.o: getopt.c

utils:: icc2it8

clean:
	-rm icc2it8.o getopt.o $(PROGRAM)$(EXESUFFIX)

uninstall:
	-rm -f $(DESTDIR)$(BINDIR)/$(PROGRAM)$(EXESUFFIX)
