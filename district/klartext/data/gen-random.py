#!/usr/bin/env python3
import sys
import random

code = sys.argv[1]

module = __import__(code)

print("%d %s" % ( module.C, module.encrypt(module.generate_random())))
