#!/bin/sh
##
# Name: TRUE, FALSE
# Description: TRUE and FALSE aren't really valid C++ bool names.
# ToResolve: Change TRUE to true and FALSE to false.
# Author: Benjamin Meyer [ben at meyerhome dot net ]
##

for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
	echo $file | grep test >> /dev/null
	if [ $? -eq 0 ] ; then
		continue;
	fi

	grep generated $file >> /dev/null
	if [ $? -eq 0 ] ; then
		continue;
	fi


	awk '/TRUE/||/FALSE/ { print NR":" $0; found=1;} END { if ( found==1 ) exit 0; else exit 1; }' $file
	if [ $? = 0 ] ; then
		echo "Inproper C++ bool in: $file"
        echo
	fi
done

