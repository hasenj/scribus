SHELL = /bin/sh

CFLAGS  = -g -O4 -fomit-frame-pointer -Wall

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

test:
	# we are doing nothing for the test target

clean:
	-rm -f $(OBJS) liblprof.a

install: liblprof.a
	mkdir -p $(DESTDIR)$(BINDIR) $(DESTDIR)$(LIBDIR) $(DESTDIR)$(INCDIR)
	cp -a liblprof.a $(DESTDIR)$(LIBDIR)
	cp lcmsprf.h $(DESTDIR)$(INCDIR)
	chmod 644 $(DESTDIR)$(INCDIR)/lcmsprf.h

uninstall:
	-rm -f $(DESTDIR)$(LIBDIR)/liblprof.a $(DESTDIR)$(INCDIR)/lcmsprf.h
