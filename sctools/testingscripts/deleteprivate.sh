#!/bin/sh
##
# Name: Delete Private
# Description: When a private class is used (and created in the constructor) it needs to be deleted in the destructor.
# ToResolve: Delete private class in the destructor.  See <a href="http://developer.kde.org/documentation/library/kdeqt/kde3arch/devel-binarycompatibility.html">Using a d-Pointer (see last paragraph on the page)</a>. NOTE: If you fix any memory leaks in HEAD make sure it is backported to the current stable branch.
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

for file in `find . -name '*.cpp' -o -name '*.cc' | grep -v libkdenetwork/gpgmepp` ; do
	awk '{gsub(/[ ]/||/[\t]/, "", $0); } /^d=new.*Private/ { exit 1 } ' $file
	if [ $? -eq 1 ] ;then
		awk '{gsub(/[ ]/||/[\t]/, "", $0); } /deleted/ { exit 1 } ' $file
		if [ ! $? -eq 1 ] ;then
			echo "Warning the private variable \"d\" might never be deleted in: $file"
            echo
		fi
	fi
done

