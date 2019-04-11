#!/usr/bin/env python3

import sys
import random

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
	def __init__(self, id, bw, sender, receiver):
		self.bw = bw
		self.sender = sender
		self.receiver = receiver
		self.fid = id

	def xml(self):
		bag = random.randint(1, 2)
		return '\n'.join((
			'	<vl>',
			'		<id>%d</id>' % self.fid,
			'		<sender>%d</sender>' % self.sender,
			'		<receiver>%d</receiver>' % self.receiver,
			'		<bag>%d</bag>' % bag,
			'		<lmax>%d</lmax>' % (self.bw * bag),
			'		<jitter>0.01</jitter>',
			'	</vl>'
		))


class RandomFlows:
	BW = 500

	def __init__(self, data_class, hosts):
		self.type = data_class
		self.hosts = hosts

	def generate(self):
		flows = []
		vl = 0
		k = 1
		for amount in [self.type.light(), self.type.medium(), self.type.heavy()]:
			for i in range(amount):
				vl += 1
				receiver = 0
				sender = 0
				while receiver == sender:
					receiver = random.randint(1, 4)
					sender = random.randint(1, 4)
				bw = self.BW * k
				flows.append(Flow(vl, bw, sender, receiver))
			k *= 2
		return flows

	def xml(self):
		flows = self.generate()
		return '\n'.join((
			'<vls>',
			'\n'.join([flow.xml() for flow in flows]),
			'</vls>'
		))



if len(sys.argv) < 5:
	print("Usage: ./generator.py filename type size hosts")
	sys.exit(-1)

filename = sys.argv[1]
data_type = int(sys.argv[2])
size = int(sys.argv[3])
hosts = int(sys.argv[4])

flows = RandomFlows(DataClass(data_type, size), hosts)
with open(filename, 'w') as f:
	f.write(flows.xml())
