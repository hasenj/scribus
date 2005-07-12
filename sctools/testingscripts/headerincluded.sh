#!/bin/sh
##
# Name: possible double inclusion
# Description: A possible double inclusion in possible for headers that don't include #ifndef
# ToResolve: Add #ifndef FILENAME_H and #define FILENAME_H at the top and #endif FILENAME_H at the bottom (replace FILENAME with the file name of course).  Check out other headers for examples 
# Author: Benjamin Meyer [ben + kdetesting at meyerhome dot net ]
##

for file in `find . -name \*.h | grep -v config.h | grep -v .ui.h | grep -v version.h | grep -v generated` ; do
	grep 'ifndef' $file >> /dev/null
	if [ $? = 1 ] ; then
		echo "Missing ifndef in: $file"
	fi
done

