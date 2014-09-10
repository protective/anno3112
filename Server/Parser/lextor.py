#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import subprocess
"""
Rapex is generator for efficient lexical analysers in C.

Structure:

 - Read input
 - Parse regular expressions to syntax trees
	 - For all regular expressions
		 - Agument the regex
		 - Parse it to a tree of nodes
		 - Add metadata to the agumented node
	- Join all toplevel expressions using union nodes
- Generate DFA
	- Assign positions to the char nodes
	- Compute followpos
	- Build transition table using a dictionary of states
- Replace transistions to agumented states with acceptance
- Generate code recursively
"""

class Reader:
	def __init__(self, inputFile):
		self.inputFile = inputFile
		self.peek = ""
		self.current = self.peek
		self.line = ""
		self.ReadChar()
	
	def ReadChar(self):
		self.current = self.peek
		self.peek = self.inputFile.read(1)
		self.line += self.current
		if(self.current == '\n'):
			self.line = ""
		
	def nextLine(self):
		while(self.current != '\n'):
			self.ReadChar()

def build(optimize = True):
	
	inputFile = open(inputfile, 'r')
	outputFile = open(outputfile, 'w')
	
	reader = Reader(inputFile)

	parsing = False
	nowParsing = ''
	nowReading = ''
	regex = ''
	action =''
	slashcount = 0
	bcount = 0
	errorParsingRules = 0
	errorfoundLX = 0
	gKey = ''
	gValue = ''

	reader.ReadChar()	
	while(len(reader.current) != 0):
		if(not parsing):
			if(reader.line.startswith('/*** LX ***')):
				parsing = True
				errorfoundLX = 1
			elif(reader.line.startswith('*** LX ***/')):
				sys.stderr.write("Found end LX without begin LX\n")
				sys.exit()
			elif(reader.peek == '\n'):
				outputFile.write(reader.line + '\n')
		elif(parsing):
			if(reader.line.startswith('/*** LX ***')):
				sys.stderr.write("Found begin LX without end LX\n")
				sys.exit()
			elif(reader.line.startswith('*** LX ***/')):
				nowParsing = ''
				if (len(r.actions) <= 0):
					sys.stderr.write("No regular expressions found\n")
					sys.exit()
				r.buildDFA()
				if optimize:
					r.minimizeDFA()
				r.generateCode(outputFile)
				parsing = False
				if (nowReading == 'action'):
					sys.stderr.write("regex action mismatch\n")
					sys.exit()
			elif(reader.line.startswith('rules:')):
				if (bcount != 0):
					sys.stderr.write("curly brackets mismatch\n")
					sys.exit()	
				if (nowReading == 'regex'):#Do not get this one
					sys.stderr.write("regex action mismatch\n")
					sys.exit()
				nowParsing = 'rules'
				nowReading = ''
				errorParsingRules = 1
				bcount = 0
			elif(reader.line.startswith('groups:')):
				if (errorParsingRules == 1):
					sys.stderr.write("Reading groups after rules\n")
					sys.exit()
				if (nowReading == 'regex'):
					sys.stderr.write("regex action mismatch\n")
					sys.exit()
				if (bcount != 0):
					sys.stderr.write("curly brackets mismatch\n")
					sys.exit()
				nowParsing = 'groups'
				nowReading = ''

			elif(reader.line.startswith('error:')):
				if (bcount != 0):
					sys.stderr.write("curly brackets mismatch\n")
					sys.exit()
				nowParsing = 'error'
				nowReading = ''
			elif(reader.line.startswith('accept:')):
				if (bcount != 0):
					sys.stderr.write("curly brackets mismatch\n")
					sys.exit()
				nowParsing = 'accept'
				nowReading = ''

			if(reader.current == '/' and slashcount == 1): #handles // as comment
				slashcount = 0
				reader.nextLine()
			elif(reader.current == '/'):
				slashcount+=1	
			elif(reader.current != '/'):
				slashcount = 0

			if(nowParsing == 'groups'):

			
				if(reader.current == ']'):
					gKey += ']'
					nowReading = ''	
				elif(reader.current == '}'):
					nowReading = ''
					r.groups[gKey] = gValue
					gKey = ''
					gValue = ''
				elif(reader.current == '['):
					gKey += '['
					nowReading = 'group'
				elif(reader.current == '{'):
					nowReading = 'subsitution'						
				elif(nowReading == 'group'):
					gKey += reader.current
				elif(nowReading == 'subsitution'):
					gValue += reader.current
			

			elif(nowParsing == 'error'):
				if(reader.current =='{'):
					if(bcount == 0):
						 action = ''
					bcount +=1
				elif(reader.current == '\\'):
					if(reader.peek in ('{', '}')):
						temp = reader.peek
						reader.ReadChar()
						action += temp
							
					else:
						action += "\\"
				elif(reader.current == '}'):
					bcount -=1
					if (bcount == 0):
						r.defaultAction = action
					elif (bcount < 0):
						sys.stderr.write("curly brackets mismatch\n")
						sys.exit()
				else:
					action += reader.current		


			elif(nowParsing == 'accept'):
				if(reader.current =='{'):
					if(bcount == 0):
						 action = ''
					bcount +=1
				elif(reader.current == '\\'):
					if(reader.peek in ('{', '}')):
						temp = reader.peek
						reader.ReadChar()
						action += temp
							
					else:
						action += "\\"
				elif(reader.current == '}'):
					bcount -=1
					if (bcount == 0):
						r.alwaysAcceptCode = action
					elif (bcount < 0):
						sys.stderr.write("curly brackets mismatch\n")
						sys.exit()
				else:
					action += reader.current		


			elif(nowParsing == 'rules'):

				if(reader.current == '}' and nowReading == 'regex'):
					bcount -=1
					if (bcount == 0):
						nowReading = 'action'
					elif (bcount < 0):
						sys.stderr.write("curly brackets mismatch\n")
						sys.exit()
				elif(reader.current == '}' and nowReading == 'action'):
					bcount -=1
					if (bcount < 0):
						sys.stderr.write("curly brackets mismatch\n")
						sys.exit()	
					elif (bcount == 0):
						for group, subs in r.groups.iteritems():
							regex = regex.replace(group, '(' + subs + ')');
						r.addRule(regex, action)
						nowReading = 'regex'
				elif((reader.current =='{' and nowReading == 'regex') or (reader.current =='{' and nowReading == '')):
					if(bcount == 0):
						nowReading = 'regex'
						regex = ''
					bcount +=1
				elif(reader.current =='{' and nowReading == 'action'):
					if(bcount == 0):
						 action = ''
					bcount +=1
				elif(reader.current == '\\'):
					if(reader.peek in ('{', '}')):
						temp = reader.peek
						reader.ReadChar()
						if(nowReading == 'regex'):
							regex += temp
					else:
						regex += "\\"
				elif(nowReading == 'regex'):
					regex += reader.current
				elif(nowReading == 'action'):
					action += reader.current
		#Read char in end of while loop
		reader.ReadChar()
	
	if (errorfoundLX == 0):
		sys.stderr.write("No begin LX found\n")
		sys.exit()
	inputFile.close()
	outputFile.close()
	
class PositionSet:
	"""A hashable set of integers"""
	data = 0
	def __init__(self, *positions):
		for p in positions:
			self.data |= 1<<p
	def union(self, positions):
		"""Union with an other PositionSet"""
		if not isinstance(positions, PositionSet):
			raise Exception("positions must be a PositionSet")
		retval = PositionSet()
		retval.data = self.data | positions.data
		return retval
	def intersect(self, positions):
		"""Intersect with an other PositionSet"""
		if not isinstance(positions, PositionSet):
			raise Exception("positions must be a PositionSet")
		retval = PositionSet()
		retval.data = self.data & positions.data
		return retval
	def add(self, *positions):
		"""Add positions to this state"""
		for p in positions:
			if isinstance(p, PositionSet):
				self.data |= p.data
			else:
				self.data |= 1<<p
	def positions(self):
		"""Returns the positions in this position set"""
		d = self.data
		pos = 0
		while d != 0:
			if d & 1:
				yield pos
			d >>= 1
			pos += 1
	def __hash__(self):
		return self.data
	def __eq__(self, other):
		if not isinstance(other, PositionSet): return False
		return self.data == other.data
	def __cmp__(self, other):
		return self.data.__cmp__(other.data)
	def isEmpty(self):
		return self.data == 0

class Node:
	"""Abstact base class for all nodes in the syntax tree for a regular expression"""
	def __init__(self):
		raise NotImplementedError("Node is an abstract class")
	def nullable(self):
		raise NotImplementedError("nullable must be overwritten in base class")
	def firstpos(self):
		raise NotImplementedError("firstpos must be overwritten in base class")
	def lastpos(self):
		raise NotImplementedError("lastpos must be overwritten in base class")
	def computeFollowPos(self, leafs):
		raise NotImplementedError("computeFollowPos must be overwritten in base class")
	def dumptree(self, depth = 0):
		raise NotImplementedError("dumptree must be overwritten in base class")

class Leaf(Node):
	"""A leaf node with a character"""
	char = None
	pos = None
	followpos = None
	def __init__(self, char, position):
		self.char = char
		self.pos = position
		self.followpos = PositionSet()
	def nullable(self):
		return False
	def firstpos(self):
		if self.pos == None:
			raise Exception("Leaf was not assigned a position!")
		return PositionSet(self.pos)
	def lastpos(self):
		return self.firstpos()
	def match(self, char):
		return self.char == char
	def computeFollowPos(self, leafs):
		pass
	def dumptree(self, depth = 0):
		print "\t"*depth + self.char + " : " + str(self.pos)

class UnionNode(Node):
	"""Union of two regular expressions used in a syntax tree"""
	left = None
	right = None
	followpos = None
	def __init__(self, left, right):
		if not isinstance(left, Node): raise Exception("left must be a Node")
		if not isinstance(right, Node): raise Exception("right must be a Node")
		self.left = left
		self.right = right
	def nullable(self):
		return self.left.nullable() or self.right.nullable()
	def firstpos(self):
		return self.left.firstpos().union(self.right.firstpos())
	def lastpos(self):
		return self.left.lastpos().union(self.right.lastpos())
	def computeFollowPos(self, leafs):
		self.left.computeFollowPos(leafs)
		self.right.computeFollowPos(leafs)
	def dumptree(self, depth = 0):
		print "\t"*depth + "| : " + str([i for i in self.firstpos().positions()]) + ", " + str([i for i in self.lastpos().positions()]) #+ ", " + str([i for i in self.followpos.positions()])
		self.left.dumptree(depth+1)
		self.right.dumptree(depth+1)

class ConcatNode(Node):
	left = None
	right = None
	followpos = PositionSet()
	def __init__(self, left, right):
		if not isinstance(left, Node): raise Exception("left must be a Node")
		if not isinstance(right, Node): raise Exception("right must be a Node")
		self.left = left
		self.right = right
	def nullable(self):
		return self.left.nullable() and self.right.nullable()
	def firstpos(self):
		if self.left.nullable():
			return self.left.firstpos().union(self.right.firstpos())
		return self.left.firstpos()
	def lastpos(self):
		if self.right.nullable():
			return self.left.lastpos().union(self.right.lastpos())
		return self.right.lastpos()
	def computeFollowPos(self, leafs):
		fp = self.right.firstpos()
		for leaf in (leafs[i] for i in self.left.lastpos().positions()):
			leaf.followpos.add(fp)
		self.left.computeFollowPos(leafs)
		self.right.computeFollowPos(leafs)
	def dumptree(self, depth = 0):
		print "\t"*depth + "& : " + str([i for i in self.firstpos().positions()]) + ", " + str([i for i in self.lastpos().positions()]) #+ ", " + str([i for i in self.followpos.positions()])
		self.left.dumptree(depth+1)
		self.right.dumptree(depth+1)

class KleeneNode(Node):
	child = None
	def __init__(self, child):
		if not isinstance(child, Node): raise Exception("child must be a Node")
		self.child = child
	def nullable(self):
		return True
	def firstpos(self):
		return self.child.firstpos()
	def lastpos(self):
		return self.child.lastpos()
	def computeFollowPos(self, leafs):
		fp = self.firstpos()
		for leaf in (leafs[i] for i in self.lastpos().positions()):
			leaf.followpos.add(fp)
		self.child.computeFollowPos(leafs)
	def dumptree(self, depth = 0):
		print "\t"*depth + "* : " + str([i for i in self.firstpos().positions()]) + ", " + str([i for i in self.lastpos().positions()])# + ", " + str([i for i in self.followpos.positions()])
		self.child.dumptree(depth+1)

class EmptyNode(Node):
	pos = None
	followpos = None
	def __init__(self, position):
		self.pos = position
		self.followpos = PositionSet()
	def nullable(self):
		return True
	def firstpos(self):
		return PositionSet()
	def lastpos(self):
		return PositionSet()
	def computeFollowPos(self, leafs):
		pass
	def dumptree(self, depth = 0):
		print "\t"*depth + "e : " + str([i for i in self.firstpos().positions()]) + ", " + str([i for i in self.lastpos().positions()])# + ", " + str([i for i in self.followpos.positions()])

class AcceptNode(Node):
	pos = None
	rule = None
	followpos = None
	def __init__(self, rule, position):
		self.pos = position
		self.rule = rule
		self.followpos = PositionSet()
	def nullable(self):
		return False
	def firstpos(self):
		if self.pos == None:
			raise Exception("Accept node was not assigned a position!")
		return PositionSet(self.pos)
	def lastpos(self):
		return self.firstpos()
	def match(self, char):
		return False
	def computeFollowPos(self, leafs):
		pass
	def dumptree(self, depth = 0):
		print "\t"*depth + "# : " + str(self.pos) + ", returns " + str(self.rule)

class InputStream:
	data = ""
	offset = 0
	def __init__(self, data):
		self.offset = 0
		self.data = data
	def peek(self):
		if len(self.data) <= self.offset:
			return None
		return self.data[self.offset]
	def readchar(self):
		if len(self.data) <= self.offset:
			return None
		retval = self.data[self.offset]
		self.offset += 1
		return retval

class State:
	transitions = None
	idset = None
	rule = None
	name = None
	group = None
	def __init__(self, idset, name, rule = None):
		self.idset = idset
		self.rule = rule
		self.name = name
		self.transitions = {}
	def setRule(self, rule):
		self.rule = rule
	def addTransition(self, char, state):
		"""Add a transition, the state argument should be a state name, e.g. integer"""
		self.transitions[char] = state
		
	def isAccepting(self):
		return self.rule != None
	def generateCode(self, stream):
		stream.write("State%i:\n\tcursor++;\n" % self.name)
		stream.write("\tif(limit == cursor) fill();\n")
		if self.isAccepting():
			stream.write("\taccept = %i;\n" % self.rule)
			stream.write("\tmarker = cursor;\n")
		if self.name == 0: #This is the start state
			stream.write("START: \n")
		stream.write("\tswitch(*cursor){\n")
		for char, state in self.transitions.items():
			if ord(char) >= 32  and ord(char) <= 127:
				stream.write("\t\tcase %i: goto State%i;\t//'%s'\n" % (ord(char), state.name, char))
			else:
				stream.write("\t\tcase %i: goto State%i;\n" % (ord(char), state.name))
		stream.write("\t\tdefault: goto final;\n\t};\n\n")
	
#TODO: Support for '+', '?', '^' and '$' operators

class Rapex:
	def __init__(self):
		self.acceptPositions = PositionSet()
		self.leafs = ()
		self.states = {}
		self.unmarked = []
		self.stateNames = {}
		self.actions = ()
		self.groups = {}
		self.defaultAction = "some c blabla"
	leafs = None
	acceptPositions = None
	tree = None
	#The order in which rules are added should decide the precedence
	def addRule(self, regex, rule):
		#Parse the input
		t = self._parse(InputStream(regex))
		#Concat with an accept node
		a = AcceptNode(len(self.actions), len(self.leafs))
		self.actions += (rule,)
		self.leafs += (a,)
		self.acceptPositions.add(a.pos)
		t = ConcatNode(t, a)
		#Union it with the rest of the tree
		if self.tree == None: self.tree = t
		else:
			self.tree = UnionNode(self.tree, t)

	def getState(self,name):
		for s in self.states.itervalues():
			if s.name == name:
				return s

	def _parse(self, stream):
		t = None
		c = stream.readchar()
		while c != None:
			if c == chr(92):
				c = stream.readchar()
				l = None
				if c == 'x':
					c = stream.readchar()
					c += stream.readchar()
					c = chr(int(c, 16)) #Allow char to be written as \x04 for EOF, for instance
				elif c == 'n':
					c = '\n'
				elif c == 'r':
					c = '\r'
				elif c == 't':
					c = '\t'
				elif c == 'e':
					l = EmptyNode(len(self.leafs))
				if not l:
					l = Leaf(c, len(self.leafs))
					self.leafs += (l,)				
			elif c == '(':
				l = self._parse(stream)
			elif c == ')':
				return t
			elif c == '|':
				return UnionNode(t, self._parse(stream))
				
			else:

				l = Leaf(c, len(self.leafs))
				self.leafs += (l,)
			if stream.peek() == '*':
				stream.readchar()
				l = KleeneNode(l)
			elif stream.peek()== '?':
				stream.readchar()
				l = UnionNode(l,EmptyNode(len(self.leafs)))


			elif stream.peek()== '+':
				stream.readchar()
				l = ConcatNode(KleeneNode(l),l)


			if t == None: t = l
			else: t = ConcatNode(t, l)
			c = stream.readchar()
		return t
	states = {} #Mapping PositionSets to states
	unmarked = [] #Unmarked states, during generation
	stateNames = {} #Mapping from state PositionSet to integer state name
	def buildDFA(self):
		print " - building DFA"
		self._computeFollowPos()
		self._createState(self.tree.firstpos())
		while len(self.unmarked) > 0:
			state = self.unmarked.pop()
			for symbol in (chr(c) for c in xrange(0, 256)):
				U = PositionSet()
				for node in (self.leafs[p] for p in state.idset.positions()):
					if node.match(symbol):
						U.add(node.followpos)
				if not U.isEmpty():
					if U not in self.states.keys():
						self._createState(U)
					state.addTransition(symbol, self.states[U])
	def _createState(self, idset):
		rule = None
		a = self.acceptPositions.intersect(idset)
		for p in a.positions():
			if not isinstance(self.leafs[p], AcceptNode):
				raise Exception("AcceptNode was expected!")
			rule = self.leafs[p].rule
			break #Just, need the first rule
		name = len(self.stateNames)
		state = State(idset, name, rule)
		self.states[idset] = state
		self.unmarked += [state,]
		self.stateNames[idset] = name
		return state
	def _computeFollowPos(self):
		self.tree.computeFollowPos(self.leafs)
	def minimizeDFA(self):
		print " - minimising DFA"
		sortedGroups = {}
		
		for state in self.states.values():
			rule = 0
			if(state.isAccepting()):
				rule = state.rule
			else:
				rule = -1 	#Not an accepting state
				
			if(sortedGroups.has_key(rule) == False):
				sortedGroups[rule] = []
			sortedGroups[rule] += [state, ]
			state.group = sortedGroups[rule]
		
		groups = []
		for l in sortedGroups.values():
			if len(l) > 1: #Only add groups with more than one element
				groups.append(l)
		groupCounter = 0

		#Find states that can be removed, by finding those that cannot be combined
		while(len(groups) > 0):
			group = groups.pop()
			newGroup = []
			groupCounter += 1
			for t in (chr(c) for c in xrange(0,255)):
				firstGroup = None
				for state in group:
					if (state.transitions.has_key(t)):
						
						if (firstGroup == None):
							firstGroup = state.transitions[t].group
						elif (firstGroup != state.transitions[t].group):
							newGroup += [state, ]
					else:
						if (firstGroup == None):
							firstGroup = -2
						elif(firstGroup != None and firstGroup != -2):
							newGroup += [state, ]
				if(len(newGroup) > 0):
					break
						
			#Remove the states from newGroup in group
			for s in newGroup:
				s.group = newGroup
				if(s in group):
					group.remove(s)
					
			#Reset if new group has been made
			if(len(newGroup) > 0):
				groupCounter = 0
			
			#Add the two groups if they contain more that one state
			if(len(newGroup) > 1):
				groups.insert(0,newGroup)
			if(len(group) > 1):
				groups.insert(0,group)
			
			#Merge states to one state if no split has been made
			if(groupCounter >= len(groups)):
				for state in self.states.values():
					for k, v in state.transitions.iteritems():
						if(v in group):
							if state in group:
								group[0].transitions[k] = group[0]
							else:
								state.transitions[k] = group[0]	

				#Remove all but the first element in group
				while(len(group) > 1):
					del self.states[group.pop().idset]

	def generateCode(self, stream):
		stream.write("""\t{\n\tbufstart = marker;\n\tint accept = -1;
	goto START;
final:
	if(accept == -1)
		marker++;
	cursor = marker;
	{
		%s
	}
	switch(accept){\n""" % self.alwaysAcceptCode)
		for i in range(0, len(self.actions)):
			stream.write("\tcase " + str(i) + ":\n\t\t{\n\t\t" + str(self.actions[i]) + "\n\t\t}\n\t\tbreak;\n")
		stream.write("\tdefault:\n\t\t{\n\t\t" + self.defaultAction + "\n\t\t}\n\t\tbreak;\n")
		stream.write("\t}\n\tbufstart = marker;\n\tgoto START;\n")
		for state in self.states.values():
			state.generateCode(stream)
		stream.write("\t}\n")
		
	def draw(self):
		dfaStream = ""
		dfaStream += """
digraph finite_state_machine {
	rankdir=LR;
	size="8,5"
	{rank = same; S0;}
	node [shape=plaintext];
	"" -> S0
	node [shape = doublecircle];"""
		for s in self.states.values():
			if s.isAccepting():
				dfaStream += " S" + str(s.name)
		dfaStream += ";\n"
		dfaStream += "node [shape = circle];\n"
		for s in self.states.values():
			for c,r in s.transitions.items():
				if(ord(c) > 34 and ord(c) <= 125 and ord(c) != 37):
					dfaStream += "S" + str(s.name) + " -> S" + str(r.name) + " [ label = \"" + str(c) + "\" ];\n"
				else:
					dfaStream += "S" + str(s.name) + " -> S" + str(r.name) + " [ label = \"" + str(hex(ord(c))) + "\" ];\n"
		dfaStream += "}"
		#Write dfa to file
		dfawrite = open(dfafile, "w")
		proc = subprocess.Popen("dot " + dfaType, stdin=subprocess.PIPE, shell=True, stdout=dfawrite)
		proc.communicate(input=dfaStream)[0]

if __name__ == "__main__":
	r = Rapex()
	#Read command line arguments
	inputfile = None
	outputfile = None
	dfafile = ""
	minimize = False
	for i in range(0,len(sys.argv)):
		if(sys.argv[i] == "-i"):
			inputfile = sys.argv[i+1]
		elif(sys.argv[i] == "-o"):
			outputfile = sys.argv[i+1]
		elif(sys.argv[i] == "--minimize"):
			minimize = True
		elif(sys.argv[i] == "--dfa"):
			dfafile = sys.argv[i+1]		
			#Determine type of picture file for the dfa. Used to create file
			dfaType = "-T" + dfafile[dfafile.rfind(".")+1:]
	if inputfile and outputfile:
		build(minimize)
	else:
		print >> sys.stderr, "Usage: %s -i INPUT -o OUTPUT [--dfa FILE] [--minimize]" % sys.argv[0]
		exit(1)

	#Write dfa to file
	if(len(dfafile) > 0):
		r.draw()

	print " - lexer finished"
