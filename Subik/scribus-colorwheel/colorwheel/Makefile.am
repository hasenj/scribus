pluginsdir = $(prefix)/lib/scribus/plugins
AM_CPPFLAGS = -I$(prefix)/include/scribus

SUBDIRS =

plugins_LTLIBRARIES = libcolorwheel.la

INCLUDES = $(LIBFREETYPE_CFLAGS) $(all_includes)

libcolorwheel_la_LDFLAGS = -version-info 0:0:0
libcolorwheel_la_METASOURCES = AUTO
libcolorwheel_la_SOURCES = colorwheel.cpp  colorwheelwidget.cpp  cwdialog.cpp

EXTRA_DIST = colorwheel.cpp  colorwheel.h  colorwheelwidget.cpp  colorwheelwidget.h  cwdialog.cpp  cwdialog.h

KDE_OPTIONS = qtonly
AM_LDFLAGS = -s $(LIBFREETYPE_LIBS)

AM_CPPFLAGS = \
    -I$(prefix)/include/scribus \
    -DDOCDIR=\"$(datadir)/scribus/doc/\" \
    -DICONDIR=\"$(datadir)/scribus/icons/\" \
    -DSAMPLESDIR=\"$(datadir)/scribus/samples/\" \
    -DSCRIPTSDIR=\"$(datadir)/scribus/scripts/\" \
    -DTEMPLATEDIR=\"$(datadir)/scribus/templates/\" \
    -DLIBDIR=\"$(libdir)/scribus/\" \
    -DPLUGINDIR=\"$(libdir)/scribus/plugins/\"