#!/bin/sh
##
# Name: Post-increment operators on iterators
# Description: Prefer to use pre-increment over post-increment operators on iterators. It avoids creating an unnecessary temporary object.
# ToResolve: Change to ++iterator.  Note: use a const iterator and caching the end() will produce loops significatly faster.  For example:	const QStringList::const_iterator cend = list.constEnd(); for ( QStringList::const_iterator it = list.begin(); it != cend; ++it ) { }
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

# TODO add check for i--

for file in `find . -name '*.cpp' -o -name '*.cc'` ; do
	awk '{gsub(/[ ]/||/[\t]/, "", $0); } /(for[\ ]*\(.*\++[\ ]*\))/&&/begin/ { print NR":" $0; num++ } END { if (num > 0) exit 1 } ' $file
	if [ $? == 1 ] ; then
		echo $file;
		echo
	fi;
done
