pluginsdir = $(prefix)/lib/scribus/plugins
AM_CPPFLAGS = -I$(prefix)/include/scribus

SUBDIRS =

plugins_LTLIBRARIES = libindex.la

INCLUDES = $(LIBFREETYPE_CFLAGS) $(all_includes)

libindex_la_LDFLAGS = -version-info 0:0:0
libindex_la_METASOURCES = AUTO
libindex_la_SOURCES = index.cpp indexdialog.cpp

EXTRA_DIST = index.cpp index.h indexdialog.h indexdialog.cpp indexdialog.ui.h

KDE_OPTIONS = qtonly
AM_LDFLAGS =	-s $(LIBFREETYPE_LIBS)
