from xml.etree import ElementTree
from mininet.topo import Topo

class NetTopo(Topo):
	def __init__(self, config):
		Topo.__init__(self)

		with open(config, 'r') as f:
			xml = f.read()
			self.config = ElementTree.fromstring(xml)

		self.nethosts = []
		for host in self.hostNames():
			nethost = self.addHost(host)
			self.nethosts.append(nethost)

		self.netswitches = []
		for sw in self.swNames():
			self.netswitches.append(self.addSwitch(sw))

		host_links = self.config.findall("./hostlinks/link")
		for link in host_links:
			hid = int(link.find("host").text) - 1
			swids = [int(sw.text) - 1 for sw in link.findall("switches/sw")]
			for sw in swids:
				self.addLink(self.nethosts[hid], self.netswitches[sw])

		k = 0.001 # TODO: надо снова расчитать эти тупые соотношения
		links = self.config.findall("./linksinfo/link")
		for link in links:
			sid = int(link.find("sender").text) - 1
			rid = int(link.find("receiver").text) - 1
			bw = k * int(link.find("bw").text)
			self.addLink(self.netswitches[sid], self.netswitches[rid], bw=bw)

	def hostNames(self):
		amount = int(self.config.find("hosts").text)
		return ['h' + str(i + 1) for i in range(amount)]

	def swNames(self):
		amount = int(self.config.find("switches").text)
		return ['s' + str(i + 1) for i in range(amount)]


topos = { 'mytopo': ( lambda: MyTopo() ) }
