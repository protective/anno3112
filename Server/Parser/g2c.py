#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
from LALR import *

class GrammarParser:
	def __init__(self, inputfile, outputFile, csv = None, log = None):
		#Setup the stream and initialise the peek value
		self.file = open(inputfile, "r")
		self.outputFile = outputFile
		self.header = open(outputFile + ".h", "w")
		self.output = open(outputFile + ".cpp", "w")
		self.peek = None
		self.ReadChar()
		self.csv = csv
		self.log = log
		self.symbols = {}

		#Parse the file
		self.Parse()

		#Close the streams
		self.file.close()
		self.header.close()
		self.output.close()

	def GenerateCode(self):
		#print "Grammer parsed: "
		#print str(self.grammar) + "\n"
		print "Building LALR(1) kernel items:"
		pb = ParserBuilder(self.grammar)
		print "Building parsing table:"
		if self.log:
			logfile = open(self.log, "w")
			if pb.createActions(logfile):
				print " - Had conflicts, see: " + self.log
			logfile.close()
		else:
			pb.createActions(sys.stdout)
		print " - goto table"
		pb.createGotoTable()
		print "Writing parser code:"
		print " - generating header"
		pb.generateHeader(self.header)
		print " - generating code"
		pb.generateCode(self.output, self.outputFile + ".h")
		if self.csv != None:
			print "Generate CSV..."
			csv = open(self.csv, "w")
			pb.dumpCSV(csv)
			csv.close()

	def Parse(self):
		"""Parses file. Assumes current and peek are already valid values."""
		state = "start"
		currentHead = ""
		currentProduction = None
		currentString = ""
		bCount = 0					#Bracket counter
		self.ReadChar()

		while len(self.current) != 0:
			if state == "start":
				currentString += self.current
				if not currentString.startswith("/*** Grammar ***"[:len(currentString)]):
					self.output.write(currentString)
					currentString = ""
				elif currentString == "/*** Grammar ***":
					self.output.write("//Generated code:\n")
					state = "root"
					currentString = ""
			elif state == "root":
				if self.isSpace():
					pass
				elif self.current == "-" and self.peek == ">":
					state = "body"
					self.symbols[currentString] = Symbol(currentString, None)
					self.grammar = Grammar(self.symbols[currentString])
					currentProduction = Production(self.symbols[currentString], (), self.grammar)
					self.grammar.productions += (currentProduction,)
					self.ReadChar()
					currentString = ""
				elif len(currentString) == 0 and self.current == "#":
					while self.peek != "\n":
						self.ReadChar()
				else:
					currentString += self.current
			elif state == "head":
				if self.isSpace():
					pass
				elif self.current == "-" and self.peek == ">":
					state = "body"
					if not self.symbols.has_key(currentString):
						self.symbols[currentString] = Symbol(currentString, self.grammar)
						self.grammar.symbols += (self.symbols[currentString],)
					currentProduction = Production(self.symbols[currentString], (), self.grammar)
					self.grammar.productions += (currentProduction,)
					self.ReadChar()
					currentString = ""
				elif len(currentString) == 0 and self.current == "#":
					while self.peek != "\n":
						self.ReadChar()
				elif len(currentString) == 0 and self.current == "|":
					currentProduction = Production(currentProduction.head, (), self.grammar)
					self.grammar.productions += (currentProduction,)
					state = "body"
				elif len(currentString) == 0 and self.current == "*" and self.peek == "/":
					self.ReadChar()
					self.GenerateCode()
					state = "end"
				else:
					currentString += self.current
			elif state == "body":
				if self.isSpace() and len(currentString) != 0:
					if not self.symbols.has_key(currentString):
						self.symbols[currentString] = Symbol(currentString, self.grammar)
						self.grammar.symbols += (self.symbols[currentString],)
					currentProduction.body += (self.symbols[currentString],)
					currentString = ""
				elif self.isSpace():
					pass
				elif self.current == "{":
					if len(currentString) != 0:
						if not self.symbols.has_key(currentString):
							self.symbols[currentString] = Symbol(currentString, self.grammar)
							self.grammar.symbols += (self.symbols[currentString],)
						currentProduction.body += (self.symbols[currentString],)
					state = "action"
					bCount = 0
					currentString = ""
				else:
					currentString += self.current
			elif state == "action":
				if self.current == "}":
					bCount -= 1
					if bCount < 0:
						currentProduction.action = ActionCode(currentString)
						currentString = ""
						state = "head"
						self.ReadChar()
						continue
				elif self.current == "{":
					bCount += 1
				currentString += self.current
			elif state == "end":
				self.output.write(self.current)
			else:
				pass
			self.ReadChar()
				
 	def isSpace(self):
		return self.current in (" ", "\t", "\r", "\n")
		
	def ReadChar(self):
		self.current = self.peek
		self.peek = self.file.read(1)

	def test(self):
		print self.grammar
		print "Symbols:"
		for sym in self.grammar.symbols:
			print sym

if __name__ == "__main__":
	inputfile = None
	output = None
	csv = None
	log = None
	i = 1
	while i < len(sys.argv):
		if sys.argv[i] == "-o":
			output = sys.argv[i+1]
			i += 1
		elif sys.argv[i] == "--log":
			i += 1
			log = sys.argv[i]
		elif sys.argv[i] == "--csv":
			i += 1
			csv = sys.argv[i]
		else:
			inputfile = sys.argv[i]
		i += 1
	if not inputfile or not output:
		print sys.argv[0] + " [input] -o [output] --csv [csv file] --log [conflict log]\nType '" + sys.argv[0] + " --help' for usage."
	else:
		GrammarParser(inputfile, output, csv, log)
