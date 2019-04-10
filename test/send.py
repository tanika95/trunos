from scapy.all import *
import sys
import time

vl = int(sys.argv[1])
lmax = int(sys.argv[2])
bag = int(sys.argv[3])

app_port = 10000 + vl
payload = RandString(size=lmax - 46)
packet = Ether()/Dot1Q(vlan=vl)/IP()/UDP(sport=app_port, dport=app_port)/Raw(payload)

#TODO: номера пакетов
for i in range(0, 100000):
	sendp(packet)
	time.sleep(bag)
