pluginsdir = $(prefix)/lib/scribus/plugins
AM_CPPFLAGS = -I$(prefix)/include/scribus

SUBDIRS = config

plugins_LTLIBRARIES = libloremipsum.la

INCLUDES = $(LIBFREETYPE_CFLAGS) $(all_includes)

libloremipsum_la_LDFLAGS = -version-info 0:0:0
libloremipsum_la_METASOURCES = AUTO
libloremipsum_la_SOURCES = loremipsum.cpp

EXTRA_DIST = loremipsum.cpp loremipsum.h

KDE_OPTIONS = qtonly
AM_LDFLAGS =	-s $(LIBFREETYPE_LIBS)
