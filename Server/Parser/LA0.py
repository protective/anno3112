#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""Classes and functions for working LA(0) parser generation
Note: This just implements the subset of functions that can be useful for LALR parser generation.
"""

from grammar import *
from ItemSet import *

class Item:
	"Representation of an item for an LA(0) parser"
	def __init__(self, production, position):
		self.production = production
		self.position = position
		self.hash = production.name ^ position
	def rehash(self):
		self.hash = self.production.name ^ self.position
	def __eq__(self, item):
		if self.hash != item.hash:
			return False
		return item.production == self.production and self.position == item.position
	def __cmp__(self, other):
		return self.hash - other.hash
	def nextSymbol(self):
		"Gets the symbol after position, or None"
		try:
			return self.production.body[self.position]
		except:
			return None
		#if self.position >= len(self.production.body):
		#	return None
		#return self.production.body[self.position]
	def clone(self):
		"Creates a shallow clone"
		return Item(self.production, self.position)
	def __str__(self):
		retval = str(self.production.head) + " ->"
		c = 0
		for symbol in self.production.body:
			if c == self.position:
				retval += " ~"
			c += 1
			retval += " " + str(symbol)
		if c == self.position:
			retval += " ~"
		return retval
	def isKernel(self):
		"Returns true if this is a kernel item"
		return self.position != 0 or self.production.grammar.rootProduction == self.production

#Dragon Book, Fig. 4.32
def closure(item):
	"Compute the closure of an item"
	if isinstance(item, Item):
		J = SetOfItems((item,))
		new = [item]
	else:
		J = SetOfItems()
		new = []
		for it in item:
			J.add(it)
			new += [it]
	while len(new) != 0:
		it = new.pop()
		B = it.nextSymbol()
		if B:
			for p in B.productions():
				newItem = Item(p, 0)
				if J.condAdd(newItem):
					new += [newItem]
	"""
	changed = True
	while changed:
		changed = False
		for it in J:
			B = it.nextSymbol()
			if B:
				for p in B.productions():
					newItem = Item(p, 0)
					if newItem not in J:
						J.add(newItem)
						changed = True
	"""
	return J


#Dragon Book, Section 4.6.2
def goto(items, symbol):
	"Computes the goto set of a set of items for a given symbol"
	retval = SetOfItems()
	for item in items:
		if item.nextSymbol() == symbol:
			ni = item.clone()
			ni.position += 1
			ni.rehash()
			retval.add(ni)
	return closure(retval)

#Dragon Book, Section 4.6.2
def kernelGoto(items, symbol):
	"Computes the goto set of a set of items for a given symbol"
	retval = SetOfItems()
	for item in items:
		if item.nextSymbol() == symbol:
			ni = item.clone()
			ni.position += 1
			ni.rehash()
			retval.add(ni)
	return retval

#Dragon Book, Fig. 4.33
def items(grammar):
	"Compute the canonical collections of set of LR(0) items"
	s = closure(Item(grammar.rootProduction,0))
	new = [s]
	C = (s,)
	while len(new) != 0:
		I = new.pop()
		for X in grammar.symbols:
			g = goto(I, X)
			if not g.isEmpty() and g not in C:
				C += (g,)
				new += [g]
		yield I
	"""
	C = (closure(Item(grammar.rootProduction,0)),)
	changed = True
	while changed:
		changed = False
		for I in C:
			for X in grammar.symbols:
				g = goto(I, X)
				if not g.isEmpty() and g not in C:
					C += (g,)
					changed = True
	return C"""
