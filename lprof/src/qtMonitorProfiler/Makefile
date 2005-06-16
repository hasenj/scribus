#
# The monitor profiler Makefile
#


# Assure these are defined
UIC = $(QTDIR)/bin/uic
MOC = $(QTDIR)/bin/moc
PROGRAM=qtmonitorprofiler

ifdef USE_KDE
KDEINCLUDE=-I$(KDEDIR)/include
KDELIBDIR=-L$(KDEDIR)/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkio
PROGRAM=kmonitorprofiler
endif


# some settings
INCLUDES = -I../../include -I../liblprof -I../qtlcmswidgets -I../../../lcms-1.09/include -I$(QTDIR)/include -I. -I.. -I$(QTDIR)/include/qt  $(KDEINCLUDE)
LIBS     = -L$(QTDIR)/lib -L../liblprof -L../qtlcmswidgets -L../../src $(KDELIBDIR) -L../../../lcms-1.09/src
CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -lqtlcmswidgets -llprof -llcms -lm
BINDIR   = ../../
OBJECTS=main.o qtmonitorprofilerdialog.o qtmonitorprofilerdialogbase.o moc_qtmonitorprofilerdialog.o moc_qtmonitorprofilerdialogbase.o

# Targets
all: $(PROGRAM) install

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


install: $(PROGRAM)
	-cp $(PROGRAM) $(BINDIR)

clean:
	rm -f moc_*.* *.o qtmonitorprofilerdialogbase.cpp qtmonitorprofilerdialogbase.h $(PROGRAM) $(PROGRAM).exe $(BINDIR)$(PROGRAM) $(BINDIR)$(PROGRAM).exe
