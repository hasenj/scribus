SHELL = /bin/sh

init: FORCE
	@$(MAKE) all

ifndef BASEDIR
BASEDIR = $(DESTDIR)/usr/local
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

MAKEARGS=BASEDIR=$(BASEDIR) LIBDIR=$(LIBDIR) BINDIR=$(BINDIR) INCDIR=$(INCDIR) QTDIR=$(QTDIR) QT_BINDIR=$(QT_BINDIR) UIC=$(UIC) MOC=$(MOC) QT_INCDIR=$(QT_INCDIR) QT_LIBDIR=$(QT_LIBDIR) EXESUFFIX=$(EXESUFFIX)

all install clean test:: 
	@echo "little cms profiler construction set 1.09 being made $@."
	@echo "please wait ..."
	( cd src ; $(MAKE) $(MAKEARGS) $@ )

FORCE:


