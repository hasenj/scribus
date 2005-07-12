#!/bin/sh
##
# Name: No if body
# Description: Finds if and while statements that have no body or the body is never called because there is a \";\" 
# ToResolve: Either give an empty body {} or fix the bug.
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

for file in `find $1 -name '*.cpp' -o -name '*.cc'` ; do
	egrep -n '\bif\([^)]*\);' $file
	if [ $? == 0 ] ; then
		echo "\";\" at end of line in: $file"
		echo
	fi
	# for is hard to detect, lots of edge cases
	#egrep -n '\bfor\([^)]*\);' $file | egrep '\);$'
	#egrep   '\bfor\([^)]*\);^' $file
	
	error=`egrep -n '\bwhile\([^)]*\);' $file`
	if [ $? == 0 ] ; then
		grep "do"  $file >> /dev/null
		if [ $? == 1 ] ; then
			echo $error
			echo "\";\" at end of line in while: $file"
			echo
		fi
	fi
done

