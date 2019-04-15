from functools import reduce
from datetime import *

class PacketStat:
	def __init__(self, stat):
		self.num = int(stat[0])
		self.time = stat[1]

	def timestamp(self):
		return datetime.strptime(self.time, "%M.%S.%f").timestamp()


class SniffStats:
	def __init__(self, file):
		self.file = file

	def asVector(self):
		f = open(self.file, 'r')
		return [PacketStat(line.split()) for line in f.readlines()]


class FlowStats:
	def __init__(self, id, send, recv):
		self.id = id
		delays, self.losts = self.diffes(send, recv)
		self.delay = max(delays)
		min_delay = min(delays)
		mean = reduce(lambda x, y: x + y, delays) / len(delays)
		self.jitter = max([self.delay - mean, mean - min_delay])

	def lost(self):
		return len(self.losts)

	def diffes(self, send, recv):
		i = 0
		losts = []
		delays = []
		for packet in send:
			if i >= len(recv):
				break
			if packet.num != recv[i].num:
				 losts.append((packet.num, packet.time))
			else:
				rcv = recv[i].timestamp()
				snd = packet.timestamp()
				delays.append(rcv - snd)
				if rcv - snd < 0:
					print(i)
				i += 1
		return delays, losts

	def info(self):
		report = '-' * 30 + '\n'
		report += "Поток %u: задержка %f, джиттер %f, число потерь %u\n" \
			% (self.id, self.delay, self.jitter, self.lost())
		report += "Потеряные пакеты: \n"
		for packet in self.losts:
			 report += "%u отправленный в %s\n" % (packet[0], packet[1])
		return report


class Results:
	raw = 'raw/'

	def __init__(self, amount, catalog):
		self.flows = amount
		self.path = catalog

	def gather(self):
		stats = []
		for i in range(self.flows):
			send = SniffStats(self.path + self.raw + str(i + 1) + '.snd').asVector()
			recv = SniffStats(self.path + self.raw + str(i + 1) + '.rcv').asVector()
			stats += [FlowStats(i + 1, send, recv)]

		max_delay = max([s.delay for s in stats])
		jitter = max([s.jitter for s in stats])
		losts = max([s.lost() for s in stats])

		report = "Максимальные задержка %f, джиттер %f, число потерь %u\n" \
			% (max_delay, jitter, losts)
		report += ''.join([s.info() for s in stats])
		return report

	def toFile(self, file):
		result = self.gather()
		f = open(self.path + file, 'w')
		f.write(result)
