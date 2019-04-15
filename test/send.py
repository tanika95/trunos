from datetime import *
from scapy.all import *
import sys
import time
from Flows import Flows

host = int(sys.argv[1])
config = sys.argv[2]
flows = Flows(config).toSendBy(host)
count = 100

def send(bag, packets):
	if len(packets) == 0:
			return 0
	sendp(packets.pop(0))
	threading.Timer(bag, send, [bag, packets]).start()

# Заранее чтобы пакеты были сгенерированы - не терять время
info = [(flow.bag, flow.packets(count))  for flow in flows]
for flow in info:
	bag = flow[0]
	packets = flow[1]
	send(bag, packets)
