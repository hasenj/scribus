SHELL = /bin/sh

CFLAGS = -g -O4 -fomit-frame-pointer -Wall -I../include -I../../lcms-1.09/include -I/usr/include -I/usr/local/include
BASEDIR = $(DESTDIR)/usr
BINDIR  = ..


all:	icc2it8

icc2it8: icc2it8.o getopt.o
	$(CC) $(CFLAGS) icc2it8.o getopt.o ../src/liblprof.a -o $@ -lm -llcms
	-cp icc2it8 $(BINDIR)
	-cp icc2it8.exe $(BINDIR)

icc2it8.o: icc2it8.c
getopt.o: getopt.c

install utils:: icc2it8
	
clean:
	-rm icc2it8.o getopt.o icc2it8 icc2it8.exe 

	
