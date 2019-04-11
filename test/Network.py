import time
from mininet.cli import CLI
from mininet.link import TCLink
from mininet.log import setLogLevel, info
from mininet.net import Mininet
from mininet.node import RemoteController, UserSwitch
from mininet.clean import cleanup

from NetTopo import NetTopo

class Network:
	actions = "actions.sh"

	def __init__(self, config):
		cleanup()
		setLogLevel('info')
		runos = RemoteController('runos', '0.0.0.0', 6653)
		self.topology = NetTopo(config)
		self.net = Mininet(controller=runos, switch=UserSwitch, link=TCLink,
			topo=self.topology, autoSetMacs=True)
		for host in self.topology.hostNames():
			self.net.getNodeByName(host).setDefaultRoute(host + '-eth0')

		self.config = config

	def start(self):
		self.net.start()
		time.sleep(8)
		f = open(self.actions, 'w')
		f.write(self.sinkCommands())
		f.write(self.flowsCommands())
		f.close()
		CLI(self.net, script=self.actions)
		CLI(self.net)

	def stop(self):
		self.net.stop

	def sinkCommands(self):
		config = ''
		for host in self.topology.hostNames():
			config += host + " python3 rcv.py "
			config += host + ' ' + self.config + ' &\n'
		return config

	def flowsCommands(self):
		i = 0
		config = ''
		for host in self.topology.hostNames():
			i += 1
			config += host + " python3 send.py "
			config += str(i) + ' ' + self.config + ' &\n'
		return config
