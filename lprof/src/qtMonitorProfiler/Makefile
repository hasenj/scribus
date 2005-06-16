#
# The monitor profiler Makefile
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

PROGRAM=qtmonitorprofiler

ifdef USE_KDE
KDEINCLUDE=-I$(KDEDIR)/include
KDELIBDIR=-L$(KDEDIR)/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkio
PROGRAM=kmonitorprofiler
endif


# some settings
INCLUDES = -I../liblprof -I../libqtlcmswidgets -I$(QT_INCDIR) -I. $(KDEINCLUDE)
LIBS     = -L$(QT_LIBDIR) -L../liblprof -L../libqtlcmswidgets $(KDELIBDIR)
CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -lqtlcmswidgets -llprof -llcms -lm
OBJECTS=main.o qtmonitorprofilerdialog.o qtmonitorprofilerdialogbase.o moc_qtmonitorprofilerdialog.o moc_qtmonitorprofilerdialogbase.o

# Targets
all: $(PROGRAM)

$(PROGRAM):  $(OBJECTS)
	@echo "Building monitor profiler ..."
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

main.cpp: qtmonitorprofilerdialog.h

qtmonitorprofilerdialog.h: qtmonitorprofilerdialogbase.h

qtmonitorprofilerdialog.o: qtmonitorprofilerdialog.cpp qtmonitorprofilerdialog.h

qtmonitorprofilerdialogbase.o: qtmonitorprofilerdialogbase.cpp qtmonitorprofilerdialogbase.h

clean:
	rm -f moc_*.* *.o qtmonitorprofilerdialogbase.cpp qtmonitorprofilerdialogbase.h \
	$(PROGRAM)$(EXESUFFIX)

install: $(PROGRAM)
	cp $(PROGRAM)$(EXESUFFIX) $(DESTDIR)$(BINDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(PROGRAM)$(EXESUFFIX)
