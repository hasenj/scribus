#!/bin/sh
##
# Name: QString::null == calls
# Description: Finds cases where QString foo == QString::null is used when foo.isNull() should be used because it is much faster.
# ToResolve: Change code to use string.isNull()
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
	awk '{gsub(/[ ]/||/[\t]/, "", $0); } /QString::null==/||/==QString::null/||/QString::null!=/||/!=QString::null/ { print $0; num++ } END { if (num > 0) exit 1 } ' $file
	if [ $? == 1 ] ; then
		echo $file;
		echo
	fi;
done

