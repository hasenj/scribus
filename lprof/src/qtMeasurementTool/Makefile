#
# The measurement tool Makefile
#


# Assure these are defined
UIC = $(QTDIR)/bin/uic
MOC = $(QTDIR)/bin/moc
PROGRAM=qtmeasurementtool

ifdef USE_KDE
KDEINCLUDE=-I$(KDEDIR)/include
KDELIBDIR=-L$(KDEDIR)/lib
KDEFLAGS=-DUSE_KDE
KDEPOSTLIB=-lkdeui -lkdecore -lkio
PROGRAM=kmeasurementtool
endif

# some settings
INCLUDES = -I../../include -I../../../lcms-1.09/include -I$(QTDIR)/include -I. -I.. -I$(QTDIR)/include/qt $(KDEINCLUDE)
LIBS     = -L$(QTDIR)/lib -L../../src $(KDELIBDIR) -L../../../lcms-1.09/src
CFLAGS   = -O4 -Wall $(KDEFLAGS)
POSTLIB  = $(KDEPOSTLIB) -lqt-mt -llprof -llcms -lm

BINDIR   = ../../
OBJECTS=main.o qtlcmswidgets.o qtmeasurementtooldialog.o qtmeasurementtooldialogbase.o moc_qtmeasurementtooldialog.o moc_qtmeasurementtooldialogbase.o moc_qtlcmswidgets.o

# Targets
all: $(PROGRAM) install

$(PROGRAM):  $(OBJECTS)
	@echo "Building measurement tool program ..."
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

# special dependency
moc_qtlcmswidgets.cpp: ../qtlcmswidgets.h
	$(MOC) $< -o $@

qtlcmswidgets.o: ../qtlcmswidgets.cpp
	$(CC) -c $(INCLUDES) $(CFLAGS) ../qtlcmswidgets.cpp -o qtlcmswidgets.o

main.cpp: qtmeasurementtooldialog.h

qtmeasurementtooldialog.h: qtmeasurementtooldialogbase.h

qtmeasurementtooldialog.o: qtmeasurementtooldialog.cpp qtmeasurementtooldialog.h

qtmeasurementtooldialogbase.o: qtmeasurementtooldialogbase.cpp qtmeasurementtooldialogbase.h


install: $(PROGRAM)
	-cp $(PROGRAM) $(BINDIR)
# nothing to install

clean:
	rm -f moc_*.* *.o qtmeasurementtooldialogbase.cpp qtmeasurementtooldialogbase.h \
	$(PROGRAM) $(PROGRAM).exe $(BINDIR)$(PROGRAM) \
	$(BINDIR)$(PROGRAM).exe 
