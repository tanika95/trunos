#!/usr/bin/env python3
import sys
from Results import Results


if len(sys.argv) < 2:
	print("Usage: ./res.py flows")
	sys.exit(-1)
amount = int(sys.argv[1])
Results(amount, '').toFile('report')
