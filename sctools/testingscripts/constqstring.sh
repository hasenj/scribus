#!/bin/sh

##
# Name: const QString &
# Description: Finds functions that don't pass a Qt item using a const reference.  This is slower and makes bigger binaries.
# ToResolve: Change to use "const class &" (Note: Don't change libs until 4.0!  It breaks binary compatiblity!).  Note that in some cases you can't just change the function header, but have to massage the code a little.  If you change a slot don't forget to change the connect() as it wont break compile, but it will break at runtime.
# Author: Benjamin Meyer <ben + kdetest at meyerhome dot net>
##

if [ ! -z `echo $PWD | grep kdelibs` ] ; then
	echo "Skipping kdelibs till HEAD is for 4.0";
	exit -1;
fi

a="(.*QString .*)"
b="QString[ ]*\*"
c="QString[ ]*&"
d="QString::"
e="QString"
for item in QCString QStringList QColor QImage QPixmap QByteArray QPoint QSize QBitmap QTime QDate QPen QIconSet QPalette; do
	a="$a\|(.*$item .*)"
	b="$b\|$item[ ]*\*"
	c="$c\|$item[ ]*&"
	d="$d\|$item::" 
	e="$e\|$item"
done
export e

for file in `find $1 -name \*.h` ; do
	# Skip DCOP stuff sense it can't be const?
	grep DCOP $file >> /dev/null
	if [ $? -eq 0 ] ; then
		continue;
	fi
	
	# Will miss for void processDirectory(QCString *received, const QString &host, QString path);
		grep -n "$a" $file | grep -v "$b" | grep -v "$c" | grep -v "$d" | grep -v "const" | grep -v "Q_PROPERTY" | sed -e s/virtual//g | sed -e s/static//g | awk '{
		gsub(/[\t]/, "", $0);
		ln=$0
		gsub(/[ ]/||/[\t]/, "", ln);
		substr(ln,1,7);
		if(ln != $e && substr(ln,0,1) != "*") { 
			print $0
			found++;
		}
	}
	END {
		if(found > 0) {
			exit 2;
		}
	}'
	if [ $? == 2 ] ; then
		echo "Missing const in : $file"
		echo
	fi
done

