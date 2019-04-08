#!/usr/bin/env python3

import os
import sys
import time
from NetTopo import NetTopo
from mininet.cli import CLI
from mininet.link import TCLink
from mininet.log import setLogLevel, info
from mininet.net import Mininet
from mininet.node import RemoteController, UserSwitch
from mininet.clean import cleanup


if len(sys.argv) < 2:
	print("Usage: ./run.py config")
	sys.exit(-1)
config = sys.argv[1]
cleanup()
setLogLevel('info')
runos = RemoteController('runos', '0.0.0.0', 6653)
net = Mininet(topo=NetTopo(config), controller=runos, switch=UserSwitch, link=TCLink)
net.start()

CLI(net)
net.stop()
