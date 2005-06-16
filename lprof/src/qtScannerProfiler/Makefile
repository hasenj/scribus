#
# The scanner profiler Makefile
#


# Assure these are defined
UIC = $(QTDIR)/bin/uic
MOC = $(QTDIR)/bin/moc
PROGRAM=qtscannerprofiler

ifdef USE_KDE
KDEINCLUDE=-I$(KDEDIR)/include
KDELIBDIR=-L$(KDEDIR)/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkio
PROGRAM=kscannerprofiler
endif


# some settings
INCLUDES = -I../../bininclude -I../liblprof -I../libqtlcmswidgets -I../../../lcms-1.09/include -I$(QTDIR)/include -I. -I.. -I$(QTDIR)/include/qt  $(KDEINCLUDE)
LIBS     = -L$(QTDIR)/lib -L../liblprof -L../libqtlcmswidgets -L../../binsrc $(KDELIBDIR) -L../../../lcms-1.09/src
CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -lqtlcmswidgets -llprof -llcms -lm
BINDIR   = ../../bin
OBJECTS=main.o qtscannerprofilerdialog.o qtscannerprofilerdialogbase.o moc_qtscannerprofilerdialog.o moc_qtscannerprofilerdialogbase.o

# Targets
all: $(PROGRAM) install

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


install: $(PROGRAM)
	-cp $(PROGRAM) $(BINDIR)

clean:
	rm -f moc_*.* *.o qtscannerprofilerdialogbase.cpp qtscannerprofilerdialogbase.h $(PROGRAM) $(PROGRAM).exe $(BINDIR)$(PROGRAM) $(BINDIR)$(PROGRAM).exe
