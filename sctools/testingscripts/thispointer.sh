#!/bin/sh
##
# Name: Finds this-> constructs
# Description: Finds classes that use this-> that aren't templates.
# ToResolve: When it isn't a (see <a href="http://www.parashift.com/c++-faq-lite/containers-and-templates.html#faq-34.17">template-derived-class</a>), simply remove "this->"
# Author: Benjamin Meyer < ben + kdetest at meyerhome dot net >
##

for file in `find . -name \*.cpp | grep -v kresources/groupwise/soap` ; do
	awk '/\ this->/ {
		# Store line
		ln=$0;
		# Strip whitespace
		gsub(/[ ]|[\t]*|;/, "", $0);
		# Strip this->
		$0=substr($0,7);
		split($0,vars,"=");
		if(vars[1] != vars[2]) {
			print NR":" ln;
			exit 1;
		}
	}' $file

	if [ $? = 1 ] ; then
 		echo "Possible warning in: $file"
        echo
	fi
done
