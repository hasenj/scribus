
EXTRA_DIST = scribus-vlna.rc

install-data-local:
	$(mkinstalldirs) $(prefix)/lib/scribus/plugins/
	$(INSTALL_DATA) $(srcdir)/scribus-short-words.rc $(prefix)/lib/scribus/plugins/scribus-short-words.rc

uninstall-local:
	-rm -f $(prefix)/lib/scribus/plugins/scribus-short-words.rc
