SHELL = /bin/sh

CFLAGS  = -g -O4 -fomit-frame-pointer -Wall

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

VERSION = 1.09

.c.o:	
	$(CC) $(CFLAGS) $(LDFLAGS) -c $<

SRCS = cmshull.c cmslm.c cmslnr.c cmsmatn.c cmsmkmsh.c cmsmntr.c cmsoutl.c \
	 cmspcoll.c cmsprf.c cmsreg.c cmsscn.c cmssheet.c 

OBJS = $(SRCS:.c=.o)

all:	liblprof.a

liblprof.a: $(OBJS)
	ar -cru liblprof.a $(OBJS)
	ranlib liblprof.a

install: liblprof.a
	mkdir -p $(BINDIR) $(LIBDIR) $(INCDIR)
	cp -a liblprof.a $(LIBDIR)
	cp lcmsprf.h $(INCDIR)
	chmod 644 $(INCDIR)/lcmsprf.h

test:
	# we are doing nothing for the test target

clean:
	-rm -f $(OBJS) liblprof.a

uninstall:
	-rm -f $(LIBDIR)/liblprof.a $(INCDIR)/lcmsprf.h
