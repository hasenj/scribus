#!/usr/bin/env python
# -*- coding: Utf8 -*-
"""Generate Python documentation in clean and nice HTML for Scribus.
Based on the PyDoc package.
"""
__author__ = "Petr Vanek <petr@yarpen.cz>"
__date__ = "2004/12/27"
__version__ = "$Id$"
__credits__ = "Ka-Ping Yee <ping@lfw.org> for PyDoc"

import sys, imp, os, re, types, inspect, __builtin__
from repr import Repr
from string import expandtabs, find, join, lower, split, strip, rfind, rstrip

# --------------------------------------------------------- common routines
def pathdirs():
	"""Convert sys.path into a list of absolute, existing, unique paths."""
	dirs = []
	normdirs = []
	for dir in sys.path:
		dir = os.path.abspath(dir or '.')
		normdir = os.path.normcase(dir)
		if normdir not in normdirs and os.path.isdir(dir):
			dirs.append(dir)
			normdirs.append(normdir)
	return dirs

def getdoc(object):
	"""Get the doc string or comments for an object."""
	result = inspect.getdoc(object) or inspect.getcomments(object)
	return result and re.sub('^ *\n', '', rstrip(result)) or ''

def splitdoc(doc):
	"""Split a doc string into a synopsis line (if any) and the rest."""
	lines = split(strip(doc), '\n')
	if len(lines) == 1:
		return lines[0], ''
	elif len(lines) >= 2 and not rstrip(lines[1]):
		return lines[0], join(lines[2:], '\n')
	return '', join(lines, '\n')

def classname(object, modname):
	"""Get a class name and qualify it with a module name if necessary."""
	name = object.__name__
	if object.__module__ != modname:
		name = object.__module__ + '.' + name
	return name

def isdata(object):
	"""Check if an object is of a type that probably means it's data."""
	return not (inspect.ismodule(object) or inspect.isclass(object) or
				inspect.isroutine(object) or inspect.isframe(object) or
				inspect.istraceback(object) or inspect.iscode(object))

def replace(text, *pairs):
	"""Do a series of global replacements on a string."""
	while pairs:
		text = join(split(text, pairs[0]), pairs[1])
		pairs = pairs[2:]
	return text

def cram(text, maxlen):
	"""Omit part of a string if needed to make it fit in a maximum length."""
	if len(text) > maxlen:
		pre = max(0, (maxlen-3)//2)
		post = max(0, maxlen-3-pre)
		return text[:pre] + '...' + text[len(text)-post:]
	return text

def stripid(text):
	"""Remove the hexadecimal id from a Python object representation."""
	# The behaviour of %p is implementation-dependent; we check two cases.
	for pattern in [' at 0x[0-9a-f]{6,}(>+)$', ' at [0-9A-F]{8,}(>+)$']:
		if re.search(pattern, repr(Exception)):
			return re.sub(pattern, '\\1', text)
	return text

def _is_some_method(object):
	return inspect.ismethod(object) or inspect.ismethoddescriptor(object)

def allmethods(cl):
	methods = {}
	for key, value in inspect.getmembers(cl, _is_some_method):
		methods[key] = 1
	for base in cl.__bases__:
		methods.update(allmethods(base)) # all your base are belong to us
	for key in methods.keys():
		methods[key] = getattr(cl, key)
	return methods

def _split_list(s, predicate):
	"""Split sequence s via predicate, and return pair ([true], [false]).

	The return value is a 2-tuple of lists,
		([x for x in s if predicate(x)],
		 [x for x in s if not predicate(x)])
	"""
	yes = []
	no = []
	for x in s:
		if predicate(x):
			yes.append(x)
		else:
			no.append(x)
	return yes, no

def visiblename(name):
	"""Decide whether to show documentation on a variable."""
	# Certain special names are redundant.
	if name in ['__builtins__', '__doc__', '__file__', '__path__',
				'__module__', '__name__']: return 0
	# Private names are hidden, but special names are displayed.
	if name.startswith('__') and name.endswith('__'): return 1
	return not name.startswith('_')

# ----------------------------------------------------- module manipulation

def ispackage(path):
	"""Guess whether a path refers to a package directory."""
	if os.path.isdir(path):
		for ext in ['.py', '.pyc', '.pyo']:
			if os.path.isfile(os.path.join(path, '__init__' + ext)):
				return True
	return False

def synopsis(filename, cache={}):
	"""Get the one-line summary out of a module file."""
	mtime = os.stat(filename).st_mtime
	lastupdate, result = cache.get(filename, (0, None))
	if lastupdate < mtime:
		info = inspect.getmoduleinfo(filename)
		file = open(filename)
		if info and 'b' in info[2]: # binary modules have to be imported
			try: module = imp.load_module('__temp__', file, filename, info[1:])
			except: return None
			result = split(module.__doc__ or '', '\n')[0]
			del sys.modules['__temp__']
		else: # text modules can be directly examined
			line = file.readline()
			while line[:1] == '#' or not strip(line):
				line = file.readline()
				if not line: break
			line = strip(line)
			if line[:4] == 'r"""': line = line[1:]
			if line[:3] == '"""':
				line = line[3:]
				if line[-1:] == '\\': line = line[:-1]
				while not strip(line):
					line = file.readline()
					if not line: break
				result = strip(split(line, '"""')[0])
			else: result = None
		file.close()
		cache[filename] = (mtime, result)
	return result

class ErrorDuringImport(Exception):
	"""Errors that occurred while trying to import something to document it."""
	def __init__(self, filename, (exc, value, tb)):
		self.filename = filename
		self.exc = exc
		self.value = value
		self.tb = tb

	def __str__(self):
		exc = self.exc
		if type(exc) is types.ClassType:
			exc = exc.__name__
		return 'problem in %s - %s: %s' % (self.filename, exc, self.value)

def importfile(path):
	"""Import a Python source file or compiled file given its path."""
	magic = imp.get_magic()
	file = open(path, 'r')
	if file.read(len(magic)) == magic:
		kind = imp.PY_COMPILED
	else:
		kind = imp.PY_SOURCE
	file.close()
	filename = os.path.basename(path)
	name, ext = os.path.splitext(filename)
	file = open(path, 'r')
	try:
		module = imp.load_module(name, file, path, (ext, 'r', kind))
	except:
		raise ErrorDuringImport(path, sys.exc_info())
	file.close()
	return module

def safeimport(path, forceload=0, cache={}):
	"""Import a module; handle errors; return None if the module isn't found.

	If the module *is* found but an exception occurs, it's wrapped in an
	ErrorDuringImport exception and reraised.  Unlike __import__, if a
	package path is specified, the module at the end of the path is returned,
	not the package at the beginning.  If the optional 'forceload' argument
	is 1, we reload the module from disk (unless it's a dynamic extension)."""
	if forceload and path in sys.modules:
		# This is the only way to be sure.  Checking the mtime of the file
		# isn't good enough (e.g. what if the module contains a class that
		# inherits from another module that has changed?).
		if path not in sys.builtin_module_names:
			# Python never loads a dynamic extension a second time from the
			# same path, even if the file is changed or missing.  Deleting
			# the entry in sys.modules doesn't help for dynamic extensions,
			# so we're not even going to try to keep them up to date.
			info = inspect.getmoduleinfo(sys.modules[path].__file__)
			if info[3] != imp.C_EXTENSION:
				cache[path] = sys.modules[path] # prevent module from clearing
				del sys.modules[path]
	try:
		module = __import__(path)
	except:
		# Did the error occur before or after the module was found?
		(exc, value, tb) = info = sys.exc_info()
		if path in sys.modules:
			# An error occured while executing the imported module.
			raise ErrorDuringImport(sys.modules[path].__file__, info)
		elif exc is SyntaxError:
			# A SyntaxError occurred before we could execute the module.
			raise ErrorDuringImport(value.filename, info)
		elif exc is ImportError and \
			 split(lower(str(value)))[:2] == ['no', 'module']:
			# The module was not found.
			return None
		else:
			# Some other error occurred during the importing process.
			raise ErrorDuringImport(path, sys.exc_info())
	for part in split(path, '.')[1:]:
		try: module = getattr(module, part)
		except AttributeError: return None
	return module

# ---------------------------------------------------- formatter base class

class Doc:
	def document(self, object, name=None, *args):
		"""Generate documentation for an object."""
		args = (object, name) + args
		# 'try' clause is to attempt to handle the possibility that inspect
		# identifies something in a way that pydoc itself has issues handling;
		# think 'super' and how it is a descriptor (which raises the exception
		# by lacking a __name__ attribute) and an instance.
		try:
			if inspect.ismodule(object): return self.docmodule(*args)
			if inspect.isclass(object): return self.docclass(*args)
			if inspect.isroutine(object): return self.docroutine(*args)
		except AttributeError:
			pass
		return self.docother(*args)

	def fail(self, object, name=None, *args):
		"""Raise an exception for unimplemented types."""
		message = "don't know how to document object%s of type %s" % (
			name and ' ' + repr(name), type(object).__name__)
		raise TypeError, message

	docmodule = docclass = docroutine = docother = fail

# -------------------------------------------- HTML documentation generator

class HTMLRepr(Repr):
	"""Class for safely making an HTML representation of a Python object."""
	def __init__(self):
		Repr.__init__(self)
		self.maxlist = self.maxtuple = 20
		self.maxdict = 10
		self.maxstring = self.maxother = 100

	def escape(self, text):
		return replace(text, '&', '&amp;', '<', '&lt;', '>', '&gt;')

	def repr(self, object):
		return Repr.repr(self, object)

	def repr1(self, x, level):
		if hasattr(type(x), '__name__'):
			methodname = 'repr_' + join(split(type(x).__name__), '_')
			if hasattr(self, methodname):
				return getattr(self, methodname)(x, level)
		return self.escape(cram(stripid(repr(x)), self.maxother))

	def repr_string(self, x, level):
		test = cram(x, self.maxstring)
		testrepr = repr(test)
		if '\\' in test and '\\' not in replace(testrepr, r'\\', ''):
			# Backslashes are only literal in the string and are never
			# needed to make any special characters, so show a raw string.
			return 'r' + testrepr[0] + self.escape(test) + testrepr[0]
		return re.sub(r'((\\[\\abfnrtv\'"]|\\[0-9]..|\\x..|\\u....)+)',
					  r'<font color="#c040c0">\1</font>',
					  self.escape(testrepr))

	repr_str = repr_string

	def repr_instance(self, x, level):
		try:
			return self.escape(cram(stripid(repr(x)), self.maxstring))
		except:
			return self.escape('<%s instance>' % x.__class__.__name__)

	repr_unicode = repr_string

class HTMLDoc(Doc):
	"""Formatter class for HTML documentation."""

	# ------------------------------------------- HTML formatting utilities

	_repr_instance = HTMLRepr()
	repr = _repr_instance.repr
	escape = _repr_instance.escape

	def page(self, title, contents):
		"""Format an HTML page."""
		return '''
<qt>
%s
</qt>''' % (contents)

	def heading(self, title, fgcol, bgcol, extras=''):
		"""Format a page heading."""
		return '''
<h2>%s</h2>
<p>debug_Extras: %s</p>
	''' % (title, extras or '&nbsp;')

	def section(self, title, fgcol, bgcol, contents, width=6,
				prelude='', marginalia=None, gap=' '):
		"""Format a section with a heading."""
		if marginalia is None:
#marginalia = '<tt>' + '&nbsp;' * width + '</tt>'
			pass
		result = '''
<h4>debug_Section: "%s"</h4>
''' % (title)
		if prelude:
			result = result + '''
<p>debug_Prelude: %s</p>
''' % (prelude)
		return result + '''
<p>debug_Contents: %s</p>
''' % contents

	def bigsection(self, title, *args):
		"""Format a section with a big heading."""
		title = '''debug_Title<h7>%s</h7>''' % title
		return self.section(title, *args)

	def preformat(self, text):
		"""Format literal preformatted text."""
		text = self.escape(expandtabs(text))
		return replace(text, '\n\n', '\n \n', '\n\n', '\n \n')
						#'\n', '<br>\n')

	def multicolumn(self, list, format, cols=4):
		"""Format a list of items into a multi-column list."""
		"""result = ''
		rows = (len(list)+cols-1)/cols
		for col in range(cols):
#result = result + '<td width="%d%%" valign=top>' % (100/cols)
			for i in range(rows*col, rows*col+rows):
				if i < len(list):
					result = result + format(list[i]) + ' '
			result = result + '</td>'
		return '<p>%s</p>' % result"""
		pass

	def grey(self, text): return '<p>debug_Grey: %s</p>' % text

	def namelink(self, name, *dicts):
		"""Make a link for an identifier, given name-to-URL mappings."""
		for dict in dicts:
			if name in dict:
				return '<a href="%s">%s</a>' % (dict[name], name)
		return name

	def classlink(self, object, modname):
		"""Make a link for a class."""
		name, module = object.__name__, sys.modules.get(object.__module__)
		if hasattr(module, name) and getattr(module, name) is object:
			return '<a href="%s.html#%s">%s</a>' % (
				module.__name__, name, classname(object, modname))
		return classname(object, modname)

	def modulelink(self, object):
		"""Make a link for a module."""
		return '<a href="%s.html">%s</a>' % (object.__name__, object.__name__)

	def modpkglink(self, (name, path, ispackage, shadowed)):
		"""Make a link for a module or package to display in an index."""
		if shadowed:
			return self.grey(name)
		if path:
			url = '%s.%s.html' % (path, name)
		else:
			url = '%s.html' % name
		if ispackage:
			text = '<h7>debug_IsPackage: %s (package)</h7>' % name
		else:
			text = name
		return '<a href="%s">%s</a>' % (url, text)

	def markup(self, text, escape=None, funcs={}, classes={}, methods={}):
		"""Mark up some plain text, given a context of symbols to look for.
		Each context dictionary maps object names to anchor names."""
		escape = escape or self.escape
		results = []
		here = 0
		pattern = re.compile(r'\b((http|ftp)://\S+[\w/]|'
								r'RFC[- ]?(\d+)|'
								r'PEP[- ]?(\d+)|'
								r'(self\.)?(\w+))')
		while True:
			match = pattern.search(text, here)
			if not match: break
			start, end = match.span()
			results.append(escape(text[here:start]))

			all, scheme, rfc, pep, selfdot, name = match.groups()
			if scheme:
				url = escape(all).replace('"', '&quot;')
				results.append('<a href="%s">%s</a>' % (url, url))
			elif rfc:
				url = 'http://www.rfc-editor.org/rfc/rfc%d.txt' % int(rfc)
				results.append('<a href="%s">%s</a>' % (url, escape(all)))
			elif pep:
				url = 'http://www.python.org/peps/pep-%04d.html' % int(pep)
				results.append('<a href="%s">%s</a>' % (url, escape(all)))
			elif text[end:end+1] == '(':
				results.append(self.namelink(name, methods, funcs, classes))
			elif selfdot:
				results.append('self.<strong>%s</strong>' % name)
			else:
				results.append(self.namelink(name, classes))
			here = end
		results.append(escape(text[here:]))
		return join(results, '')

	# ---------------------------------------------- type-specific routines

	def formattree(self, tree, modname, parent=None):
		"""Produce HTML for a class tree as given by inspect.getclasstree()."""
		result = ''
		for entry in tree:
			if type(entry) is type(()):
				c, bases = entry
				result = result + '<dt><font face="helvetica, arial">'
				result = result + self.classlink(c, modname)
				if bases and bases != (parent,):
					parents = []
					for base in bases:
						parents.append(self.classlink(base, modname))
					result = result + '(' + join(parents, ', ') + ')'
				result = result + '\n</font></dt>'
			elif type(entry) is type([]):
				result = result + '<dd>\n%s</dd>\n' % self.formattree(
					entry, modname, c)
		return '<dl>\n%s</dl>\n' % result

	def docmodule(self, object, name=None, mod=None, *ignored):
		"""Produce HTML documentation for a module object."""
		name = object.__name__ # ignore the passed-in name
		parts = split(name, '.')
		links = []
		for i in range(len(parts)-1):
			links.append(
				'<a href="%s.html">%s</a>' %
				(join(parts[:i+1], '.'), parts[i]))
		linkedname = join(links + parts[-1:], '.')
		head = '<h5>debug_Linkedname:%s</h5>' % linkedname
		try:
			path = inspect.getabsfile(object)
			url = path
			if sys.platform == 'win32':
				import nturl2path
				url = nturl2path.pathname2url(path)
			filelink = '<a href="file:%s">%s</a>' % (url, path)
		except TypeError:
			filelink = '(built-in)'
		info = []
		if hasattr(object, '__version__'):
			version = str(object.__version__)
			if version[:11] == '$' + 'Revision: ' and version[-1:] == '$':
				version = strip(version[11:-1])
			info.append('version %s' % self.escape(version))
		if hasattr(object, '__date__'):
			info.append(self.escape(str(object.__date__)))
		if info:
			head = head + ' (%s)' % join(info, ', ')
		result = self.heading(
			head, '#ffffff', '#7799ee', '<a href=".">index</a><br>' + filelink)

		modules = inspect.getmembers(object, inspect.ismodule)

		classes, cdict = [], {}
		for key, value in inspect.getmembers(object, inspect.isclass):
			if (inspect.getmodule(value) or object) is object:
				if visiblename(key):
					classes.append((key, value))
					cdict[key] = cdict[value] = '#' + key
		for key, value in classes:
			for base in value.__bases__:
				key, modname = base.__name__, base.__module__
				module = sys.modules.get(modname)
				if modname != name and module and hasattr(module, key):
					if getattr(module, key) is base:
						if not key in cdict:
							cdict[key] = cdict[base] = modname + '.html#' + key
		funcs, fdict = [], {}
		for key, value in inspect.getmembers(object, inspect.isroutine):
			if inspect.isbuiltin(value) or inspect.getmodule(value) is object:
				if visiblename(key):
					funcs.append((key, value))
					fdict[key] = '#-' + key
					if inspect.isfunction(value): fdict[value] = fdict[key]
		data = []
		for key, value in inspect.getmembers(object, isdata):
			if visiblename(key):
				data.append((key, value))

		doc = self.markup(getdoc(object), self.preformat, fdict, cdict)
		doc = doc and '<tt>%s</tt>' % doc
		result = result + '<p>%s</p>\n' % doc

		if hasattr(object, '__path__'):
			modpkgs = []
			modnames = []
			for file in os.listdir(object.__path__[0]):
				path = os.path.join(object.__path__[0], file)
				modname = inspect.getmodulename(file)
				if modname != '__init__':
					if modname and modname not in modnames:
						modpkgs.append((modname, name, 0, 0))
						modnames.append(modname)
					elif ispackage(path):
						modpkgs.append((file, name, 1, 0))
			modpkgs.sort()
			contents = self.multicolumn(modpkgs, self.modpkglink)
			result = result + self.bigsection(
				'Package Contents', '#ffffff', '#aa55cc', contents)
		elif modules:
			contents = self.multicolumn(
				modules, lambda (key, value), s=self: s.modulelink(value))
			result = result + self.bigsection(
				'Modules', '#fffff', '#aa55cc', contents)

		if classes:
			classlist = map(lambda (key, value): value, classes)
			contents = [
				self.formattree(inspect.getclasstree(classlist, 1), name)]
			for key, value in classes:
				contents.append(self.document(value, key, name, fdict, cdict))
			result = result + self.bigsection(
				'Classes', '#ffffff', '#ee77aa', join(contents))
		if funcs:
			contents = []
			for key, value in funcs:
				contents.append(self.document(value, key, name, fdict, cdict))
			result = result + self.bigsection(
				'Functions', '#ffffff', '#eeaa77', join(contents))
		if data:
			contents = []
			for key, value in data:
				contents.append(self.document(value, key))
			result = result + self.bigsection(
				'Data', '#ffffff', '#55aa55', join(contents, '<br>\n'))
		if hasattr(object, '__author__'):
			contents = self.markup(str(object.__author__), self.preformat)
			result = result + self.bigsection(
				'Author', '#ffffff', '#7799ee', contents)
		if hasattr(object, '__credits__'):
			contents = self.markup(str(object.__credits__), self.preformat)
			result = result + self.bigsection(
				'Credits', '#ffffff', '#7799ee', contents)

		return result

	def docclass(self, object, name=None, mod=None, funcs={}, classes={},
				 *ignored):
		"""Produce HTML documentation for a class object."""
		realname = object.__name__
		name = name or realname
		bases = object.__bases__

		contents = []
		push = contents.append

		# Cute little class to pump out a horizontal rule between sections.
		class HorizontalRule:
			pass
			"""def __init__(self):
				self.needone = 0
			def maybe(self):
				if self.needone:
					push('<hr>\n')
				self.needone = 1"""
		hr = HorizontalRule()

		# List the mro, if non-trivial.
		mro = list(inspect.getmro(object))
		if len(mro) > 2:
			hr.maybe()
			push('<p>Method resolution order:</p>\n')
			for base in mro:
				push('%s<br>\n' % self.classlink(base, object.__module__))
			push('\n')

		def spill(msg, attrs, predicate):
			ok, attrs = _split_list(attrs, predicate)
			if ok:
				hr.maybe()
				push(msg)
				for name, kind, homecls, value in ok:
					push(self.document(getattr(object, name), name, mod,
									   funcs, classes, mdict, object))
					push('\n')
			return attrs

		def spillproperties(msg, attrs, predicate):
			ok, attrs = _split_list(attrs, predicate)
			if ok:
				hr.maybe()
				push(msg)
				for name, kind, homecls, value in ok:
					push('<dl><dt><strong>%s</strong></dt>\n' % name)
					if value.__doc__ is not None:
						doc = self.markup(value.__doc__, self.preformat,
										  funcs, classes, mdict)
						push('<dd><tt>%s</tt></dd>\n' % doc)
					for attr, tag in [('fget', '<em>get</em>'),
									  ('fset', '<em>set</em>'),
									  ('fdel', '<em>delete</em>')]:
						func = getattr(value, attr)
						if func is not None:
							base = self.document(func, tag, mod,
												 funcs, classes, mdict, object)
							push('<dd>%s</dd>\n' % base)
					push('</dl>\n')
			return attrs

		def spilldata(msg, attrs, predicate):
			ok, attrs = _split_list(attrs, predicate)
			if ok:
				hr.maybe()
				push(msg)
				for name, kind, homecls, value in ok:
					base = self.docother(getattr(object, name), name, mod)
					if callable(value) or inspect.isdatadescriptor(value):
						doc = getattr(value, "__doc__", None)
					else:
						doc = None
					if doc is None:
						push('<dl><dt>%s</dl>\n' % base)
					else:
						doc = self.markup(getdoc(value), self.preformat,
										  funcs, classes, mdict)
						doc = '<dd><tt>%s</tt>' % doc
						push('<dl><dt>%s%s</dl>\n' % (base, doc))
					push('\n')
			return attrs

		attrs = filter(lambda (name, kind, cls, value): visiblename(name),
					   inspect.classify_class_attrs(object))
		mdict = {}
		for key, kind, homecls, value in attrs:
			mdict[key] = anchor = '#' + name + '-' + key
			value = getattr(object, key)
			try:
				# The value may not be hashable (e.g., a data attr with
				# a dict or list value).
				mdict[value] = anchor
			except TypeError:
				pass

		while attrs:
			if mro:
				thisclass = mro.pop(0)
			else:
				thisclass = attrs[0][2]
			attrs, inherited = _split_list(attrs, lambda t: t[2] is thisclass)

			if thisclass is __builtin__.object:
				attrs = inherited
				continue
			elif thisclass is object:
				tag = 'defined here'
			else:
				tag = 'inherited from %s' % self.classlink(thisclass,
														   object.__module__)
			tag += ':<br>\n'

			# Sort attrs by name.
			attrs.sort(lambda t1, t2: cmp(t1[0], t2[0]))

			# Pump out the attrs, segregated by kind.
			attrs = spill('Methods %s' % tag, attrs,
						  lambda t: t[1] == 'method')
			attrs = spill('Class methods %s' % tag, attrs,
						  lambda t: t[1] == 'class method')
			attrs = spill('Static methods %s' % tag, attrs,
						  lambda t: t[1] == 'static method')
			attrs = spillproperties('Properties %s' % tag, attrs,
									lambda t: t[1] == 'property')
			attrs = spilldata('Data and other attributes %s' % tag, attrs,
							  lambda t: t[1] == 'data')
			assert attrs == []
			attrs = inherited

		contents = ''.join(contents)

		if name == realname:
			title = '<a name="%s">class <code>%s</code></a>' % (
				name, realname)
		else:
			title = '<code>%s</code> = <a name="%s">class %s</a>' % (
				name, name, realname)
		if bases:
			parents = []
			for base in bases:
				parents.append(self.classlink(base, object.__module__))
			title = title + '(%s)' % join(parents, ', ')
		doc = self.markup(getdoc(object), self.preformat, funcs, classes, mdict)
		doc = doc and '<tt>%s<br>&nbsp;</tt>' % doc

		return self.section(title, '#000000', '#ffc8d8', contents, 3, doc)

	def formatvalue(self, object):
		"""Format an argument default value as text."""
		return self.grey('=' + self.repr(object))

	def docroutine(self, object, name=None, mod=None,
				   funcs={}, classes={}, methods={}, cl=None):
		"""Produce HTML documentation for a function or method object."""
		realname = object.__name__
		name = name or realname
		anchor = (cl and cl.__name__ or '') + '-' + name
		note = ''
		skipdocs = 0
		if inspect.ismethod(object):
			imclass = object.im_class
			if cl:
				if imclass is not cl:
					note = ' from ' + self.classlink(imclass, mod)
			else:
				if object.im_self:
					note = ' method of %s instance' % self.classlink(
						object.im_self.__class__, mod)
				else:
					note = ' unbound %s method' % self.classlink(imclass,mod)
			object = object.im_func

		if name == realname:
			title = '<a name="%s">%s</a>' % (anchor, realname)
		else:
			if (cl and realname in cl.__dict__ and
				cl.__dict__[realname] is object):
				reallink = '<a href="#%s">%s</a>' % (
					cl.__name__ + '-' + realname, realname)
				skipdocs = 1
			else:
				reallink = realname
			title = '<a name="%s">%s</a> = %s' % (
				anchor, name, reallink)
		if inspect.isfunction(object):
			args, varargs, varkw, defaults = inspect.getargspec(object)
			argspec = inspect.formatargspec(
				args, varargs, varkw, defaults, formatvalue=self.formatvalue)
			if realname == '<lambda>':
				title = '%s <i>lambda</i> ' % name
				argspec = argspec[1:-1] # remove parentheses
		else:
			argspec = '(...)'

		decl = title + argspec + (note and self.grey(
			   '%s' % note))

		if skipdocs:
			return '<dl><dt>%s</dt></dl>\n' % decl
		else:
			doc = self.markup(
				getdoc(object), self.preformat, funcs, classes, methods)
			doc = doc and '<dd><tt>%s</tt></dd>' % doc
			return '<dl><dt>%s</dt>%s</dl>\n' % (decl, doc)

	def docother(self, object, name=None, mod=None, *ignored):
		"""Produce HTML documentation for a data object."""
		lhs = name and 'debug_Docother: %s = ' % name or ''
		return lhs + self.repr(object) + '<br>'

	def index(self, dir, shadowed=None):
		"""Generate an HTML index for a directory of modules."""
		modpkgs = []
		if shadowed is None: shadowed = {}
		seen = {}
		files = os.listdir(dir)

		def found(name, ispackage,
				  modpkgs=modpkgs, shadowed=shadowed, seen=seen):
			if name not in seen:
				modpkgs.append((name, '', ispackage, name in shadowed))
				seen[name] = 1
				shadowed[name] = 1

		# Package spam/__init__.py takes precedence over module spam.py.
		for file in files:
			path = os.path.join(dir, file)
			if ispackage(path): found(file, 1)
		for file in files:
			path = os.path.join(dir, file)
			if os.path.isfile(path):
				modname = inspect.getmodulename(file)
				if modname: found(modname, 0)

		modpkgs.sort()
		contents = self.multicolumn(modpkgs, self.modpkglink)
		return self.bigsection(dir, '#ffffff', '#ee77aa', contents)

# -------------------------------------------- text documentation generator

class TextRepr(Repr):
	"""Class for safely making a text representation of a Python object."""
	def __init__(self):
		Repr.__init__(self)
		self.maxlist = self.maxtuple = 20
		self.maxdict = 10
		self.maxstring = self.maxother = 100

	def repr1(self, x, level):
		if hasattr(type(x), '__name__'):
			methodname = 'repr_' + join(split(type(x).__name__), '_')
			if hasattr(self, methodname):
				return getattr(self, methodname)(x, level)
		return cram(stripid(repr(x)), self.maxother)

	def repr_string(self, x, level):
		test = cram(x, self.maxstring)
		testrepr = repr(test)
		if '\\' in test and '\\' not in replace(testrepr, r'\\', ''):
			# Backslashes are only literal in the string and are never
			# needed to make any special characters, so show a raw string.
			return 'r' + testrepr[0] + test + testrepr[0]
		return testrepr

	repr_str = repr_string

	def repr_instance(self, x, level):
		try:
			return cram(stripid(repr(x)), self.maxstring)
		except:
			return '<%s instance>' % x.__class__.__name__

class TextDoc(Doc):
	"""Formatter class for text documentation."""

	# ------------------------------------------- text formatting utilities

	_repr_instance = TextRepr()
	repr = _repr_instance.repr

	def bold(self, text):
		"""Format a string in bold by overstriking."""
		return join(map(lambda ch: ch + '\b' + ch, text), '')

	def indent(self, text, prefix='	'):
		"""Indent text by prepending a given prefix to each line."""
		if not text: return ''
		lines = split(text, '\n')
		lines = map(lambda line, prefix=prefix: prefix + line, lines)
		if lines: lines[-1] = rstrip(lines[-1])
		return join(lines, '\n')

	def section(self, title, contents):
		"""Format a section with a given heading."""
		return self.bold(title) + '\n' + rstrip(self.indent(contents)) + '\n\n'

	# ---------------------------------------------- type-specific routines

	def formattree(self, tree, modname, parent=None, prefix=''):
		"""Render in text a class tree as returned by inspect.getclasstree()."""
		result = ''
		for entry in tree:
			if type(entry) is type(()):
				c, bases = entry
				result = result + prefix + classname(c, modname)
				if bases and bases != (parent,):
					parents = map(lambda c, m=modname: classname(c, m), bases)
					result = result + '(%s)' % join(parents, ', ')
				result = result + '\n'
			elif type(entry) is type([]):
				result = result + self.formattree(
					entry, modname, c, prefix + '	')
		return result

	def docmodule(self, object, name=None, mod=None):
		"""Produce text documentation for a given module object."""
		name = object.__name__ # ignore the passed-in name
		synop, desc = splitdoc(getdoc(object))
		result = self.section('NAME', name + (synop and ' - ' + synop))

		try:
			file = inspect.getabsfile(object)
		except TypeError:
			file = '(built-in)'
		result = result + self.section('FILE', file)
		if desc:
			result = result + self.section('DESCRIPTION', desc)

		classes = []
		for key, value in inspect.getmembers(object, inspect.isclass):
			if (inspect.getmodule(value) or object) is object:
				if visiblename(key):
					classes.append((key, value))
		funcs = []
		for key, value in inspect.getmembers(object, inspect.isroutine):
			if inspect.isbuiltin(value) or inspect.getmodule(value) is object:
				if visiblename(key):
					funcs.append((key, value))
		data = []
		for key, value in inspect.getmembers(object, isdata):
			if visiblename(key):
				data.append((key, value))

		if hasattr(object, '__path__'):
			modpkgs = []
			for file in os.listdir(object.__path__[0]):
				path = os.path.join(object.__path__[0], file)
				modname = inspect.getmodulename(file)
				if modname != '__init__':
					if modname and modname not in modpkgs:
						modpkgs.append(modname)
					elif ispackage(path):
						modpkgs.append(file + ' (package)')
			modpkgs.sort()
			result = result + self.section(
				'PACKAGE CONTENTS', join(modpkgs, '\n'))

		if classes:
			classlist = map(lambda (key, value): value, classes)
			contents = [self.formattree(
				inspect.getclasstree(classlist, 1), name)]
			for key, value in classes:
				contents.append(self.document(value, key, name))
			result = result + self.section('CLASSES', join(contents, '\n'))

		if funcs:
			contents = []
			for key, value in funcs:
				contents.append(self.document(value, key, name))
			result = result + self.section('FUNCTIONS', join(contents, '\n'))

		if data:
			contents = []
			for key, value in data:
				contents.append(self.docother(value, key, name, 70))
			result = result + self.section('DATA', join(contents, '\n'))

		if hasattr(object, '__version__'):
			version = str(object.__version__)
			if version[:11] == '$' + 'Revision: ' and version[-1:] == '$':
				version = strip(version[11:-1])
			result = result + self.section('VERSION', version)
		if hasattr(object, '__date__'):
			result = result + self.section('DATE', str(object.__date__))
		if hasattr(object, '__author__'):
			result = result + self.section('AUTHOR', str(object.__author__))
		if hasattr(object, '__credits__'):
			result = result + self.section('CREDITS', str(object.__credits__))
		return result

	def docclass(self, object, name=None, mod=None):
		"""Produce text documentation for a given class object."""
		realname = object.__name__
		name = name or realname
		bases = object.__bases__

		def makename(c, m=object.__module__):
			return classname(c, m)

		if name == realname:
			title = 'class ' + self.bold(realname)
		else:
			title = self.bold(name) + ' = class ' + realname
		if bases:
			parents = map(makename, bases)
			title = title + '(%s)' % join(parents, ', ')

		doc = getdoc(object)
		contents = doc and [doc + '\n'] or []
		push = contents.append

		# List the mro, if non-trivial.
		mro = list(inspect.getmro(object))
		if len(mro) > 2:
			push("Method resolution order:")
			for base in mro:
				push('	' + makename(base))
			push('')

		# Cute little class to pump out a horizontal rule between sections.
		class HorizontalRule:
			def __init__(self):
				self.needone = 0
			def maybe(self):
				if self.needone:
					push('-' * 70)
				self.needone = 1
		hr = HorizontalRule()

		def spill(msg, attrs, predicate):
			ok, attrs = _split_list(attrs, predicate)
			if ok:
				hr.maybe()
				push(msg)
				for name, kind, homecls, value in ok:
					push(self.document(getattr(object, name),
									   name, mod, object))
			return attrs

		def spillproperties(msg, attrs, predicate):
			ok, attrs = _split_list(attrs, predicate)
			if ok:
				hr.maybe()
				push(msg)
				for name, kind, homecls, value in ok:
					push(name)
					need_blank_after_doc = 0
					doc = getdoc(value) or ''
					if doc:
						push(self.indent(doc))
						need_blank_after_doc = 1
					for attr, tag in [('fget', '<get>'),
									  ('fset', '<set>'),
									  ('fdel', '<delete>')]:
						func = getattr(value, attr)
						if func is not None:
							if need_blank_after_doc:
								push('')
								need_blank_after_doc = 0
							base = self.document(func, tag, mod)
							push(self.indent(base))
			return attrs

		def spilldata(msg, attrs, predicate):
			ok, attrs = _split_list(attrs, predicate)
			if ok:
				hr.maybe()
				push(msg)
				for name, kind, homecls, value in ok:
					if callable(value) or inspect.isdatadescriptor(value):
						doc = getattr(value, "__doc__", None)
					else:
						doc = None
					push(self.docother(getattr(object, name),
									   name, mod, 70, doc) + '\n')
			return attrs

		attrs = filter(lambda (name, kind, cls, value): visiblename(name),
					   inspect.classify_class_attrs(object))
		while attrs:
			if mro:
				thisclass = mro.pop(0)
			else:
				thisclass = attrs[0][2]
			attrs, inherited = _split_list(attrs, lambda t: t[2] is thisclass)

			if thisclass is __builtin__.object:
				attrs = inherited
				continue
			elif thisclass is object:
				tag = "defined here"
			else:
				tag = "inherited from %s" % classname(thisclass,
													  object.__module__)
			filter(lambda t: not t[0].startswith('_'), attrs)

			# Sort attrs by name.
			attrs.sort()

			# Pump out the attrs, segregated by kind.
			attrs = spill("Methods %s:\n" % tag, attrs,
						  lambda t: t[1] == 'method')
			attrs = spill("Class methods %s:\n" % tag, attrs,
						  lambda t: t[1] == 'class method')
			attrs = spill("Static methods %s:\n" % tag, attrs,
						  lambda t: t[1] == 'static method')
			attrs = spillproperties("Properties %s:\n" % tag, attrs,
									lambda t: t[1] == 'property')
			attrs = spilldata("Data and other attributes %s:\n" % tag, attrs,
							  lambda t: t[1] == 'data')
			assert attrs == []
			attrs = inherited

		contents = '\n'.join(contents)
		if not contents:
			return title + '\n'
		return title + '\n' + self.indent(rstrip(contents), ' |  ') + '\n'

	def formatvalue(self, object):
		"""Format an argument default value as text."""
		return '=' + self.repr(object)

	def docroutine(self, object, name=None, mod=None, cl=None):
		"""Produce text documentation for a function or method object."""
		realname = object.__name__
		name = name or realname
		note = ''
		skipdocs = 0
		if inspect.ismethod(object):
			imclass = object.im_class
			if cl:
				if imclass is not cl:
					note = ' from ' + classname(imclass, mod)
			else:
				if object.im_self:
					note = ' method of %s instance' % classname(
						object.im_self.__class__, mod)
				else:
					note = ' unbound %s method' % classname(imclass,mod)
			object = object.im_func

		if name == realname:
			title = self.bold(realname)
		else:
			if (cl and realname in cl.__dict__ and
				cl.__dict__[realname] is object):
				skipdocs = 1
			title = self.bold(name) + ' = ' + realname
		if inspect.isfunction(object):
			args, varargs, varkw, defaults = inspect.getargspec(object)
			argspec = inspect.formatargspec(
				args, varargs, varkw, defaults, formatvalue=self.formatvalue)
			if realname == '<lambda>':
				title = 'lambda'
				argspec = argspec[1:-1] # remove parentheses
		else:
			argspec = '(...)'
		decl = title + argspec + note

		if skipdocs:
			return decl + '\n'
		else:
			doc = getdoc(object) or ''
			return decl + '\n' + (doc and rstrip(self.indent(doc)) + '\n')

	def docother(self, object, name=None, mod=None, maxlen=None, doc=None):
		"""Produce text documentation for a data object."""
		repr = self.repr(object)
		if maxlen:
			line = (name and name + ' = ' or '') + repr
			chop = maxlen - len(line)
			if chop < 0: repr = repr[:chop] + '...'
		line = (name and self.bold(name) + ' = ' or '') + repr
		if doc is not None:
			line += '\n' + self.indent(str(doc))
		return line

# --------------------------------------------------------- user interfaces

def pager(text):
	"""The first time this is called, determine what kind of pager to use."""
	global pager
	pager = getpager()
	pager(text)

def getpager():
	"""Decide what method to use for paging through text."""
	if type(sys.stdout) is not types.FileType:
		return plainpager
	if not sys.stdin.isatty() or not sys.stdout.isatty():
		return plainpager
	if os.environ.get('TERM') in ['dumb', 'emacs']:
		return plainpager
	if 'PAGER' in os.environ:
		if sys.platform == 'win32': # pipes completely broken in Windows
			return lambda text: tempfilepager(plain(text), os.environ['PAGER'])
		elif os.environ.get('TERM') in ['dumb', 'emacs']:
			return lambda text: pipepager(plain(text), os.environ['PAGER'])
		else:
			return lambda text: pipepager(text, os.environ['PAGER'])
	if sys.platform == 'win32' or sys.platform.startswith('os2'):
		return lambda text: tempfilepager(plain(text), 'more <')
	if hasattr(os, 'system') and os.system('(less) 2>/dev/null') == 0:
		return lambda text: pipepager(text, 'less')

	import tempfile
	(fd, filename) = tempfile.mkstemp()
	os.close(fd)
	try:
		if hasattr(os, 'system') and os.system('more %s' % filename) == 0:
			return lambda text: pipepager(text, 'more')
		else:
			return ttypager
	finally:
		os.unlink(filename)

def plain(text):
	"""Remove boldface formatting from text."""
	return re.sub('.\b', '', text)

def pipepager(text, cmd):
	"""Page through text by feeding it to another program."""
	pipe = os.popen(cmd, 'w')
	try:
		pipe.write(text)
		pipe.close()
	except IOError:
		pass # Ignore broken pipes caused by quitting the pager program.

def tempfilepager(text, cmd):
	"""Page through text by invoking a program on a temporary file."""
	import tempfile
	filename = tempfile.mktemp()
	file = open(filename, 'w')
	file.write(text)
	file.close()
	try:
		os.system(cmd + ' ' + filename)
	finally:
		os.unlink(filename)

def ttypager(text):
	"""Page through text on a text terminal."""
	lines = split(plain(text), '\n')
	try:
		import tty
		fd = sys.stdin.fileno()
		old = tty.tcgetattr(fd)
		tty.setcbreak(fd)
		getchar = lambda: sys.stdin.read(1)
	except (ImportError, AttributeError):
		tty = None
		getchar = lambda: sys.stdin.readline()[:-1][:1]

	try:
		r = inc = os.environ.get('LINES', 25) - 1
		sys.stdout.write(join(lines[:inc], '\n') + '\n')
		while lines[r:]:
			sys.stdout.write('-- more --')
			sys.stdout.flush()
			c = getchar()

			if c in ['q', 'Q']:
				sys.stdout.write('\r		  \r')
				break
			elif c in ['\r', '\n']:
				sys.stdout.write('\r		  \r' + lines[r] + '\n')
				r = r + 1
				continue
			if c in ['b', 'B', '\x1b']:
				r = r - inc - inc
				if r < 0: r = 0
			sys.stdout.write('\n' + join(lines[r:r+inc], '\n') + '\n')
			r = r + inc

	finally:
		if tty:
			tty.tcsetattr(fd, tty.TCSAFLUSH, old)

def plainpager(text):
	"""Simply print unformatted text.  This is the ultimate fallback."""
	sys.stdout.write(plain(text))

def describe(thing):
	"""Produce a short description of the given thing."""
	if inspect.ismodule(thing):
		if thing.__name__ in sys.builtin_module_names:
			return 'built-in module ' + thing.__name__
		if hasattr(thing, '__path__'):
			return 'package ' + thing.__name__
		else:
			return 'module ' + thing.__name__
	if inspect.isbuiltin(thing):
		return 'built-in function ' + thing.__name__
	if inspect.isclass(thing):
		return 'class ' + thing.__name__
	if inspect.isfunction(thing):
		return 'function ' + thing.__name__
	if inspect.ismethod(thing):
		return 'method ' + thing.__name__
	if type(thing) is types.InstanceType:
		return 'instance of ' + thing.__class__.__name__
	return type(thing).__name__

def locate(path, forceload=0):
	"""Locate an object by name or dotted path, importing as necessary."""
	parts = [part for part in split(path, '.') if part]
	module, n = None, 0
	while n < len(parts):
		nextmodule = safeimport(join(parts[:n+1], '.'), forceload)
		if nextmodule: module, n = nextmodule, n + 1
		else: break
	if module:
		object = module
		for part in parts[n:]:
			try: object = getattr(object, part)
			except AttributeError: return None
		return object
	else:
		if hasattr(__builtin__, path):
			return getattr(__builtin__, path)

# --------------------------------------- interactive interpreter interface

text = TextDoc()
html = HTMLDoc()

def resolve(thing, forceload=0):
	"""Given an object or a path to an object, get the object and its name."""
	if isinstance(thing, str):
		object = locate(thing, forceload)
		if not object:
			raise ImportError, 'no Python documentation found for %r' % thing
		return object, thing
	else:
		return thing, getattr(thing, '__name__', None)

def doc(thing, title='Python Library Documentation: %s', forceload=0):
	"""Display text documentation, given an object or a path to an object."""
	try:
		object, name = resolve(thing, forceload)
		desc = describe(object)
		module = inspect.getmodule(object)
		if name and '.' in name:
			desc += ' in ' + name[:name.rfind('.')]
		elif module and module is not object:
			desc += ' in module ' + module.__name__
		pager(title % desc + '\n\n' + text.document(object, name))
	except (ImportError, ErrorDuringImport), value:
		print value

def writedoc(thing, forceload=0):
	"""Write HTML documentation to a file in the current directory."""
	try:
		object, name = resolve(thing, forceload)
		page = html.page(describe(object), html.document(object, name))
		file = open(name + '.html', 'w')
		file.write(page)
		file.close()
		print 'wrote', name + '.html'
	except (ImportError, ErrorDuringImport), value:
		print value

def writedocs(dir, pkgpath='', done=None):
	"""Write out HTML documentation for all modules in a directory tree."""
	if done is None: done = {}
	for file in os.listdir(dir):
		path = os.path.join(dir, file)
		if ispackage(path):
			writedocs(path, pkgpath + file + '.', done)
		elif os.path.isfile(path):
			modname = inspect.getmodulename(path)
			if modname:
				if modname == '__init__':
					modname = pkgpath[:-1] # remove trailing period
				else:
					modname = pkgpath + modname
				if modname not in done:
					done[modname] = 1
					writedoc(modname)

class Helper:
	keywords = {
		'and': 'BOOLEAN',
		'assert': ('ref/assert', ''),
		'break': ('ref/break', 'while for'),
		'class': ('ref/class', 'CLASSES SPECIALMETHODS'),
		'continue': ('ref/continue', 'while for'),
		'def': ('ref/function', ''),
		'del': ('ref/del', 'BASICMETHODS'),
		'elif': 'if',
		'else': ('ref/if', 'while for'),
		'except': 'try',
		'exec': ('ref/exec', ''),
		'finally': 'try',
		'for': ('ref/for', 'break continue while'),
		'from': 'import',
		'global': ('ref/global', 'NAMESPACES'),
		'if': ('ref/if', 'TRUTHVALUE'),
		'import': ('ref/import', 'MODULES'),
		'in': ('ref/comparisons', 'SEQUENCEMETHODS2'),
		'is': 'COMPARISON',
		'lambda': ('ref/lambdas', 'FUNCTIONS'),
		'not': 'BOOLEAN',
		'or': 'BOOLEAN',
		'pass': ('ref/pass', ''),
		'print': ('ref/print', ''),
		'raise': ('ref/raise', 'EXCEPTIONS'),
		'return': ('ref/return', 'FUNCTIONS'),
		'try': ('ref/try', 'EXCEPTIONS'),
		'while': ('ref/while', 'break continue if TRUTHVALUE'),
		'yield': ('ref/yield', ''),
	}

	topics = {
		'TYPES': ('ref/types', 'STRINGS UNICODE NUMBERS SEQUENCES MAPPINGS FUNCTIONS CLASSES MODULES FILES inspect'),
		'STRINGS': ('ref/strings', 'str UNICODE SEQUENCES STRINGMETHODS FORMATTING TYPES'),
		'STRINGMETHODS': ('lib/string-methods', 'STRINGS FORMATTING'),
		'FORMATTING': ('lib/typesseq-strings', 'OPERATORS'),
		'UNICODE': ('ref/strings', 'encodings unicode SEQUENCES STRINGMETHODS FORMATTING TYPES'),
		'NUMBERS': ('ref/numbers', 'INTEGER FLOAT COMPLEX TYPES'),
		'INTEGER': ('ref/integers', 'int range'),
		'FLOAT': ('ref/floating', 'float math'),
		'COMPLEX': ('ref/imaginary', 'complex cmath'),
		'SEQUENCES': ('lib/typesseq', 'STRINGMETHODS FORMATTING xrange LISTS'),
		'MAPPINGS': 'DICTIONARIES',
		'FUNCTIONS': ('lib/typesfunctions', 'def TYPES'),
		'METHODS': ('lib/typesmethods', 'class def CLASSES TYPES'),
		'CODEOBJECTS': ('lib/bltin-code-objects', 'compile FUNCTIONS TYPES'),
		'TYPEOBJECTS': ('lib/bltin-type-objects', 'types TYPES'),
		'FRAMEOBJECTS': 'TYPES',
		'TRACEBACKS': 'TYPES',
		'NONE': ('lib/bltin-null-object', ''),
		'ELLIPSIS': ('lib/bltin-ellipsis-object', 'SLICINGS'),
		'FILES': ('lib/bltin-file-objects', ''),
		'SPECIALATTRIBUTES': ('lib/specialattrs', ''),
		'CLASSES': ('ref/types', 'class SPECIALMETHODS PRIVATENAMES'),
		'MODULES': ('lib/typesmodules', 'import'),
		'PACKAGES': 'import',
		'EXPRESSIONS': ('ref/summary', 'lambda or and not in is BOOLEAN COMPARISON BITWISE SHIFTING BINARY FORMATTING POWER UNARY ATTRIBUTES SUBSCRIPTS SLICINGS CALLS TUPLES LISTS DICTIONARIES BACKQUOTES'),
		'OPERATORS': 'EXPRESSIONS',
		'PRECEDENCE': 'EXPRESSIONS',
		'OBJECTS': ('ref/objects', 'TYPES'),
		'SPECIALMETHODS': ('ref/specialnames', 'BASICMETHODS ATTRIBUTEMETHODS CALLABLEMETHODS SEQUENCEMETHODS1 MAPPINGMETHODS SEQUENCEMETHODS2 NUMBERMETHODS CLASSES'),
		'BASICMETHODS': ('ref/customization', 'cmp hash repr str SPECIALMETHODS'),
		'ATTRIBUTEMETHODS': ('ref/attribute-access', 'ATTRIBUTES SPECIALMETHODS'),
		'CALLABLEMETHODS': ('ref/callable-types', 'CALLS SPECIALMETHODS'),
		'SEQUENCEMETHODS1': ('ref/sequence-types', 'SEQUENCES SEQUENCEMETHODS2 SPECIALMETHODS'),
		'SEQUENCEMETHODS2': ('ref/sequence-methods', 'SEQUENCES SEQUENCEMETHODS1 SPECIALMETHODS'),
		'MAPPINGMETHODS': ('ref/sequence-types', 'MAPPINGS SPECIALMETHODS'),
		'NUMBERMETHODS': ('ref/numeric-types', 'NUMBERS AUGMENTEDASSIGNMENT SPECIALMETHODS'),
		'EXECUTION': ('ref/execmodel', 'NAMESPACES DYNAMICFEATURES EXCEPTIONS'),
		'NAMESPACES': ('ref/naming', 'global ASSIGNMENT DELETION DYNAMICFEATURES'),
		'DYNAMICFEATURES': ('ref/dynamic-features', ''),
		'SCOPING': 'NAMESPACES',
		'FRAMES': 'NAMESPACES',
		'EXCEPTIONS': ('ref/exceptions', 'try except finally raise'),
		'COERCIONS': ('ref/coercion-rules','CONVERSIONS'),
		'CONVERSIONS': ('ref/conversions', 'COERCIONS'),
		'IDENTIFIERS': ('ref/identifiers', 'keywords SPECIALIDENTIFIERS'),
		'SPECIALIDENTIFIERS': ('ref/id-classes', ''),
		'PRIVATENAMES': ('ref/atom-identifiers', ''),
		'LITERALS': ('ref/atom-literals', 'STRINGS BACKQUOTES NUMBERS TUPLELITERALS LISTLITERALS DICTIONARYLITERALS'),
		'TUPLES': 'SEQUENCES',
		'TUPLELITERALS': ('ref/exprlists', 'TUPLES LITERALS'),
		'LISTS': ('lib/typesseq-mutable', 'LISTLITERALS'),
		'LISTLITERALS': ('ref/lists', 'LISTS LITERALS'),
		'DICTIONARIES': ('lib/typesmapping', 'DICTIONARYLITERALS'),
		'DICTIONARYLITERALS': ('ref/dict', 'DICTIONARIES LITERALS'),
		'BACKQUOTES': ('ref/string-conversions', 'repr str STRINGS LITERALS'),
		'ATTRIBUTES': ('ref/attribute-references', 'getattr hasattr setattr ATTRIBUTEMETHODS'),
		'SUBSCRIPTS': ('ref/subscriptions', 'SEQUENCEMETHODS1'),
		'SLICINGS': ('ref/slicings', 'SEQUENCEMETHODS2'),
		'CALLS': ('ref/calls', 'EXPRESSIONS'),
		'POWER': ('ref/power', 'EXPRESSIONS'),
		'UNARY': ('ref/unary', 'EXPRESSIONS'),
		'BINARY': ('ref/binary', 'EXPRESSIONS'),
		'SHIFTING': ('ref/shifting', 'EXPRESSIONS'),
		'BITWISE': ('ref/bitwise', 'EXPRESSIONS'),
		'COMPARISON': ('ref/comparisons', 'EXPRESSIONS BASICMETHODS'),
		'BOOLEAN': ('ref/Booleans', 'EXPRESSIONS TRUTHVALUE'),
		'ASSERTION': 'assert',
		'ASSIGNMENT': ('ref/assignment', 'AUGMENTEDASSIGNMENT'),
		'AUGMENTEDASSIGNMENT': ('ref/augassign', 'NUMBERMETHODS'),
		'DELETION': 'del',
		'PRINTING': 'print',
		'RETURNING': 'return',
		'IMPORTING': 'import',
		'CONDITIONAL': 'if',
		'LOOPING': ('ref/compound', 'for while break continue'),
		'TRUTHVALUE': ('lib/truth', 'if while and or not BASICMETHODS'),
		'DEBUGGING': ('lib/module-pdb', 'pdb'),
	}

	def __init__(self, input, output):
		self.input = input
		self.output = output
		self.docdir = None
		execdir = os.path.dirname(sys.executable)
		homedir = os.environ.get('PYTHONHOME')
		for dir in [os.environ.get('PYTHONDOCS'),
					homedir and os.path.join(homedir, 'doc'),
					os.path.join(execdir, 'doc'),
					'/usr/doc/python-docs-' + split(sys.version)[0],
					'/usr/doc/python-' + split(sys.version)[0],
					'/usr/doc/python-docs-' + sys.version[:3],
					'/usr/doc/python-' + sys.version[:3],
					os.path.join(sys.prefix, 'Resources/English.lproj/Documentation')]:
			if dir and os.path.isdir(os.path.join(dir, 'lib')):
				self.docdir = dir

	def __repr__(self):
		if inspect.stack()[1][3] == '?':
			self()
			return ''
		return '<pydoc.Helper instance>'

	def __call__(self, request=None):
		if request is not None:
			self.help(request)
		else:
			self.intro()
			self.interact()
			self.output.write('''
You are now leaving help and returning to the Python interpreter.
If you want to ask for help on a particular object directly from the
interpreter, you can type "help(object)".  Executing "help('string')"
has the same effect as typing a particular string at the help> prompt.
''')

	def interact(self):
		self.output.write('\n')
		while True:
			self.output.write('help> ')
			self.output.flush()
			try:
				request = self.input.readline()
				if not request: break
			except KeyboardInterrupt: break
			request = strip(replace(request, '"', '', "'", ''))
			if lower(request) in ['q', 'quit']: break
			self.help(request)

	def help(self, request):
		if type(request) is type(''):
			if request == 'help': self.intro()
			elif request == 'keywords': self.listkeywords()
			elif request == 'topics': self.listtopics()
			elif request == 'modules': self.listmodules()
			elif request[:8] == 'modules ':
				self.listmodules(split(request)[1])
			elif request in self.keywords: self.showtopic(request)
			elif request in self.topics: self.showtopic(request)
			elif request: doc(request, 'Help on %s:')
		elif isinstance(request, Helper): self()
		else: doc(request, 'Help on %s:')
		self.output.write('\n')

	def intro(self):
		self.output.write('''
Welcome to Python %s!  This is the online help utility.

If this is your first time using Python, you should definitely check out
the tutorial on the Internet at http://www.python.org/doc/tut/.

Enter the name of any module, keyword, or topic to get help on writing
Python programs and using Python modules.  To quit this help utility and
return to the interpreter, just type "quit".

To get a list of available modules, keywords, or topics, type "modules",
"keywords", or "topics".  Each module also comes with a one-line summary
of what it does; to list the modules whose summaries contain a given word
such as "spam", type "modules spam".
''' % sys.version[:3])

	def list(self, items, columns=4, width=80):
		items = items[:]
		items.sort()
		colw = width / columns
		rows = (len(items) + columns - 1) / columns
		for row in range(rows):
			for col in range(columns):
				i = col * rows + row
				if i < len(items):
					self.output.write(items[i])
					if col < columns - 1:
						self.output.write(' ' + ' ' * (colw-1 - len(items[i])))
			self.output.write('\n')

	def listkeywords(self):
		self.output.write('''
Here is a list of the Python keywords.  Enter any keyword to get more help.

''')
		self.list(self.keywords.keys())

	def listtopics(self):
		self.output.write('''
Here is a list of available topics.  Enter any topic name to get more help.

''')
		self.list(self.topics.keys())

	def showtopic(self, topic):
		if not self.docdir:
			self.output.write('''
Sorry, topic and keyword documentation is not available because the Python
HTML documentation files could not be found.  If you have installed them,
please set the environment variable PYTHONDOCS to indicate their location.
''')
			return
		target = self.topics.get(topic, self.keywords.get(topic))
		if not target:
			self.output.write('no documentation found for %s\n' % repr(topic))
			return
		if type(target) is type(''):
			return self.showtopic(target)

		filename, xrefs = target
		filename = self.docdir + '/' + filename + '.html'
		try:
			file = open(filename)
		except:
			self.output.write('could not read docs from %s\n' % filename)
			return

		divpat = re.compile('<div[^>]*navigat.*?</div.*?>', re.I | re.S)
		addrpat = re.compile('<address.*?>.*?</address.*?>', re.I | re.S)
		document = re.sub(addrpat, '', re.sub(divpat, '', file.read()))
		file.close()

		import htmllib, formatter, StringIO
		buffer = StringIO.StringIO()
		parser = htmllib.HTMLParser(
			formatter.AbstractFormatter(formatter.DumbWriter(buffer)))
		parser.start_table = parser.do_p
		parser.end_table = lambda parser=parser: parser.do_p({})
		parser.start_tr = parser.do_br
		parser.start_td = parser.start_th = lambda a, b=buffer: b.write('\t')
		parser.feed(document)
		buffer = replace(buffer.getvalue(), '\xa0', ' ', '\n', '\n  ')
		pager('  ' + strip(buffer) + '\n')
		if xrefs:
			buffer = StringIO.StringIO()
			formatter.DumbWriter(buffer).send_flowing_data(
				'Related help topics: ' + join(split(xrefs), ', ') + '\n')
			self.output.write('\n%s\n' % buffer.getvalue())

	def listmodules(self, key=''):
		if key:
			self.output.write('''
Here is a list of matching modules.  Enter any module name to get more help.

''')
			apropos(key)
		else:
			self.output.write('''
Please wait a moment while I gather a list of all available modules...

''')
			modules = {}
			def callback(path, modname, desc, modules=modules):
				if modname and modname[-9:] == '.__init__':
					modname = modname[:-9] + ' (package)'
				if find(modname, '.') < 0:
					modules[modname] = 1
			ModuleScanner().run(callback)
			self.list(modules.keys())
			self.output.write('''
Enter any module name to get more help.  Or, type "modules spam" to search
for modules whose descriptions contain the word "spam".
''')

help = Helper(sys.stdin, sys.stdout)

class Scanner:
	"""A generic tree iterator."""
	def __init__(self, roots, children, descendp):
		self.roots = roots[:]
		self.state = []
		self.children = children
		self.descendp = descendp

	def next(self):
		if not self.state:
			if not self.roots:
				return None
			root = self.roots.pop(0)
			self.state = [(root, self.children(root))]
		node, children = self.state[-1]
		if not children:
			self.state.pop()
			return self.next()
		child = children.pop(0)
		if self.descendp(child):
			self.state.append((child, self.children(child)))
		return child

class ModuleScanner(Scanner):
	"""An interruptible scanner that searches module synopses."""
	def __init__(self):
		roots = map(lambda dir: (dir, ''), pathdirs())
		Scanner.__init__(self, roots, self.submodules, self.isnewpackage)
		self.inodes = map(lambda (dir, pkg): os.stat(dir).st_ino, roots)

	def submodules(self, (dir, package)):
		children = []
		for file in os.listdir(dir):
			path = os.path.join(dir, file)
			if ispackage(path):
				children.append((path, package + (package and '.') + file))
			else:
				children.append((path, package))
		children.sort() # so that spam.py comes before spam.pyc or spam.pyo
		return children

	def isnewpackage(self, (dir, package)):
		inode = os.path.exists(dir) and os.stat(dir).st_ino
		if not (os.path.islink(dir) and inode in self.inodes):
			self.inodes.append(inode) # detect circular symbolic links
			return ispackage(dir)
		return False

	def run(self, callback, key=None, completer=None):
		if key: key = lower(key)
		self.quit = False
		seen = {}

		for modname in sys.builtin_module_names:
			if modname != '__main__':
				seen[modname] = 1
				if key is None:
					callback(None, modname, '')
				else:
					desc = split(__import__(modname).__doc__ or '', '\n')[0]
					if find(lower(modname + ' - ' + desc), key) >= 0:
						callback(None, modname, desc)

		while not self.quit:
			node = self.next()
			if not node: break
			path, package = node
			modname = inspect.getmodulename(path)
			if os.path.isfile(path) and modname:
				modname = package + (package and '.') + modname
				if not modname in seen:
					seen[modname] = 1 # if we see spam.py, skip spam.pyc
					if key is None:
						callback(path, modname, '')
					else:
						desc = synopsis(path) or ''
						if find(lower(modname + ' - ' + desc), key) >= 0:
							callback(path, modname, desc)
		if completer: completer()

def apropos(key):
	"""Print all the one-line module summaries that contain a substring."""
	def callback(path, modname, desc):
		if modname[-9:] == '.__init__':
			modname = modname[:-9] + ' (package)'
		print modname, desc and '- ' + desc
	try: import warnings
	except ImportError: pass
	else: warnings.filterwarnings('ignore') # ignore problems during import
	ModuleScanner().run(callback, key)


################################################## make it

import scribus
import sys
sys.setappdefaultencoding("utf8")

writedoc(scribus)
writedoc(scribus.PDFfile)
writedoc(scribus.Printer)
