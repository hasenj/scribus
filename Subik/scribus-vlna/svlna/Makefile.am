pluginsdir = $(prefix)/lib/scribus/plugins
AM_CPPFLAGS = -I$(prefix)/include/scribus

SUBDIRS = translation doc 

plugins_LTLIBRARIES = libscribusvlna.la

INCLUDES = $(LIBFREETYPE_CFLAGS) $(all_includes)

libscribusvlna_la_LDFLAGS = -version-info 0:0:0
libscribusvlna_la_METASOURCES = AUTO
libscribusvlna_la_SOURCES = frame.cpp selection.cpp vlnadialog.cpp vlnapage.cpp svlna.cpp 

EXTRA_DIST = frame.cpp selection.cpp svlna.cpp vlnadialog.cpp vlnapage.cpp frame.h selection.h svlna.h vlnadialog.h vlnapage.h vlnadialog.ui 

KDE_OPTIONS = qtonly
AM_LDFLAGS =	-s $(LIBFREETYPE_LIBS)
