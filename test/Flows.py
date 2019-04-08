from xml.etree import ElementTree


class Flow:
	def __init__(self, xml):
		self.id = xml.find("id").text
		self.bag = xml.find("bag").text
		self.lmax = xml.find("lmax").text
		self.jitter = float(xml.find("jitter").text)

	def command(self):
		return ' '.join(["python3 send.py", self.id, self.lmax, self.bag])


class Flows:
	def __init__(self, config):
		with open(config, 'r') as f:
			xml = f.read()
			self.config = ElementTree.fromstring(xml)

	def toSendBy(self, id):
		flows = []
		for flow_xml in self.config.findall("./vls/vl"):
			if int(flow_xml.find("sender").text) == id:
				flows.append(Flow(flow_xml))
		return flows

	def toReceiveBy(self, id):
		flows = []
		for flow_xml in self.config.findall("./vls/vl"):
			if int(flow.find("receiver").text) == id:
				flows.append(Flow(flow_xml))
		return flows
