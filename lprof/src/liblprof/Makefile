SHELL = /bin/sh

CFLAGS  = -g -O4 -I../include -I../../lcms-1.09/include -fomit-frame-pointer -Wall 
BASEDIR = $(DESTDIR)/usr
BINDIR  = $(BASEDIR)/bin
LIBDIR  = $(BASEDIR)/lib
INCDIR  = $(BASEDIR)/include
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
	cp ../include/lcmsprf.h $(INCDIR)
	chmod 644 $(INCDIR)/lcmsprf.h

test:
	# we are doing nothing for the test target

clean:
	-rm $(OBJS) liblprof.a 
