pluginsdir = $(prefix)/lib/scribus/plugins
AM_CPPFLAGS = -I$(prefix)/include/scribus

SUBDIRS = config

plugins_LTLIBRARIES = libloremipsum.la

INCLUDES = $(LIBFREETYPE_CFLAGS) $(all_includes)

libloremipsum_la_LDFLAGS = -version-info 0:0:0
libloremipsum_la_METASOURCES = AUTO
libloremipsum_la_SOURCES = loremconfig.cpp loremipsum.cpp loremnetwork.cpp loremturkey.cpp loremdialog.cpp loremstandard.cpp

EXTRA_DIST = loremconfig.cpp loremconfig.h loremipsum.cpp loremipsum.h loremnetwork.cpp loremnetwork.h loremturkey.cpp  loremturkey.h loremdialog.cpp loremdialog.h loremdialog.ui.h loremstandard.cpp loremstandard.h

KDE_OPTIONS = qtonly
AM_LDFLAGS =	-s $(LIBFREETYPE_LIBS)
