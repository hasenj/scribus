#!/bin/sh
##
# Name: Empty char* comparison
# Description: Finds usage where a QString is compared to "" where using .isEmpty() should be used because it is much faster.
# ToResolve: Change code to use string.isEmpty()  In the event that it is a std::string change to empty()
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
	awk '{gsub(/[\t]/, " ", $0); } /==[ ]*""/||/""[ ]*==/||/!=[ ]*""/||/""[ ]*!=/ { print NR":" $0; num++ } END { if (num > 0) exit 1 } ' $file
	if [ $? == 1 ] ; then
		echo $file;
		echo
	fi;
done

