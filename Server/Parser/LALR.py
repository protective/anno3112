#!/usr/bin/env python
# -*- coding: utf-8 -*-

from grammar import *
from ItemSet import *
import LA0

import os.path

class Item:
	"Representation of an item for an LALR parser"
	def __init__(self, production, position, lookahead):
		self.production = production
		self.position = position
		self.lookahead = lookahead
		self.hash = production.name ^ position ^ id(lookahead)
	def rehash(self):
		self.hash = self.production.name ^ self.position ^ id(self.lookahead)
	def __eq__(self, item):
		if item.hash != self.hash:
			return False
		return item.production == self.production and self.position == item.position and self.lookahead == item.lookahead
	def __cmp__(self, other):
		return self.hash - other.hash
	def nextSymbol(self):
		"Gets the symbol after position, or None"
		if self.position >= len(self.production.body):
			return None
		return self.production.body[self.position]
	def clone(self):
		"Creates a shallow clone"
		return Item(self.production, self.position, self.lookahead)
	def __str__(self):
		retval = "{" + str(self.production.head) + " ->"
		c = 0
		for symbol in self.production.body:
			if c == self.position:
				retval += " ~"
			c += 1
			retval += " " + str(symbol)
		if c == self.position:
			retval += " ~"
		return retval + ", " + str(self.lookahead) + "}"
	def isKernel(self):
		"Returns true if this is a kernel item"
		return self.position != 0 or self.production.grammar.rootProduction == self.production
	def toLA0(self):
		return LA0.Item(self.production, self.position)
	def isAtEnd(self):
		"Checks if we're at the end of the production"
		return self.position >= len(self.production.body)

#Dragon Book, Section 4.4.2
def first(X, working = ()): #X is a single symbol
	if X.isTerminal():
		yield X
	elif X not in working:
		working += (X,)
		for p in X.productions():
			for Y in p.body:
				if Y == X: #TODO: Fix this, a grammar that doesn't work with this might be possible
					break
				toBreak = True
				for a in first(Y, working):
					if a: yield a
					else: toBreak = False
				if toBreak:
					break
			if len(p.body) == 0:
				yield None

def firstInBody(body, working = ()): #body is a tuple of grammar symbols
	for Y in body:
		toBreak = True
		for a in first(Y, working):
			if a: yield a
			else: toBreak = False
		if toBreak:
			break
	if len(body) == 0:
		yield None

#Dragon Book, fig. 4.40
def closure(item):
	"Closure for an item"
	if isinstance(item, Item):
		I = SetOfItems((item,))
		new = [item]
	else:
		I = SetOfItems()
		new = []
		for it in item:
			I.add(it)
			new += (it,)
	while len(new) != 0:
		it = new.pop()
		B = it.nextSymbol()
		if B and not B.isTerminal():
			for b in firstInBody(it.production.body[it.position+1:] + (it.lookahead,)):
				if b:
					for p in B.productions():
						ni = Item(p, 0, b)
						if I.condAdd(ni):
							new += (ni,)
	return I
	"""
	changed = True
	while changed:
		changed = False
		for it in I:
			B = it.nextSymbol()
			if B:
				for p in B.productions():
					for b in firstInBody(it.production.body[it.position+1:] + (it.lookahead,)):
						if b:
							ni = Item(p, 0, b)
							if ni not in I:
								I.add(ni)
								changed = True
	return I"""

#Dragon Book, fig. 4.40
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

def kernelGoto(items, symbol):
	"Computes the kernels a set of items may goto"
	retval = SetOfItems()
	for item in items:
		if item.nextSymbol() == symbol:
			ni = item.clone()
			ni.position += 1
			ni.rehash()
			retval.add(ni)
	return retval

def LR1_items(grammar):
	"Compute the canonical collections of set of LR(1) items"
	s = closure(Item(grammar.rootProduction, 0, grammar.EOF))
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

uids = 0 #Unique identifier counter... I don't care that this is global, as long as it's unique...
lookout = {}
class KernelItemSet:
	"Entry for the kernel table in the KernelComputer"
	def __init__(self):
		self.items = ()
		self.propagates = []
		self.lookaheads = []
		self.ids = ()

	def addKernel(self, kernel):
		self.items += (kernel,)
		global uids
		nid = uids
		self.ids += (nid,)
		uids += 1
		global lookout
		self.propagates += [()]
		lo = []
		lookout[nid] = lo
		self.lookaheads += [lo]

	def idOf(self, kernel):
		for i in xrange(0, len(self.items)):
			if self.items[i] == kernel:
				return self.ids[i]
		raise Exception, "Kernel was not found in this KernelEntry"

	def addLookahead(self, item, lookahead):
		for i in xrange(0, len(self.items)):
			if self.items[i] == item:
				self.lookaheads[i] += (lookahead,)

	def addPropagation(self, kernel, to):
		for i in xrange(0, len(self.items)):
			if self.items[i] == kernel:
				self.propagates[i] += (to,)

	def __iter__(self):
		for item in self.items: yield item;

	def __contains(self, item):
		return item in self.items

	def match(self, items):
		if len(items) != len(self.items):
			return False
		for it in items:
			if it not in self.items:
				return False
		return True

	def generateKernels(self):
		kset = SetOfItems()
		for i in xrange(0, len(self.items)):
			for lh in self.lookaheads[i]:
				kset.condAdd(Item(self.items[i].production, self.items[i].position, lh))
		return kset

class KernelComputer:
	def __init__(self, grammar):
		self.grammar = grammar
		self.kernelTable = ()	#Tuple of kernelItemSets
		for itSet in LA0.items(self.grammar):
			t = KernelItemSet()
			for k in itSet.kernels():
				t.addKernel(k)
			self.kernelTable += (t,)
		#Add the EOF symbol as lookahead for root production
		rItem = LA0.Item(self.grammar.rootProduction, 0)
		for kset in self.kernelTable:
			if rItem in kset:
				kset.addLookahead(rItem, self.grammar.EOF)

	def computeLookaheads(self):
		D = Symbol("#", self.grammar)
		for kSet in self.kernelTable:
			#Find the items
			I = LA0.closure(kSet)
			#Dictionary of symbol and kernelEntry
			gotoTable = {}
			for kernel in kSet:
				for item in closure(Item(kernel.production, kernel.position, D)):
					a = item.nextSymbol()
					if a == None:
						continue
					if not gotoTable.has_key(a):
						SearchFor = ()
						for it in LA0.kernelGoto(I, a).kernels():
							SearchFor += (it,)
						#rSet is the KernelEntry where items == SearchFor
						rSet = None
						for entry in self.kernelTable:
							if entry.match(SearchFor):
								rSet = entry
								break
						assert rSet != None, "rSet must not be None!!"
						gotoTable[a] = rSet
					else:
						rSet = gotoTable[a]
					#rItem is the LA0 item where searching for...
					rItem = item.toLA0()
					rItem.position += 1 #Move to the other side of X
					rItem.rehash()
					if item.lookahead != D:
						rSet.addLookahead(rItem, item.lookahead)
					else:
						to = rSet.idOf(rItem)
						kSet.addPropagation(kernel, to)

	def propagateLookaheads(self):
		global lookout
		changed = True
		while changed:
			changed = False
			for entry in self.kernelTable:
				for i in xrange(0, len(entry.items)):
					for to in entry.propagates[i]:
						for lh in entry.lookaheads[i]:
							if lh not in lookout[to]:
								lookout[to] += (lh,)
								changed = True

	def generateKernels(self):
		for entry in self.kernelTable:
			yield entry.generateKernels()


class Action:
	def __eq__(self, other):
		return False
	def generateCode(self, stream):
		raise NotImplementedError, "Must be overwritten in baseclasses"
	def is_conflict(self, action):
		raise NotImplementedError, "Must be overwritten in baseclasses"
	def generateAction(self, stream):
		raise NotImplementedError, "Must be overwritten in baseclasses"

class ShiftAction(Action):
	def __init__(self, symbol, state, item):
		self.symbol = symbol
		self.state = state #State name
		self.item = item
	def __eq__(self, other):
		if not isinstance(other, ShiftAction):
			return False
		return other.state == self.state and self.symbol == other.symbol
	def generateCode(self, stream):
		stream.write("\t\tcase TOKEN_" + self.symbol.name + ": ")
		self.generateAction(stream)
	def generateAction(self, stream):
		stream.write("goto Shift" + str(self.state) + ";\n")
	def is_conflict(self, action):
		if self.symbol == action.symbol:
			return not isinstance(action, ShiftAction) or self.state != action.state
		return False

class ReduceAction(Action):
	def __init__(self, symbol, production, item):
		self.symbol = symbol
		self.production = production
		self.item = item
	def __eq__(self, other):
		if not isinstance(other, ReduceAction):
			return False
		return other.production == self.production and self.symbol == other.symbol
	def generateCode(self, stream):
		stream.write("\t\tcase TOKEN_" + self.symbol.name + ": ")
		self.generateAction(stream)
	def generateAction(self, stream):
		stream.write("goto Reduce" + str(self.production.name) + ";\n")
	def is_conflict(self, action):
		if self.symbol == action.symbol:
			return not isinstance(action, ReduceAction) or self.production != action.production
		return False

class AcceptAction(Action):
	def __init__(self, symbol, item):
		self.symbol = symbol
		self.item = item
	def __eq__(self, other):
		if not isinstance(other, AcceptAction):
			return False
		return True
	def generateCode(self, stream):
		stream.write("\t\tcase TOKEN_" + self.symbol.name + ": ")
		self.generateAction(stream)
	def generateAction(self, stream):
		stream.write("return symbols.top();\n")
	def is_conflict(self, action):
		if self.symbol == action.symbol:
			return not isinstance(action, AcceptAction)
		return False

class State:
	def __init__(self, name, kernels, isStart = False):
		self.name = name			#Unique integer
		self.items = closure(kernels)#SetOfItems
		self.kernels = kernels		#SetOfItems
		self.actions = [] 			#Tuple of Actions
		self.goto = () 				#Tuple of tuples, with nonterminal, state name
		self.isStart = isStart		#True if this is the start state
	
	def has_conflict(self, action):
		for a in self.actions:
			if a.is_conflict(action):
				return a
		return False

	def has_action(self, action):
		return action in self.actions

	def isRecoveryState(self):
		"Returns true if this state is shifted "
		if self.kernels[0].position == 0: return False
		if len(self.kernels[0].production.body) == 0: return False
		return self.kernels[0].production.body[self.kernels[0].position-1].name == "error"

	def generateCode(self, stream):
		stream.write("Shift" + str(self.name) + ":\n")
		stream.write("/*\n")
		for k in self.kernels:
			stream.write(str(k) + "\n")
		stream.write("*/\n")
		stream.write("\tsymbols.push(current_terminal);\n")
		stream.write("\tcurrent_terminal = lexer->nextToken();\n")
		if self.isStart: #If this is the start state
			stream.write("START:\n")
		stream.write("State" + str(self.name) + ":\n")
		#stream.write("\tcerr<<\"state " + str(self.name) + " \"<< TokenToString(current_terminal->token())<<endl;\n")
		stream.write("\tstates.push(&&Goto" + str(self.name) + ");\n")
		if self.isRecoveryState(): #If this is a recovery state
			stream.write("Switch" + str(self.name) + ":\n")
		stream.write("\tswitch(current_terminal->token()){\n")
		for action in self.actions:
			action.generateCode(stream)
		if self.isRecoveryState(): #Discard input if this is a recovery state
			stream.write("\t\tdefault:\n")
			stream.write("\t\t\t((ErrorTerminal*)symbols.top())->discard(current_terminal);\n")
			stream.write("\t\t\tcurrent_terminal = lexer->nextToken();\n")
			stream.write("\t\t\tgoto Switch%s;\n" % str(self.name))
		else: #Raise an error
			stream.write("\t\tdefault: goto ERROR;\n")
		stream.write("\t}\n\n")
		#Generate goto table entry
		stream.write("Goto" + str(self.name) + ":\n")
		stream.write("\tswitch(top_non_terminal){\n")
		for nt, state in self.goto:
			stream.write("\t\tcase SYMBOL_" + str(nt.name) + ": goto State" + str(state) + ";\n")
		#Handle error if we can
		stream.write("\t\tcase SYMBOL_error:\n\t\t\t")
		handleError = False
		for action in self.actions:
			if action.symbol.name == "error":
				action.generateAction(stream)
				handleError = True
				break
		if not handleError:
			stream.write("states.pop();\n")
			stream.write("\t\t\tsymbols.pop();\n")
			stream.write("\t\t\tgoto *states.top();\n")
		stream.write("\t\tdefault: goto FATAL_ERROR;\n")
		stream.write("\t}\n\n")
		
	def dump(self):
		print "State" + str(self.name) + ":"
		print "\tItems:"
		for item in self.items:
			print "\t\t" + str(item)
		print "\tKernels:"
		for item in self.kernels:
			print "\t\t" + str(item)
		print ""

class ParserBuilder:
	def __init__(self, grammar):
		self.states = () #Tuple of states
		self.grammar = grammar
		print " - LA0 kernel items"
		kc = KernelComputer(grammar)
		print " - find lookaheads"
		kc.computeLookaheads()
		print " - propagate lookaheads"
		kc.propagateLookaheads()
		print " - creating states"
		for kernels in kc.generateKernels():
			if Item(self.grammar.rootProduction, 0, self.grammar.EOF) in kernels:
				self.states += (State(len(self.states), kernels, True),)
			else:
				self.states += (State(len(self.states), kernels),)
		#Create state name table:
		self.nameMap = {}
		for state in self.states:
			self.nameMap[self.getStateCoreUniqueSet(state.kernels)] = state
				
	def getStateCoreUniqueSet(self, items):
		stateSet = ()
		for item in items:
			stateSet += ((item.production.name, item.position),)
		return frozenset(stateSet)
 
	def dumpStates(self):
		print "Dumping states: "
		for state in self.states:
			state.dump()

	def getStateName(self, items):
		return self.nameMap[self.getStateCoreUniqueSet(items.kernels())].name

	def createActions(self, log):
		hadConflicts = False
		eof = self.grammar.EOF
		finish = Item(self.grammar.rootProduction, 1, eof)
		for state in self.states:
			gotoStateNames = {}
			for item in state.items:
				#Shift action
				a = item.nextSymbol()
				if a != None and a.isTerminal():
					if not gotoStateNames.has_key(a):
						J = kernelGoto(state.items, a)
						Jindex = self.getStateName(J)
						gotoStateNames[a] = Jindex
					else:
						Jindex = gotoStateNames[a]
					action = ShiftAction(a, Jindex, item)
					if self.assignAction(state, action, log):
						hadConflicts = True
				#Reduce action
				if item.isAtEnd() and not item.production.defines(self.grammar.root):
					a = item.lookahead
					action = ReduceAction(a, item.production, item)
					if self.assignAction(state, action, log):
						hadConflicts = True
				#Accept action
				if finish == item:
					action = AcceptAction(eof, item)
					conflict = state.has_conflict(action)
					if conflict:
						print "Shift-Accept or Reduce-Accept conflict, grammar not in LALR(1) !"
						#TODO: Print hints
						#TODO: Resolve conflict by default resolution rules
					elif not state.has_action(action):
							state.actions += (action,)
		return hadConflicts

	def assignAction(self, state, action, log):
		"Assigns an action and handles conflicts"
		#Find anything that conflicts
		conflict = state.has_conflict(action)
		#If no conflict, just add the action
		if not conflict:
			if not state.has_action(action):
				state.actions += (action,)
		else:
			if action.item.production.name < conflict.item.production.name or (action.item.production.name == conflict.item.production.name and isinstance(action, ReduceAction)):
				state.actions.remove(conflict) #Discard the old action
				state.actions += (action,)
				alternative = conflict
				choice = action
			else: #Discard the new action
				alternative = action
				choice = conflict
			log.write("Conflict:\n")
			log.write("         " + str(alternative.item) + "\n")
			log.write("Choose:  " + str(choice.item) + "\n")
			return True
		return False

	def createGotoTable(self):
		for state in self.states:
			for nt in self.grammar.nonterminals():
				J = kernelGoto(state.items, nt)
				if not J.isEmpty():
					j = self.getStateName(J)
					state.goto += ((nt, j),)

	def generateHeader(self, stream):
		stream.write("""#ifndef PARSER_H
#define PARSER_H
#include "../../../SFunctions.h"
class Lexer;
class SOrderNode;

SOrderNode* parse(Lexer* lex);

""")
		stream.write("enum Token{\n")
		tokens = "\tTOKEN_error,\n"
		for symbol in self.grammar.symbols:
			if symbol.isTerminal() and symbol.name != "error":
				tokens += "\tTOKEN_" + symbol.name + ",\n"
		stream.write(tokens[:-2] + "\n};\n")

		stream.write("""

string TokenToString(Token token);

#endif /* PARSER_H */
""")

	def generateCode(self, stream, header):
		stream.write("#include <stack>\n#include \"%s\"\nusing namespace std;\n\n" % os.path.basename(header))
		#Define the internally used Symbol enum
		stream.write("/* Enumeration for all non-terminals */\nenum Symbol{\n")
		symbols = "\tSYMBOL_error,\n"
		for symbol in self.grammar.symbols:
			if not symbol.isTerminal():
				symbols += "\tSYMBOL_" + symbol.name + ",\n"
		stream.write(symbols[:-2] + "\n};\n")
		stream.write("""

/* The following auto generated code expects the function lexer->nextToken() to return a Terminal
 * object pointer (e.g. Terminal*). The terminal object is assumed to have a token() method
 * returning a Token (the enum defined in the header file). The Terminal class must also
 * derivate from a class called Node, which must also be defined.
 * 
 * At last but not least a subclass of Terminal called ErrorTerminal must exist. This class
 * must have a constructor that takes a Terminal pointer as single argument. It must also
 * have a method called discard(Terminal* terminal), which will be called whenever a terminal
 * following an error is discarded.
 */

/** Function for parsing input read from lexer->nextToken() */
SOrderNode* parse(Lexer* lexer){
	stack<SOrderNode*> symbols = stack<SOrderNode*>();
	stack<void*> states = stack<void*>();
	Symbol top_non_terminal;
	SOrderTerminal* current_terminal = lexer->nextToken();
""")
		#Allocate memory for arguments and result;
		stream.write("\tSOrderNode* result")
		args = ()
		for production in self.grammar.productions:
			for arg in production.action.args:
				if arg not in args: args += (arg,)
		for arg in args:
			stream.write(", *" + arg)
		#Start
		stream.write(";\n\tgoto START;\n")
		stream.write("\t/*** States ****/\n")
		#Generate code for states
		for state in self.states:
			state.generateCode(stream)
		stream.write("\t/*** Reductions ****/\n")
		#Generate code for reductions
		for production in self.grammar.productions:
			stream.write("Reduce" + str(production.name) + ": //%s\n" % str(production))
			for arg in ("arg%i" % i for i in xrange(len(production.body)-1, -1, -1)):
				if arg in production.action.args:
					stream.write("\t%s = symbols.top();\n" % arg)
				else:
					stream.write("\tdelete symbols.top();\n")
				stream.write("\tsymbols.pop();\n")
				stream.write("\tstates.pop();\n")
			stream.write("\tresult = NULL;\n")
			stream.write("\t{\n\t" + production.action.code.replace("\n", "\n\t") + "\n\t}\n")
			stream.write("\tsymbols.push(result);\n")
			stream.write("\ttop_non_terminal = SYMBOL_" + production.head.name + ";\n")
			stream.write("\tgoto *states.top();\n\n")
		#Error handling
		stream.write("""
ERROR:
	current_terminal = new SOrderErrorTerminal(current_terminal);
	top_non_terminal = SYMBOL_error;
	goto *states.top();
FATAL_ERROR:
	fprintf(stderr, "Fatal error occured, this shouldn't be possible!");
	exit(9);
""")
		stream.write("}\n") #End of parse function
		stream.write("""\nstring TokenToString(Token token){
	switch(token){\n""")
		for symbol in self.grammar.symbols:
			if symbol.isTerminal():
				stream.write("\t\tcase TOKEN_" + str(symbol.name) + ": return \"" + str(symbol.name) + "\";\n")
		stream.write("\t\tdefault: return \"Unknown token\";\n\t}\n}\n")
		

	def dumpCSV(self, stream):
		#Find terminals and nonterminals
		nonterminals = ()
		terminals = ()
		for symbol in self.grammar.symbols:
			if symbol.isTerminal():
				terminals += (symbol,)
			else:
				nonterminals += (symbol,)
		#Write header
		stream.write("\"STATE\", \"Actions\"" + ","*len(terminals) + " \"GOTO\"" + ","*(len(nonterminals)-1) + "\r\n")
		for terminal in terminals:
			stream.write(",\"" + terminal.name + "\"")
		for nt in nonterminals:
			stream.write(",\"" + nt.name + "\"")
		stream.write("\r\n")
		#Write the states:
		for state in self.states:
			stream.write("\"" + str(state.name) + "\"")
			for terminal in terminals:
				ac = None
				for action in state.actions:
					if action.symbol == terminal:
						ac = action
				if ac: #We have an action
					if isinstance(ac, ShiftAction):
						stream.write(",\"Shift" + str(ac.state) + "\"")
					elif isinstance(ac, ReduceAction):
						stream.write(",\"Reduce" + str(ac.production.name) + "\"")
					elif isinstance(ac, AcceptAction):
						stream.write(",\"Accept\"")
				else:
					stream.write(",") #Error entry
			for nt in nonterminals:
				gs = None
				for n, s in state.goto:
					if n == nt:
						gs = s
				if gs:
					stream.write(",\"" + str(gs) + "\"")
				else:
					stream.write(",")
			stream.write("\r\n")
		stream.write("\"Productions:\"" + ","* (len(terminals) + len(nonterminals)) + "\r\n")
		for production in self.grammar.productions:
			stream.write("\"" + str(production.name)+ "\",\"" + str(production) + "\"" + ","* (len(terminals) + len(nonterminals)-1) + "\r\n")

"""
	TODO:
 + Introduce error in enums
 + Make default entry in action table an error action
 + Update goto tables to handle errors or propagate them
 + Identify and add symbol discardment for shift error states
 - Produce errors when error is non-terminal or root is used a terminal or non-terminal in grammar
 - Always add error terminal to the grammar

Ambiguity:
 - Reduce/Reduce, choose production mention first
 - Shift/Reduce
    - If conflict  is A->a.  B->a.a, choose B if it has higher percedencen
    - Resolved in favor of shifting by default
 + Annotate production with precedence
 - Annotate production with associativity of terminals, defaults to left, unless -R is specified



"""



