from datetime import *
import os
from scapy.all import *
import sys
import time
from Flows import Flows
from threading import Thread

import pcapy as pcap
conf.use_pcap=True


host = sys.argv[1]
config = sys.argv[2]
result = {}
flows = Flows(config)
outgoing = flows.sentByIds(host)
incomming = flows.sentByIds(host)
count = 90

def write(report, stats):
	f = open('results/raw' + report, 'w')
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

def rcv(vl, send):
	port = vl
	report = str(vl)
	if send:
		port += SEND_BASE
		report += '-snd'
	else:
		port += RCV_BASE
		report += '-rcv'
	stats = []
	sniff(prn=lambda p: stats.append(entry(p, vl)), count=count, filter='udp and port %u' % port)
	write(report, stats)

threads = []
for sink in [(outgoing, True), (incomming, False)]:
	vls = sink[0]
	send = sink[1]
	for vl in vls:
		threads += [Thread(target=rcv, args=(vl, send))]

for thread in threads:
	thread.start()

for thread in threads:
	thread.join()
