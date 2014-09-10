#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re, sys

class Symbol:
	def __init__(self, name, grammar):
		self.name = name
		self.grammar = grammar
		self._isTerminal = None
		self._productions = None
	def __hash__(self):
		return id(self)
	def productions(self):
		if self._productions == None:
			self._productions = ()
			for p in self.grammar.productions:
				if p.defines(self):
					self._productions += (p,)
		return self._productions
	def isTerminal(self):
		if self._isTerminal == None:
			for p in self.grammar.productions:
				if p.defines(self):
					self._isTerminal = False
					break
			if self._isTerminal == None:
				self._isTerminal = True
		return self._isTerminal
	def __str__(self):
		if self.isTerminal():
			return "[" + self.name + "]"
		return self.name;
#	def __eq__(self, other):
#		if not isinstance(other, Symbol):
#			return False
#		return self.name == other.name and self.grammar == other.grammar


class Production:
	def __init__(self, head, body, grammar, action = None):
		if not isinstance(head, Symbol): raise TypeError, "Head must be a symbol"
		if not isinstance(body, tuple): raise TypeError, "body must be a tuple"
		self.head = head
		self.body = body
		self.grammar = grammar
		if grammar:
			self.name = len(grammar.productions)
		else:
			self.name = 0
		self.action = action or ActionCode()
	def defines(self, symbol):
		return symbol == self.head
	def contains(self, symbol):
		return symbol in self.body
	def __str__(self):
		retval = str(self.head) + " ->"
		for symbol in self.body:
			retval += " " + str(symbol)
		return retval

ArgPattern = re.compile("arg[0-9]+")
class ActionCode:
	def __init__(self, code = "result = arg0;"):
		if code == "":
			self.code = "result = arg0;"
		else:
			self.code = code #Code with arg0, arg1, arg2... as arguments, assigning to result
		global ArgPattern #Find the arguments that should be declared if provided by the production
		self.args = ArgPattern.findall(self.code)
		if "result" not in self.code:
			print >> sys.stderr, "WARNING: Action code %s does not set the result variable!" % str(self)
	def __str__(self):
		return "{" + self.code + "}"

class Grammar:
	def __init__(self, root):
		if not isinstance(root, Symbol): raise TypeError, "root must be a root symbol"
		root.grammar = self
		self.root = Symbol("root", self) #Root symbol, this is agumented, it only has one simple production
		self.EOF = Symbol("EOF", self) #End-Of-File symbol, used later
		self.symbols = (self.root, root, self.EOF)
		self.rootProduction = Production(self.root, (root,), None)
		self.productions = (self.rootProduction,)
		self.rootProduction.grammar = self
	def __str__(self):
		retval = ""
		for production in self.productions:
			retval += str(production) + "\n"
		return retval[:-1]

	def nonterminals(self):
		for symbol in self.symbols:
			if not symbol.isTerminal():
				yield symbol


