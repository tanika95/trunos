#!/usr/bin/env python3

import os
import sys
import time
from Network import Network


if len(sys.argv) < 3:
	print("Usage: ./run.py config result")
	sys.exit(-1)
config = sys.argv[1]
result = sys.argv[2]
net = Network(config, result)
net.start()
net.stop()
