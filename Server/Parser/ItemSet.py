#!/usr/bin/env python
# -*- coding: utf-8 -*-

class SetOfItems:
	def __init__(self, items = None):
		if items:
			self.items = items
		else:
			self.items = ()
		self.altered = True
	def __contains__(self, item):
		h = item.hash
		for it in self.items:
			if it.hash == h:
				if item == it:
					return True
		return False
	def add(self, item):
		"Add an item or all the items in a set of items to this set"
		if isinstance(item, SetOfItems):
			for it in item.items:
				if it not in self.items:
					self.items += (it,)
		else:
			self.items += (item,)
	def __eq__(self, other):
		"Compare to sets of items"
		if len(other.items) != len(self.items):
			return False
		for it in self.items:
			if it not in other.items:
				return False
		return True
	def condAdd(self, item):
		h = item.hash
		for it in self.items:
			if it.hash == h:
				if item == it:
					return False
		#if item in self:
		#	return False
		self.items += (item,)
		return True
	def isEmpty(self):
		return len(self.items) == 0
	def __iter__(self):
		for item in self.items: yield item
	def __getitem__(self, index):
		return self.items[index]
	def kernels(self):
		"Get the kernel items of this set of items"
		for item in self.items:
			if item.isKernel(): yield item
	def __str__(self):
		retval = "["
		for it in self:
			retval += str(it) + ", "
		return retval + "]"

"""
import bisect

class SetOfItems:
	def __init__(self, items = None):
		if items:
			self.items = items
		else:
			self.items = ()
		self.indexed = False
	def __contains__(self, item):
		if not self.indexed:
			if len(self.items) < 150:
				h = item.hash
				for it in self.items:
					if it.hash == h:
						if item == it:
							return True
				return False
			else:
				self.indexed = True
				self.items = list(self.items)
				self.items.sort()
		i = bisect.bisect_left(self.items, item)
		if i >= len(self.items):
			return False
		return self.items[i] == item
	def add(self, item):
		"Add an item or all the items in a set of items to this set"
		if isinstance(item, SetOfItems):
			self.indexed = False
			for it in item.items:
				if it not in self.items:
					self.items += (it,)
		else:
			if self.indexed:
				i = bisect.bisect_left(self.items, item)
				self.items.insert(i, item)
			else:
				self.items += (item,)
	def condAdd(self, item):
		"Add item if not in this set"
		if not self.indexed:
			if len(self.items) < 150:
				h = item.hash
				for it in self.items:
					if it.hash == h:
						if item == it:
							return False
				self.items += (item,)
				return True
			else:
				self.indexed = True
				self.items = list(self.items)
				self.items.sort()
		i = bisect.bisect_left(self.items, item)
		if i >= len(self.items):
			self.items.insert(i, item)
			return True
		if not item == self.items[i]:
			self.items.insert(i, item)
			return True
		return False
	def __eq__(self, other):
		"Compare to sets of items"
		if len(other.items) != len(self.items):
			return False
		for it in self.items:
			if it not in other.items:
				return False
		return True
	def isEmpty(self):
		return len(self.items) == 0
	def __iter__(self):
		for item in self.items: yield item
	def __getitem__(self, index):
		return self.items[index]
	def kernels(self):
		"Get the kernel items of this set of items"
		for item in self.items:
			if item.isKernel(): yield item
	def __str__(self):
		retval = "["
		for it in self:
			retval += str(it) + ", "
		return retval + "]"
"""

