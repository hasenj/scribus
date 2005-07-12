#!/bin/sh
##
# Name: Returning QPtrList
# Description: QPtrList's are not implicitly shared so returning them will copy the full QPtrList by iterating over all of its elements and inserting them in the newly created 
#QPtrList which is very slow.
# ToResolve: change to use QValueList.
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##
if [ ! -z `echo $PWD | grep kdelibs` ] ; then
	echo "Skipping kdelibs till HEAD is for 4.0";
	exit -1;
fi

for file in `find $1 -name \*.h` ; do
	awk '{gsub(/([\t])|(virtual)/, " ", $0);} /^[ ]*QPtrList[ ]*\(/ {print $0}' $file
	if [ $? == 1 ] ; then
		echo "$file"
        echo
	fi
done

