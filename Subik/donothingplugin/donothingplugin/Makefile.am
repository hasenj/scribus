pluginsdir = $(prefix)/lib/scribus/plugins
AM_CPPFLAGS = -I$(prefix)/include/scribus

SUBDIRS =  

plugins_LTLIBRARIES = libdonothingplugin.la

INCLUDES = $(LIBFREETYPE_CFLAGS) $(all_includes)

libdonothingplugin_la_LDFLAGS = -version-info 0:0:0
libdonothingplugin_la_METASOURCES = AUTO
libdonothingplugin_la_SOURCES = myplugin.cpp

EXTRA_DIST = myplugin.cpp myplugin.h

KDE_OPTIONS = qtonly
AM_LDFLAGS =	-s $(LIBFREETYPE_LIBS)
