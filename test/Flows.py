from xml.etree import ElementTree
from scapy.all import *

SEND_BASE = 10000
RCV_BASE = 20000


class Flow:
	def __init__(self, xml):
		self.id = int(xml.find("id").text)
		self.bag = int(xml.find("bag").text)
		self.lmax = int(xml.find("lmax").text)
		self.jitter = float(xml.find("jitter").text)

	def packets(self, amount):
		packets = []
		sport = SEND_BASE + self.id
		dport = RCV_BASE + self.id
		sequence = 8
		payload = RandString(size=self.lmax - 46 - sequence)
		for i in range(0, amount):
			num = str(i)
			load = '0' * (sequence - len(num)) + num + str(payload)
			packets += [Ether()/Dot1Q(vlan=self.id)/IP()/UDP(sport=sport, dport=dport)/Raw(load)]
		return packets

class Flows:
	def __init__(self, config):
		with open(config, 'r') as f:
			xml = f.read()
			self.config = ElementTree.fromstring(xml)

	def toSendBy(self, id):
		flows = []
		for flow_xml in self.config.findall("./vls/vl"):
			if int(flow_xml.find("sender").text) == id:
				flows.append(Flow(flow_xml))
		return flows

	def sentByIds(self, id):
		flows = []
		for flow_xml in self.config.findall("./vls/vl"):
			if int(flow_xml.find("sender").text) == id:
				flows.append(int(flow_xml.find("id").text))
		return flows

	def receivedByIds(self, id):
		flows = []
		for flow_xml in self.config.findall("./vls/vl"):
			if int(flow_xml.find("receiver").text) == id:
				flows.append(int(flow_xml.find("id").text))
		return flows

	def amount(self):
		return len(self.config.findall("./vls/vl"))
