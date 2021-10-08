#!/usr/bin/env python3

import string
import random

# CIPHER 4

C = 4

A = string.ascii_lowercase

def encrypt(msg):
    perm = generate(0, len(msg))
    return ''.join([msg[perm[i]] for i in range(len(msg))])

def decrypt(msg):
    perm = generate(0, len(msg))
    return ''.join(msg[perm.index(x)] for x in range(len(msg)))

def generate(a, b):
    if b - a == 1:
        return [a]

    mid = (a + b) // 2
    if (b - a) % 2 == 0:
        return generate(mid, b) + generate(a, mid)
    return generate(a, mid) + [mid] + generate(mid + 1, b)

def generate_random():
    length = random.randint(1, 16)
    return ''.join(random.choice(A) for i in range(length))

def test():
    for i in range(50):
        x = generate_random();
        assert decrypt(encrypt(x)) == x
