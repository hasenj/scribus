SHELL = /bin/sh

init: FORCE
	@$(MAKE) all

ifndef BASEDIR
BASEDIR = /usr/local
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

ifndef DOCDIR
DOCDIR  = $(BASEDIR)/share/doc/lprof
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

all:

clean:

test:

install:
	mkdir -p $(DESTDIR)$(DOCDIR)
	cp manual.txt $(DESTDIR)$(DOCDIR)

uninstall:
	rm -f $(DESTDIR)$(DOCDIR)/manual.txt

FORCE:
