#!/usr/bin/env python3

import sys


class DataClass:
	def __init__(self, type, size):
		self.size = size
		self.type = type

	def light(self):
		if self.type == 1:
			return int(0.9 * self.size)
		elif self.type == 2:
			return int(0.1 * self.size)
		elif self.type == 3:
			return int(0.33 * self.size)
		elif self.type == 4:
			return int(0.05 * self.size)

	def medium(self):
		if self.type == 1:
			return int(0.07 * self.size)
		elif self.type == 2:
			return int(0.80 * self.size)
		elif self.type == 3:
			return int(0.33 * self.size)
		elif self.type == 4:
			return int(0.15 * self.size)

	def heavy(self):
		if self.type == 1:
			return int(0.03 * self.size)
		elif self.type == 2:
			return int(0.1 * self.size)
		elif self.type == 3:
			return int(0.33 * self.size)
		elif self.type == 4:
			return int(0.80 * self.size)


class Flow:
	def __init__(self, bw, sender, receiver):
		self.bw = bw
		self.sender = sender
		self.receiver = receiver

	def xml(self):
		return ''.join((
			'<vl>',
			'<elems>',
			'<count>%d</count>' % 5,
			'</vl>'
		))


class RandomFlows:
	BW = 500

	def __init__(self, data_class, hosts):
		self.type = data_class
		self.hosts = hosts

	def generate(self):
		flows = []
		for amount in [self.type.light(), self.type.medium(), self.type.heavy()]
			for i in range(amount):
				sender = 1
				receiver = 2
				bw = self.BW * (i + 1)
				flows.append(Flow(bw, sender, receiver))
		return flows

	def xml(self):
		flows = self.generate()
		return ''.join((
			'<vls>',
			''.join([flow.xml() for flow in flows])
			'</vls>'
		))



if sys.argc < 5:
	print("Usage: ./generator.py filename type size hosts")
	sys.exit(-1)

filename = sys.argv[1]
data_type = sys.argv[2]
size = sys.argv[3]
hosts = sys.argv[4]

flows = RandomFlows(DataClass(data_type, size), hosts)
with open(filename, 'w') as f:
	f.write(flows.xml())
