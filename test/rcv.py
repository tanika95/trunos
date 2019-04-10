from scapy.all import *
from datetime import *
import sys
import time


import pcapy as pcap
conf.use_pcap=True

result = {}

def add(p):
	timestamp = datetime.now()
	result.setdefault(p.vlan, []).append(timestamp.strftime("%S.%f"))

sniff(prn=add)

print(result)
