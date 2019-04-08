from scapy.all import *
import sys
import time

vl = int(sys.argv[1])
lmax = int(sys.argv[2])
bag = int(sys.argv[3])

for i in range(0, 1000):
    packet = IP("10.0.0.2")/Ether()/Dot1Q(vlan=vl)/Raw(RandString(size=lmax))
    sendp(packet)
    time.sleep(bag)
