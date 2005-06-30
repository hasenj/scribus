#!/usr/bin/python
#arch-tag: fa5eee77-3ab3-4eb2-8bf1-84c28c8b48af

"""This script will refresh the translation string lists for .ts and .po
files in the Scribus cvs directory and update the Scribus.pot and
Scribus.pro files for new translations before a CVS update.

Copyright (C) 2004 Oleksandr Moskalenko <malex@tagancha.org>
License: GPLv2 (http://www.gnu.org/licenses/gpl.html)
Version: 0.1
Starting Date:  Mon, 17 May 2004 23:05:04 -0500
Last Change: Tue, 18 May 2004 14:28:07 -0500
ChangeLog:
    Version 0.1 - Tue, 18 May 2004 14:28:07 -0500
        * Used trstats.py script as a basis. First iteration.
"""

import os,sys
from optparse import OptionParser
sourcefiles = []

#Set the paths to the necessary binaries
confrmbin = '/bin/rm'
confcvsbin = '/usr/bin/cvs'
confqmakebin = '/usr/qt/3/bin/qmake'
#confqmakebin = '/usr/bin/qmake'
conflupdatebin = '/usr/qt/3/bin/lupdate'
#conflupdatebin = '/usr/bin/lupdate'
confxgettextbin = '/usr/bin/xgettext'
confmsgmergebin = '/usr/bin/msgmerge'

license = """\nCopyright (C) 2004  Oleksandr Moskalenko <malex@tagancha.org>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
or visit http://www.gnu.org/licenses/gpl.html.\n"""

def getopts():
    """This procedure parses options and arguments passed to the program and
stores them in a dictionary (opts) and a list (args)"""
    usage = "%prog [options]"
    op = OptionParser(usage=usage, version='%prog 0.1')
    op.add_option('-l', '--license', action='store_true', dest='lic', default=False, help='Show the license info.')
    op.add_option('-c', '--cvsdir', dest='cvsdir', help='main cvs "Scribus" directory in to current directory.')
    opts,args = op.parse_args(sys.argv[1:])
    if opts.cvsdir != None:
        cvsdir = opts.cvsdir
    else:
        cvsdir = "."
    lic = opts.lic
    return cvsdir,lic

def updatets():
    qmakebin = confqmakebin
    qmake = os.spawnv('P_WAIT',qmakebin,('qmake','-project'))
    if qmake == 0:
        print 'Scribus.pro updated\n'
    else:
        print 'Failed to update Scribus.pro\n'
        sys.exit(1)
    lupdate = os.spawnv('P_WAIT',conflupdatebin,('lupdate -noobsolete','Scribus.pro'))
    if lupdate == 0:
        print 'Updated .ts files\n'
    else:
        print 'Failed to update .ts files\n'
        sys.exit(1)

def getsfiles(args,dirname,names):
    global sourcefiles
    sfnames = ['.cpp','.c','.h']
    results = []
    for i in names:
        if os.path.splitext(i)[1] in sfnames:
            results.append(os.path.join(dirname,i))
    sourcefiles.extend(results)

def updatepo():
    global sourcefiles
    xgettextbin = confxgettextbin
    msgmergebin = confmsgmergebin
    polist = []
    os.path.walk('scribus',getsfiles,'')
    sflname = '/tmp/posourcefiles.txt'
    try:
        poflist = open(sflname,'w')
    except OSError:
        print "Error. Could not create a temporary file in /tmp. Please check that /tmp is writable by you" 
    for fname in sourcefiles:
        line = fname+'\n'
        poflist.write(line)
    poflist.close()
    poup = os.spawnv('P_WAIT',xgettextbin,('xgettext','-f',sflname,'-o','Scribus.pot','-ktr','--force-po','--no-location'))
    if poup == 0:
        print "Generated an updated Scribus.pot file.\n"
    else:
        print "\nError. Could not generate updated Scribus.pot file.\n"
        sys.exit(1)
    for filename in os.listdir('scribus/po'):
        if os.path.splitext(filename)[1] == '.po':
            ftomerge = os.path.join('scribus','po',filename)
            msm = os.spawnv('P_WAIT',msgmergebin,('msgmerge','-U','--silent','--backup=none',ftomerge,'Scribus.pot'))
            if msm == 0:
                pass
            else:
                print "Error! Failed to merge %s with Scribus.pot\n" % (filename)
    print "Merged .po files with Scribus.pot\n"

def main():
    if len(sys.argv) == 1:
        print "Run ./trstats.py --help | -h for additional usage directions.\n"
    cvsdir,licaction = getopts()
    if licaction == True:
        print license
        sys.exit()
    if cvsdir != None:
        try:
            os.chdir(cvsdir)
        except OSError:
            print 'Something wicked happened. Theres is no %s directory' % (cvsdir)
            sys.exit(1)
    curdirname = os.listdir('.')
    if os.path.split(os.path.abspath(os.path.curdir))[-1] != 'Scribus':
        try:
            os.chdir('Scribus')
        except OSError:
            print 'Error. I am no in the "Scribus" dir, nor am I in its parent dir.'
            sys.exit(1)
    else:
        print 'I am in the "Scribus" directory. Staring the updates...'
    updatepo()
    updatets()
    sys.exit("Success. All translation-related files have been updated.")

if __name__=='__main__':
    main()
