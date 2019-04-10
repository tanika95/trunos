#!/usr/bin/env python3

import os
import sys
import time
from Network import Network


if len(sys.argv) < 2:
	print("Usage: ./run.py config")
	sys.exit(-1)
config = sys.argv[1]
net = Network(config)
net.start()
net.stop()
