#!/usr/bin/env python3

import string
import random

# CIPHER 1

C = 1

A = string.ascii_lowercase

def decrypt(msg):
    shift, msg = msg.split("-")
    shift = int(shift)
    return ''.join(A[(int(shift) + A.find(i)) % len(A)] for i in msg)

def encrypt(msg):
    shift = random.randint(0, 25)
    return str(shift) + "-" + ''.join(A[(-int(shift) + A.find(i)) % len(A)] for i in msg)

def generate_random():
    length = random.randint(4, 16)
    return ''.join(random.choice(A) for i in range(length))

def test():
    for i in range(50):
        x = generate_random();
        assert decrypt(encrypt(x)) == x
