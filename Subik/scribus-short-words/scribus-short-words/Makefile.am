pluginsdir = $(prefix)/lib/scribus/plugins
AM_CPPFLAGS = -I$(prefix)/include/scribus

SUBDIRS = translation cfg docs

plugins_LTLIBRARIES = libscribusshortwords.la

INCLUDES = $(LIBFREETYPE_CFLAGS) $(all_includes)

libscribusshortwords_la_LDFLAGS = -version-info 0:0:0
libscribusshortwords_la_METASOURCES = AUTO
libscribusshortwords_la_SOURCES = vlnadialog.cpp parse.cpp shortwords.cpp configuration.cpp version.h

EXTRA_DIST = parse.h vlnadialog.h shortwords.h version.h configuration config.h

KDE_OPTIONS = qtonly
AM_LDFLAGS =	-s $(LIBFREETYPE_LIBS)

AM_CPPFLAGS = \
    -I$(prefix)/include/scribus \
    -DDOCDIR=\"$(datadir)/scribus/doc/\" \
    -DICONDIR=\"$(datadir)/scribus/icons/\" \
    -DSAMPLESDIR=\"$(datadir)/scribus/samples/\" \
    -DSCRIPTSDIR=\"$(datadir)/scribus/scripts/\" \
    -DTEMPLATEDIR=\"$(datadir)/scribus/templates/\" \
    -DLIBDIR=\"$(libdir)/scribus/\" \
    -DPLUGINDIR=\"$(libdir)/scribus/plugins/\"