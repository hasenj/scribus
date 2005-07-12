#!/bin/sh
##
# Name: .end() call in for loop 
# Description: When iteratoring through a list the value of end() should be cached to avoid the unnecessary creation of the temporary variable. See: <a 
# href="http://developer.kde.org/documentation/other/mistakes.html">Iterators</a>
# ToResolve: Create temporary variable (preferably const) outside of for loop to compare against.
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
	awk '{gsub(/[ ]/||/[\t]/, "", $0); } /for[\ ]*\(.*\.end.*\)/ { print $0; num++ } END { if (num > 0) exit 1 } ' $file
	if [ $? == 1 ] ; then
		echo $file;
		echo
	fi;
done

