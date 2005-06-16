#
# The scanner profiler Makefile
#

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

PROGRAM=qtscannerprofiler

ifdef USE_KDE
KDEINCLUDE=-I$(KDEDIR)/include
KDELIBDIR=-L$(KDEDIR)/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkio
PROGRAM=kscannerprofiler
endif


# some settings
INCLUDES = -I../liblprof -I../libqtlcmswidgets -I$(QT_INCDIR) -I. $(KDEINCLUDE)
LIBS     = -L$(QT_LIBDIR) -L../liblprof -L../libqtlcmswidgets $(KDELIBDIR)
CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -lqtlcmswidgets -llprof -llcms -lm
OBJECTS=main.o qtscannerprofilerdialog.o qtscannerprofilerdialogbase.o moc_qtscannerprofilerdialog.o moc_qtscannerprofilerdialogbase.o

# Targets
all: $(PROGRAM)

$(PROGRAM):  $(OBJECTS)
	@echo "Building scanner profiler ..."
	$(CC) $(LIBS) $(OBJECTS) -o $(PROGRAM) $(POSTLIB)

# general rules how to build files
%.h: %.ui
	$(UIC) -o $@ $<

moc_%.cpp: %.h
	$(MOC) $< -o $@

%.cpp: %.ui
	$(UIC) -o $@ -impl $*.h $<

%.o: %.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

main.cpp: qtscannerprofilerdialog.h

qtscannerprofilerdialog.h: qtscannerprofilerdialogbase.h

qtscannerprofilerdialog.o: qtscannerprofilerdialog.cpp qtscannerprofilerdialog.h

qtscannerprofilerdialogbase.o: qtscannerprofilerdialogbase.cpp qtscannerprofilerdialogbase.h


clean:
	rm -f moc_*.* *.o qtscannerprofilerdialogbase.cpp qtscannerprofilerdialogbase.h \
	$(PROGRAM)$(EXESUFFIX)

install: $(PROGRAM)
	-cp $(PROGRAM)$(EXESUFFIX) $(DESTDIR)$(BINDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(PROGRAM)$(EXESUFFIX)
