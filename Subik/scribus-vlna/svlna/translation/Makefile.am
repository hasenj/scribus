EXTRA_DIST = libscribusvlna.cs.qm libscribusvlna.cs.ts 

install-data-local:
	$(mkinstalldirs) $(prefix)/lib/scribus/plugins/
	$(INSTALL_DATA) $(srcdir)/libscribusvlna.cs.qm $(prefix)/lib/scribus/plugins/libscribusvlna.cs.qm

uninstall-local:
	-rm -f $(prefix)/lib/scribus/plugins/libscribusvlna.cs.qm

