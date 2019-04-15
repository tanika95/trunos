from datetime import *
import os
from scapy.all import *
import sys
import time
from Flows import *
from threading import Thread

import pcapy as pcap
conf.use_pcap=True


host = int(sys.argv[1])
config = sys.argv[2]
result = {}
flows = Flows(config)
incomming = flows.receivedByIds(host)
count = 100

def write(report, stats):
	f = open('results/raw/' + report, 'w')
	for packet in stats:
		num = str(packet[0])
		timestamp = packet[1]
		f.write(num + ' ' + timestamp + '\n')

def log(id, text):
	f = open("results/log-h" + host + '.' + str(id), 'w')
	f.write(text + '\n')

def entry(p, vlan):
	timestamp = datetime.now()
	try:
		if p.vlan != vlan:
			log(vlan, 'Несоотвествие vlan : %u - %u' % (p.vlan, vlan))
			return []
		num = int(p.load[:8])
		return (num, timestamp.strftime("%M.%S.%f"))
	except:
		log(vlan, "Неверный пакет" + p.show())
		return []

def rcv(vl):
	port = vl + RCV_BASE
	report = str(vl) + '.rcv'
	stats = []
	sniff(prn=lambda p: stats.append(entry(p, vl)), count=count, filter='udp and port %u' % port)
	write(report, stats)

threads = []
for vl in incomming:
	threads += [Thread(target=rcv, args=[vl])]

for thread in threads:
	thread.start()

for thread in threads:
	thread.join()
