# -*- coding: Utf8 -*-
import sys
import inspect
import types

sys.setappdefaultencoding('utf8')

#import scribus - I need all into locals()
from scribus import *

PyCObjectType = type(qApp)

def checkObject(name):
	if name in ['parseDocString', 'docHeader', 'docFooter', 'PyCObjectType', 'checkObject']:
		return 1
	return 0

def parseDocString(name, dstr = " ", optval=None):
	"""Makes HTML from plain text"""
	ret = '\t<dt><b>'+ name + '</b></dt>\n\t<dd><pre><p>'
	ret = ret + str(dstr).replace('\n\n', '</p><p>')#rows[0]
	ret = ret + '</p>' #</p>\n\t<p>'
	if optval:
		ret = ret + '<p>Value: ' + str(optval) + '</p>'
	return ret.replace('<p></p>', '') + '</pre></dd>\n\n'


def docHeader(fname):
	return fname.write("<qt><dl>\n\n")


def docFooter(fname):
	return fname.write("\n\n</dl></qt>")


const = []
proc = []
classes = []
excep = []
strs = []
cobj = []

print '\n\n'

for name, var in locals().items():#globals().items():
	v = type(var)
	if checkObject(name):
		continue
	# constants
	if v == types.IntType or v == types.TupleType:
		const.append((name, var))
		continue
	# functions or procedures
	if v == types.FunctionType or v == types.MethodType or v == types.BuiltinFunctionType or v == types.BuiltinMethodType:
		proc.append((name, inspect.getdoc(var) or inspect.getcomments(var)))#var.__doc__))
		continue
	# Classes (types)
	if v == types.TypeType and v != PyCObjectType:
		classes.append((name, inspect.getdoc(var) or inspect.getcomments(var)))
		continue
	if v == types.ClassType:
		excep.append((name, inspect.getdoc(var) or inspect.getcomments(var)))
		continue
	if v == types.StringType:
		strs.append((name, inspect.getdoc(var) or inspect.getcomments(var), var))
		continue
	if v == PyCObjectType:
		cobj.append((name, inspect.getdoc(var) or inspect.getcomments(var), var))
		continue
	print 'UNDOCUMENTED: '+ name+ ' '+ str(v)


import glob
origdocs = glob.glob('/home/subzero/devel/SCRIBUS13/share/scribus/doc/en/scripterapi-*.html')
docmap = {}
for i in origdocs:
	f = file(i, 'r')
	docmap[i] = (f.read(), '\n')
	f.close()

f = file('scripterapi-constants.html', 'w')
docHeader(f)
const.sort()
for i in const:
	f.write(parseDocString(i[0], 'Predefined constant', i[1]))
docFooter(f)
f.close()

import string
proc.sort()
unresolved = ''
isresolved = 0
for i in proc:
	isresolved = 0
	for j in docmap:
		if string.find(docmap[j][0], i[0]) > 0:
			docmap[j] = (docmap[j][0], docmap[j][1] + parseDocString(i[0], i[1]))
			isresolved = 1
	if isresolved == 0:
		unresolved = unresolved + parseDocString(i[0], i[1])

if len(unresolved) > 0:
	f = file('UNKNOWN.html', 'w')
	f.write(unresolved)
	f.close()

import os.path
for i in docmap:
	f = file(os.path.basename(i), 'w')
	docHeader(f)
	f.write(docmap[i][1])
	docFooter(f)
	f.close()

import scribus
classes.sort()
for i in classes:
	f = file('scripterapi-'+i[0]+'.html', 'w')
	docHeader(f)
	f.write(parseDocString(i[0], i[1]))
	try:
		d = dir(getattr(scribus, i[0]))
	except:
		d = []
	if len(d) == 0:
		continue
	d.sort()
	for j in d:
		if j[:2] != '__':
			obj = getattr(getattr(scribus, i[0]), j)
			f.write(parseDocString(j, inspect.getdoc(obj) or inspect.getcomments(obj)))
	docFooter(f)
	f.close()

f = file('scripterapi-exceptions.html', 'w')
docHeader(f)
excep.sort()
for i in excep:
	f.write(parseDocString(i[0], i[1]))
docFooter(f)
f.close()

f = file('scripterapi-strings.html', 'w')
docHeader(f)
strs.sort()
for i in strs:
	f.write(parseDocString(i[0], i[1], i[2]))
docFooter(f)
f.close()

f = file('scripterapi-cobjects.html', 'w')
docHeader(f)
cobj.sort()
for i in cobj:
	f.write(parseDocString(i[0], i[1]))
docFooter(f)
f.close()

"""
f = file('SCRIBUS.html', 'w')
docHeader(f)
f.write(parseDocString('Scribus Python API', inspect.getdoc(scribus) or inspect.getcomments(scribus)))
docFooter(f)
f.close()
"""
