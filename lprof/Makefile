SHELL = /bin/sh

init: FORCE
	@$(MAKE) all

all install clean test:: 
	@echo "little cms profiler construction set 1.09 being made $@."
	@echo "please wait ..."
	( cd src ; $(MAKE) $@ )
	( cd ICCtoIT8 ; $(MAKE) $@ )
	( cd qt/qtMeasurementTool; $(MAKE) $@ )
	( cd qt/qtMonitorProfiler; $(MAKE) $@ )
	( cd qt/qtScannerProfiler; $(MAKE) $@ )
	( cd qt/qtProfileChecker;  $(MAKE) $@ )

FORCE:


