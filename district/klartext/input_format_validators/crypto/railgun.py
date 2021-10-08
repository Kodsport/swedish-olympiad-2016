#!/usr/bin/env python3

import string
import random

# CIPHER 3

C = 3

A = string.ascii_lowercase

def encrypt(msg):
    nmsg = []
    ans = []

    while msg:
        for i in range(len(msg)):
            if i % 2 == 0:
                ans += [msg[i]]
            else:
                nmsg += [msg[i]]
        msg = list(reversed(nmsg))
        nmsg = []
    return ''.join(ans)

def decrypt(dec):
    nmsg = []
    ans = []

    msg = [i for i in range(len(dec))]
    while msg:
        for i in range(len(msg)):
            if i % 2 == 0:
                ans += [msg[i]]
            else:
                nmsg += [msg[i]]
        msg = list(reversed(nmsg))
        nmsg = []

    return ''.join(dec[ans.index(x)] for x in range(len(dec)))


def generate_random():
    length = random.randint(4, 16)
    return ''.join(random.choice(A) for i in range(length))

def test():
    for i in range(50):
        x = generate_random();
        assert decrypt(encrypt(x)) == x
