#
# The measurement tool Makefile

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

ifndef QTDIR
QTDIR=/usr
endif

ifndef QT_BINDIR
QT_BINDIR=$(QTDIR)/bin
endif

ifndef MOC
MOC=$(QT_BINDIR)/moc
endif

ifndef UIC
UIC=$(QT_BINDIR)/uic
endif

ifndef QT_INCDIR
QT_INCDIR=$(QTDIR)/include
endif

ifndef QT_LIBDIR
QT_LIBDIR=$(QTDIR)/lib
endif

ifndef EXESUFFIX
EXESUFFIX=
endif

ifdef USE_KDE
KDEINCLUDE=-I$(KDEDIR)/include
KDELIBDIR=-L$(KDEDIR)/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkio
PROGRAM=kmeasurementtool
endif

# some settings
INCLUDES = -I../liblprof/ -I. -I$(QT_INCDIR) $(KDEINCLUDE)
LIBS     = -L$(QT_LIBDIR) -L../liblprof $(KDELIBDIR)
CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -llprof -llcms -lm

all: libqtlcmswidgets.a

# general rules how to build files
%.h: %.ui
	$(UIC) -o $@ $<

moc_%.cpp: %.h
	$(MOC) $< -o $@

%.cpp: %.ui
	$(UIC) -o $@ -impl $*.h $<

%.o: %.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

# special dependency
moc_qtlcmswidgets.cpp: qtlcmswidgets.h
	$(MOC) $< -o $@

moc_qtlcmswidgets.o: moc_qtlcmswidgets.cpp
	$(CC) -c $(INCLUDES) $(CFLAGS) moc_qtlcmswidgets.cpp -o moc_qtlcmswidgets.o

qtlcmswidgets.o: qtlcmswidgets.cpp qtlcmswidgets.h moc_qtlcmswidgets.cpp
	$(CC) -c $(INCLUDES) $(CFLAGS) qtlcmswidgets.cpp -o qtlcmswidgets.o

libqtlcmswidgets.a: qtlcmswidgets.o moc_qtlcmswidgets.o
	ar -cru libqtlcmswidgets.a moc_qtlcmswidgets.o qtlcmswidgets.o
	ranlib libqtlcmswidgets.a

clean:
	rm -f moc_*.* *.o qtlcmswidgets.o liblcmswidgets.a

install:
	cp libqtlcmswidgets.a $(DESTDIR)$(LIBDIR)

uninstall:
	rm -f $(DESTDIR)$(LIBDIR)/libqtlcmswidgets.a
