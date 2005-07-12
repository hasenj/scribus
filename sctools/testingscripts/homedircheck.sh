#!/bin/sh
##
# Name: Unix home
# Description: When and only when refering to the users home directory QDir::homeDirPath is prefered to \"~\"
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
# ToResolve: Change \"~\" to QDir::homeDirPath().
##

#source generatereport testpaths

check() {
	if [ ! -d "${KDESOURCE}/${1}" ] ; then
		return;
	fi
	
	echo "Checking: $1";
	cd "${KDESOURCE}/${1}"
	for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
		grep "\".*~.*\"" $file | grep -v "http" | grep -v "kdDebug" | grep -v "URL" | grep -v "QDir::homeDirPath" | grep -v "debug" | grep -v "#"
		if [ $? -eq 0 ] ;then
			echo "Warning: <b>IF</b> refering to the home directory change: $file"
			echo ""
		fi
	done
}

for module in $KDEMODULES ; do
	check $module
done

