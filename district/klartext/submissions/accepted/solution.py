#!/usr/bin/env python3

t, msg = input().split()

import string

A = string.ascii_lowercase


def caesar(msg):
    shift, msg = msg.split("-")
    shift = int(shift)
    return ''.join(A[(int(shift) + A.find(i)) % len(A)] for i in msg)

perm = [
        24, 21, 23, 20, 22,
        9, 6, 8, 5, 7,
        19, 16, 18, 15, 17,
        4, 1, 3, 0, 2,
        14, 11, 13, 10, 12
]

def fixed(msg):
    return ''.join([msg[perm.index(i)] for i in range(25)])

def dynamic(msg):
    perm = generate(0, len(msg))
    return ''.join(msg[perm.index(x)] for x in range(len(msg)))

def generate(a, b):
    if b - a == 1:
        return [a]

    mid = (a + b) // 2
    if (b - a) % 2 == 0:
        return generate(mid, b) + generate(a, mid)
    return generate(a, mid) + [mid] + generate(mid + 1, b)

def railgun(dec):
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

def morse(msg):
    ans = []
    while msg:
        for i in range(len(msg)+1):
            if msg[:i] in rev:
                ans += rev[msg[:i]]
                msg = msg[i:]
                break
    return ''.join(ans)

dec = {
    '1': caesar,
    '2': railgun,
    '3': fixed,
    '4': dynamic,
    '5': morse,
}

print(dec[t](msg))

