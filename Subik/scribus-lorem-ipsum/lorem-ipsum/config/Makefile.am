EXTRA_DIST = lorem-ipsum.xml turkey-bass.txt turkey-czech-ascii.txt turkey-czech.txt turkey-default.txt

install-data-local:
	$(mkinstalldirs) $(prefix)/share/scribus/lorem-ipsum/
	$(INSTALL_DATA) $(srcdir)/lorem-ipsum.xml $(prefix)/share/scribus/lorem-ipsum/lorem-ipsum.xml
	$(mkinstalldirs) $(prefix)/share/scribus/lorem-ipsum/
	$(INSTALL_DATA) $(srcdir)/turkey-bass.txt $(prefix)/share/scribus/lorem-ipsum/turkey-bass.txt
	$(mkinstalldirs) $(prefix)/share/scribus/lorem-ipsum/
	$(INSTALL_DATA) $(srcdir)/turkey-czech-ascii.txt $(prefix)/share/scribus/lorem-ipsum/turkey-czech-ascii.txt
	$(mkinstalldirs) $(prefix)/share/scribus/lorem-ipsum/
	$(INSTALL_DATA) $(srcdir)/turkey-czech.txt $(prefix)/share/scribus/lorem-ipsum/turkey-czech.txt
	$(mkinstalldirs) $(prefix)/share/scribus/lorem-ipsum/
	$(INSTALL_DATA) $(srcdir)/turkey-default.txt $(prefix)/share/scribus/lorem-ipsum/turkey-default.txt

uninstall-local:
	-rm -f $(prefix)/share/scribus/lorem-ipsum/lorem-ipsum.xml
	-rm -f $(prefix)/share/scribus/lorem-ipsum/turkey-bass.txt
	-rm -f $(prefix)/share/scribus/lorem-ipsum/turkey-czech-ascii.txt
	-rm -f $(prefix)/share/scribus/lorem-ipsum/turkey-czech.txt
	-rm -f $(prefix)/share/scribus/lorem-ipsum/turkey-default.txt
