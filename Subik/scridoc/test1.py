#import scribus - I need all into locals()
from scribus import *
import types

def parseDocString(name, dstr):
	"""Makes HTML from plain text"""
	rows = dstr.split('\n')
	ret = '\t<dt>' + rows[0] + '<dt>\n\t<dd><p>'
	s = ""
	for i in range(len(rows)-1):
		if len(rows[i+1]) == 0 and (i + 1 < len(rows)-1):
			ret = ret + '</p><p>'
		else:
			if (i + 1 < len(rows)-1):
				ret = ret + rows[i+1] + ' '
	return ret.replace('<p></p>', '') + '</p></dd>\n'

const = []
proc = []
classes = []
excep = []

for name, var in locals().items():#globals().items():
	v = type(var)
	# constants
	if v == types.IntType or v == types.TupleType:
		const.append(name)
		continue
	# functions or procedures
	if v == types.FunctionType or v == types.MethodType or v == types.BuiltinFunctionType or v == types.BuiltinMethodType:
		proc.append((name, var.__doc__))
		continue
	# Classes (types)
	if v == types.TypeType:
		classes.append((name, var.__doc__))
	if v == types.ClassType:
		excep.append(name)
	print name, v


f = file('CONSTANTS.html', 'w')
for i in const:
	if i.isupper:
		f.write(i + '<br>\n')
f.close()

for i in proc:
	f = file(i[0]+'.html', 'w')
	f.write(parseDocString(i[0], i[1]))
	f.close()

for i in classes:
	f = file(i[0]+'.html', 'w')
	f.write(i[1])
	f.close()

f = file('EXCEPTIONS.html', 'w')
for i in excep:
	if i.isupper:
		f.write(i + '<br>\n')
f.close()
