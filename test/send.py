from datetime import *
from scapy.all import *
import sys
import time
from Flows import Flows

host = int(sys.argv[1])
config = sys.argv[2]
flows = Flows(config).toSendBy(host)
count = 200

def write(id, stats):
	f = open('results/raw/' + str(id) + '.snd', 'w')
	num = 0
	for timestamp in stats:
		f.write(str(num) + ' ' + timestamp.strftime("%M.%S.%f") + '\n')
		num += 1
		if num >= count / 2:
			# ловим в 2 раза меньше пакетов - чтобы не зависать в rcv
			break

def send(flow, packets, times):
	start = datetime.now()
	if len(packets) == 0:
		write(flow.id, times)
		return 0
	times.append(datetime.now())
	sendp(packets.pop(0), verbose=False)
	# Поправка на произведенные действия - чтобы меньше выбиваться из слота
	slp = flow.bag - (datetime.now() - start).microseconds / 1000000
	threading.Timer(slp, send, [flow, packets, times]).start()

# Заранее чтобы пакеты были сгенерированы - не терять время
info = [(flow, flow.packets(count))  for flow in flows]
for flow in info:
	info = flow[0]
	packets = flow[1]
	send(info, packets, [])
