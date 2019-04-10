from scapy.all import *
import sys
import time

vl = int(sys.argv[1])
lmax = int(sys.argv[2])
bag = int(sys.argv[3])

app = 10000 + vl
sequence = 8
payload = RandString(size=lmax - 46 - sequence)

#TODO: номера пакетов
for i in range(0, 100):
	num = str(i)
	load = '0' * (sequence - len(num)) + num + str(payload)
	packet = Ether()/Dot1Q(vlan=vl)/IP()/UDP(sport=app, dport=app)/Raw(load)
	sendp(packet)
	time.sleep(bag)
