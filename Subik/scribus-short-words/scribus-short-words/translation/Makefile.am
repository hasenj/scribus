EXTRA_DIST = llibscribusshortwords.cs.qm libscribusshortwords.cs.ts libscribusshortwords.pl.qm libscribusshortwords.pl.ts libscribusshortwords.fr.qm libscribusshortwords.fr.ts libscribusshortwords.sk.qm libscribusshortwords.sk.ts

install-data-local:
	$(mkinstalldirs) $(prefix)/lib/scribus/plugins/
	$(INSTALL_DATA) $(srcdir)/libscribusshortwords.cs.qm $(prefix)/lib/scribus/plugins/libscribusshortwords.cs.qm
	$(mkinstalldirs) $(prefix)/lib/scribus/plugins/
	$(INSTALL_DATA) $(srcdir)/libscribusshortwords.pl.qm $(prefix)/lib/scribus/plugins/libscribusshortwords.pl.qm
	$(mkinstalldirs) $(prefix)/lib/scribus/plugins/
	$(INSTALL_DATA) $(srcdir)/libscribusshortwords.fr.qm $(prefix)/lib/scribus/plugins/libscribusshortwords.fr.qm
	$(mkinstalldirs) $(prefix)/lib/scribus/plugins/
	$(INSTALL_DATA) $(srcdir)/libscribusshortwords.sk.qm $(prefix)/lib/scribus/plugins/libscribusshortwords.sk.qm
	
uninstall-local:
	-rm -f $(prefix)/lib/scribus/plugins/libscribusshortwords.cs.qm
	-rm -f $(prefix)/lib/scribus/plugins/libscribusshortwords.pl.qm
	-rm -f $(prefix)/lib/scribus/plugins/libscribusshortwords.fr.qm
	-rm -f $(prefix)/lib/scribus/plugins/libscribusshortwords.sk.qm
