#
# The scanner profiler Makefile
#


# Assure these are defined
UIC = $(QTDIR)/bin/uic
MOC = $(QTDIR)/bin/moc
PROGRAM=qtprofilechecker

ifdef USE_KDE
KDEINCLUDE=-I/usr/include/kde -I/usr/local/kde1/include
KDELIBDIR=-L/usr/local/kde1/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkfile
PROGRAM=kprofilechecker
endif


# some settings
INCLUDES = -I../../include -I../liblprof -I../qtlcmswidgets -I../../../lcms-1.09/include -I$(QTDIR)/include -I. -I.. -I$(QTDIR)/include/qt  $(KDEINCLUDE)
LIBS     = -L$(QTDIR)/lib -L../liblprof -L../qtlcmswidgets -L../../src $(KDELIBDIR) -L../../../lcms-1.09/src

CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -lqtlcmswidgets -llprof -llcms -lm
BINDIR   = ../../
OBJECTS=main.o qtdrawcurve.o qtcietonge.o qtprofilecheckerdialog.o qtprofilecheckerdialogbase.o moc_qtprofilecheckerdialog.o moc_qtprofilecheckerdialogbase.o

# Targets
all: $(PROGRAM) install

$(PROGRAM):  $(OBJECTS)
	@echo "Building profile checker ..."
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

main.cpp: qtprofilecheckerdialog.h

qtprofilecheckerdialog.h: qtprofilecheckerdialogbase.h

qtprofilecheckerdialog.o: qtprofilecheckerdialog.cpp qtprofilecheckerdialog.h

qtprofilecheckerdialogbase.o: qtprofilecheckerdialogbase.cpp qtprofilecheckerdialogbase.h

qtdrawcurve.o: qtdrawcurve.cpp

qtcietonge.o: qtcietonge.cpp


install: $(PROGRAM)
	-cp $(PROGRAM) $(BINDIR)

clean:
	rm -f moc_*.* *.o qtprofilecheckerdialogbase.cpp qtprofilecheckerdialogbase.h $(PROGRAM) $(PROGRAM).exe $(BINDIR)$(PROGRAM) $(BINDIR)$(PROGRAM).exe
