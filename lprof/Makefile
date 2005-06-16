SHELL = /bin/sh

init: FORCE
	@$(MAKE) -s all

all install clean test:: 
	@echo "little cms profiler construction set 1.09 being made $@."
	@echo "please wait ..."
	cd src ; $(MAKE) $@ ; cd .. 
	cd ICCtoIT8 ; $(MAKE) $@ ; cd .. 
	cd qt/qtMeasurementTool; $(MAKE) $@ ; cd ../.. 	
	cd qt/qtMonitorProfiler; $(MAKE) $@ ; cd ../.. 	
	cd qt/qtScannerProfiler; $(MAKE) $@ ; cd ../.. 	
	cd qt/qtProfileChecker;  $(MAKE) $@ ; cd ../.. 	

FORCE:


