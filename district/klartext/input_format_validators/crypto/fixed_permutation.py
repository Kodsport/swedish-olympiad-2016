#!/usr/bin/env python3

import string
import random

# CIPHER 2

C = 2

A = string.ascii_lowercase

perm = [
        24, 21, 23, 20, 22,
        9, 6, 8, 5, 7,
        19, 16, 18, 15, 17,
        4, 1, 3, 0, 2,
        14, 11, 13, 10, 12
]

def encrypt(msg):
    return ''.join([msg[perm[i]] for i in range(25)])

def decrypt(msg):
    return ''.join([msg[perm.index(i)] for i in range(25)])

def generate_random():
    length = random.randint(25, 25)
    return ''.join(random.choice(A) for i in range(length))

def test():
    for i in range(50):
        x = generate_random();
        assert decrypt(encrypt(x)) == x
