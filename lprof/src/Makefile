SHELL = /bin/sh

init: FORCE
	@$(MAKE) all

all install clean test::
	( cd liblprof ; $(MAKE) $@ )
	( cd ICCtoIT8 ; $(MAKE) $@ )
	( cd qtMeasurementTool; $(MAKE) $@ )
	( cd qtMonitorProfiler; $(MAKE) $@ )
	( cd qtScannerProfiler; $(MAKE) $@ )
	( cd qtProfileChecker;  $(MAKE) $@ )

FORCE:


