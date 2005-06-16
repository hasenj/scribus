#
# The measurement tool Makefile

# Assure these are defined
UIC = $(QTDIR)/bin/uic
MOC = $(QTDIR)/bin/moc

ifdef USE_KDE
KDEINCLUDE=-I$(KDEDIR)/include
KDELIBDIR=-L$(KDEDIR)/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkio
PROGRAM=kmeasurementtool
endif

# some settings
INCLUDES = -I../liblprof/ -I../../include -I../../../lcms-1.09/include -I$(QTDIR)/include -I. -I.. -I$(QTDIR)/include/qt $(KDEINCLUDE)
LIBS     = -L$(QTDIR)/lib -L../liblprof -L../../src $(KDELIBDIR) -L../../../lcms-1.09/src
CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -llprof -llcms -lm

BINDIR  = ../../

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
	rm -f moc_*.* *.o qtlcmswidgets.o
