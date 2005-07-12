#!/bin/sh
##
# Name: startsWith
# Description: Although techniqly 's.mid(0, 3) == "Foo"' is faster then 's.startsWith("Foo")' (by ~10 asm instructions) startsWith should be used to avoid bugs like: s.mid(0, 4) == 
#"Foo".
# ToResolve: Convert.
# Author: Benjamin Meyer [ben + kdetesting at meyerhome dot net ]
##

for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
	awk '/.mid\(0.*=.*".*"/ { print NR":" $0; found=1;} END { if ( found==1 ) exit 0; else exit 1; }' $file
	if [ $? = 0 ] ; then
		echo "Found in : $file"
        echo
	fi
done
