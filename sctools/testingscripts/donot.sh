#!/bin/sh
##
# Name: don't 
# Description: Finds abbreviation's in strings in the code.
# ToResolve: Change "don't" to "do not" etc
# Author: Benjamin Meyer [ben + kdetest at meyerhome dot net]
##

for file in `find . -name '*.cpp' -o -name '*.cc' -o -name '*.c' -o -name '*.h' -o -name '*.cxx' -o -name '*.py' -o -name '*.docbook'` ; do
	# C++ comment
	grep "\/\/" $file >> /dev/null
	if [ $? = 1 ] ; then
	
	# C comment
	grep "\/\*" $file >> /dev/null
	if [ $? = 1 ] ; then

	# Shell comment
	grep "#" $file >> /dev/null
	if [ $? = 1 ] ; then

  # Docbook comment
	grep "<!--" $file >> /dev/null
	if [ $? = 1 ] ; then

	grep -e "\(don't\|havn't\|won't\|we'll\|doesn't\|can't\)" $file
	#grep -e "\(don't\|doesn't\)" $file
	if [ $? = 0 ] ; then
		echo "Possible warning in: $file"
        echo
	fi
	
	fi
	fi
	fi
	fi
done

