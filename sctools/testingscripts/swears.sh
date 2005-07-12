#!/bin/sh
##
# Name: Swears 
# Description: Finds swear words in code.
# ToResolve: The author may have been annoyed at some api/tutorial/doc that wasn't documented well.  Evaluate if the code or a doc that needs to be improved.  If you are the author 
#it is up to you to decide if you want this comment or not in *your* code.  If you arn't the author don't touch the comment, people tend to get all pissy when you change their 
#fucking swear words.  Unless it is in a kdDebug() which goes out to the user and it should be removed. 
# Author: Benjamin Meyer [ben + kdetest at meyerhome dot net]
##

for file in `find . -name '*.cpp' -o -name '*.cc' -o -name '*.c' -o -name '*.h' -o -name '*.cxx' -o -name '*.py' -o -name '*.sh' -o -name '*.pl'` ; do
	awk '{tolower($0)} /[" ]fuck[" ]|[" ]cunt[" ]|[" ]crap[" ]|[" ]dick[" ]|[" ]shitty[" ]|[" ]shit[" ]|[" ]cock[" ]|[" ]wank[" ]|[" ]piss[" ]/ {print $0; exit 1}' $file
	
	#grep --word-regexp -e '/fuck|cunt|crap|dick|shit|cock|wank|piss/' $file
	
	if [ $? = 1 ] ; then
		echo "Possible warning in: $file"
        echo
	fi
done

