import token
import tokenize
import compiler
import inspect

#from scribus import *
import scribus
print inspect.getmoduleinfo(scribus)
#print inspect.getsource(haveDoc())


xmodule_text = '''
""" moduledocstring """
import sys

def test():
    """testdoc"""
    return 1

class TestClass:
    """testclassdoc"""
    classconst1 = 1
    def meth1(self):
        """meth1 doc"""
        pass
    def meth2(self):
        """meth2 doc"""
        pass
    def meth3(self):
        raise "error"

cons1 = 1
cons2 = 2
'''
module_text = """
from scribus import *
help(PDFfile)
"""

class Classes:
    """ Data structure - classes holder. """
    def __init__(self):
        self.name = ""
        self.doc = ""
        self.procedures = []
        self.constants = []


class Module:
    """ Main data structure - everything is stored here. """
    def __init__(self):
        self.name = "scribus"
        self.doc = ""
        self.procedures = []
        self.classes = []
        self.constants = []


class Scridoc:
    """ Scribus replacement for PyDoc.
        We don't need the HTML hell :) """

    def __init__(self, aText):
        """ Initialization and main loop.
            1 Module() ... N Classes()
            """
        self.module = Module()
        self.classes = Classes()
        self.ast = compiler.parse(aText)
        print self.ast
        #self.parseNodes(ast, self.module)
        self.parseModule()
        self.parseImport()
        self.parseClasses()
        self.parseProcedures()
        self.parseConstants()

    def parseImport(self):
        """ Imports """
        for i in self.ast.getChildNodes():
            if isinstance(i, compiler.ast.Import):
                print i.names
 
    def parseModule(self):
        """ Top of the object tree.
            Just get the docstring and dive into deep"""
        self.module.doc = self.ast.doc
        self.ast = self.ast.node

    def parseClasses(self):
        """ Create classes documentation first.
            All Class sub-trees are handled here."""
        for i in self.ast.getChildNodes():
            if isinstance(i, compiler.ast.Class):
                self.classes = Classes()
                self.classes.name = i.name
                self.classes.doc = i.doc
                self.parseNode(i.code, self.classes)
                self.module.classes.append(self.classes)

    def parseProcedures(self):
        """ Functions """
        for i in self.ast.getChildNodes():
            if isinstance(i, compiler.ast.Function):
                self.parseNode(i, self.module)

    def parseConstants(self):
        """ And constants finally. """
        for i in self.ast.getChildNodes():
            if isinstance(i, compiler.ast.AssName) or isinstance(i, compiler.ast.Assign):
                self.parseNode(i, self.module)

    def parseNode(self, node, container):
        """ Go through object tree recursively with parseNodes().
            container is Module or Classes object depending
            the context."""
        if isinstance(node, compiler.ast.Module):
            self.module.doc = self.module.doc + node.doc
        if isinstance(node, compiler.ast.Function):
            container.procedures.append((node.name, node.doc))
        if isinstance(node, compiler.ast.Class):
            self.parseClass(node)
            print node.name, ' ', node.doc, ' ', node
        if isinstance(node, compiler.ast.AssName):
            container.constants.append(node.name)
        if isinstance(node, compiler.ast.Node):
            #print node, ' Node'
            pass
        self.parseNodes(node, container)

    def parseNodes(self, nodes, container):
        """ Recursion with parseNode() """
        for i in nodes.getChildNodes():
            self.parseNode(i, container)


print '\nSCRIDOC: Parse tree'
s = Scridoc(module_text)

print '\nOUTPUT:'
print '* Module **************'
print s.module.name, ' ', s.module.doc
print '* Procedures***********'
print s.module.procedures
print '* Classes *************'
for i in s.module.classes:
    print i.name, ' ', i.procedures, ' ', i.constants
print '* Constants ***********'
print s.module.constants

