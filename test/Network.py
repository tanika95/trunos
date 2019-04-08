import time
from mininet.cli import CLI
from mininet.link import TCLink
from mininet.log import setLogLevel, info
from mininet.net import Mininet
from mininet.node import RemoteController, UserSwitch
from mininet.clean import cleanup

from NetTopo import NetTopo
from Flows import Flows

class Network:
	def __init__(self, config):
		cleanup()
		setLogLevel('info')
		runos = RemoteController('runos', '0.0.0.0', 6653)
		self.topology = NetTopo(config)
		self.net = Mininet(controller=runos, switch=UserSwitch, link=TCLink,
			topo=self.topology, autoSetMacs=True)
		for host in self.topology.hostNames():
			self.net.getNodeByName(host).setDefaultRoute(host + '-eth0')

		self.flows = Flows(config)

	def start(self):
		self.net.start()

	def stop(self):
		time.sleep(30)
		CLI(self.net)
		self.net.stop()

	def runFlows(self):
		i = 0
		for host in self.topology.hostNames():
			i += 1
			for flow in self.flows.toSendBy(i):
				self.net.getNodeByName(host).cmdPrint(flow.command())
				break
