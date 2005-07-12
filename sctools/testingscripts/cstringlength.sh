#!/bin/sh
##
# Name: Q<b>C</b>String length cache 
# Description: QCString::length() calls strlen on each invocation so it should never be called in a loop. <a href="http://developer.kde.org/documentation/other/mistakes.html">See here for more details</a>
# ToResolve: Move length calculation outside of loop.  NOTE: this script isn't the most advanced and if a QString and QCString vars are named the same in the same file it will confuse them.  <b>QString</b>.length() in a loop is ok.  Watch out for cases were the string is modified within the loop. 
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
	found=false
	for var in	`grep 'QCString ' $file | sed -e s/.*QC//g | sed -e s/\&//g | awk '{print $2}'` ; do
		var=`echo $var | sed -e s/\=.*//g | sed -e s/,.*//g | sed -e s/\(.*//g | sed -e s/\;.*//g | sed -e s/\).*//g`
		if [ -z "${var}" ] ; then
			continue;
		fi
		var=`echo $var | sed -e s/\\\]/\\\\\\\]/g | sed -e s/\\\[/\\\\\\\[/g`
		error=`grep -n "${var}.length\(\)" $file | grep "for[\ ]*("`
	
		if [ $? = 0 ] ; then
			grep -n "${var}.length().*;.*;.*)" $file >> /dev/null
			if [ $? = 0 ] ; then
				echo "ignore if length is not in the middle?: $error" >> /dev/null
			else
				echo "$error" | sed -e s/\</"\&"lt\;/g | sed -e s/\>/"\&"gt\;/g
				found=true
			fi
		fi

	done
	if [ $found == true ] ; then
		echo "Possible warning in: $file"
        echo
	fi
done

