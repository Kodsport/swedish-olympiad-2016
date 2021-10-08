#!/usr/bin/env python3
import sys
import random

t, msg = input().split()

cryptos = {
    '1': 'caesar',
    '3': 'fixed_permutation',
    '2': 'railgun',
    '4': 'dynamic_permutation',
    '5': 'morse',
}

module = __import__(cryptos[t])

module.decrypt(msg)

try:
    input()
    sys.exit(43)
except EOFError:
    sys.exit(42)
