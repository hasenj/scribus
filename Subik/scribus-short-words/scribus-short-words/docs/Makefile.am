SUBDIRS = en cs pl fr
EXTRA_DIST = index.html

install-data-local:
	$(mkinstalldirs) $(prefix)/share/scribus/doc/scribus-short-words/
	$(INSTALL_DATA) $(srcdir)/index.html $(prefix)/share/scribus/doc/scribus-short-words/index.html

uninstall-local:
	-rm -f $(prefix)/share/scribus/doc/scribus-short-words/index.html


