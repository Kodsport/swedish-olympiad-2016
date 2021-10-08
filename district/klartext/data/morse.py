#!/usr/bin/env python3

import string
import random

# CIPHER 5

C = 5

A = string.ascii_lowercase

code = {
'z' : '000',
'r' : '0011',
's' : '0100',
't' : '0110',
'u' : '1000',
'v' : '1001',
'w' : '1011',
'x' : '1101',
'y' : '1111',
'j' : '00100',
'k' : '01010',
'l' : '01011',
'm' : '01111',
'n' : '10100',
'o' : '11000',
'p' : '11001',
'q' : '11101',
'c' : '001010',
'd' : '001011',
'e' : '011100',
'f' : '011101',
'g' : '101010',
'h' : '101011',
'i' : '111001',
'a' : '1110000',
'b' : '1110001',
}

rev = {}

for k, v in code.items():
    rev[v] = k

def encrypt(msg):
    return ''.join(code[x] for x in msg)

def decrypt(msg):
    ans = []
    while msg:
        for i in range(len(msg)):
            if msg[0:i] in rev:
                ans += rev[msg[0:i]]
                msg = msg[:i]
    return ''.join(ans)

def generate_random():
    length = random.randint(4, 10)
    return ''.join(random.choice(A) for i in range(length))

def test():
    for i in range(50):
        x = generate_random();
        assert decrypt(encrypt(x)) == x
