SHELL = /bin/sh

ifndef BASEDIR
BASEDIR = $(DESTDIR)/usr/local
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

all:	icc2it8

icc2it8: icc2it8.o getopt.o
	$(CC) $(CFLAGS) icc2it8.o getopt.o -o $@ -lm -llprof -llcms

install:
	cp icc2it8$(EXESUFFIX) $(BINDIR)

icc2it8.o: icc2it8.c
getopt.o: getopt.c

utils:: icc2it8

clean:
	-rm icc2it8.o getopt.o icc2it8$(EXESUFFIX)

uninstall:
	-rm -f $(BINDIR)/icc2it8$(EXESUFFIX)
