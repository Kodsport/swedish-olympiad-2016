#!/usr/bin/env python3
# Usage: python generator_random.py n k m seed

import string
import random
import sys

(n, k, m, seed) = [int(s) for s in sys.argv[1:]]

random.seed(sys.argv[-1])

alphabet = string.ascii_uppercase
goodmask = 0
dice = []
masks = []

def bit(c):
    return 1 << (ord(c) - 65)

def gen_no():
    s = ''
    while True:
        s = random.choice(alphabet)
        if goodmask & bit(s):
            break
    used = set()
    m = bit(s)
    for i, m2 in enumerate(masks):
        if m & m2:
            used.add(i)
    assert len(used) < len(dice)
    for it in range(random.randrange(26)):
        c = s[0]
        while c in s:
            c = random.choice(alphabet)
        m = bit(c)
        s += c
        d = used.copy()
        for i, m2 in enumerate(masks):
            if m & m2:
                d.add(i)
        if len(d) == len(dice):
            s = s[:-1]
            break
        used = d

    # s is now a random collection of letters not occurring in all strings.
    # Use #occurrances+1 of them to get a contradiction by Hall's.
    # To avoid obvious contradictions, we'd prefer to at most as many of each
    # letter as is available, though.
    lims = []
    for c in s:
        m = bit(c)
        lims.append(sum(1 for m2 in masks if m & m2))
    limsum = sum(lims)
    size = len(used)
    assert limsum >= size
    if limsum == size:
        lims[0] += 1 # :(
        limsum += 1

    sel = ''
    for i, c in enumerate(s):
        sel += lims[i] * c
    incl = random.sample(sel, size+1)
    excl = []
    for i, d in enumerate(dice):
        if i not in used:
            excl.append(random.choice(d))
    random.shuffle(excl)
    del excl[-1]
    incl += excl
    random.shuffle(incl)
    return ''.join(incl)

def gen_yes():
    r = []
    for d in dice:
        r.append(random.choice(d))
    random.shuffle(r)
    return ''.join(r)

print("{} {} {}".format(n,k,m))

allmask = (1 << 26) - 1
somemask = 0
for i in range(n):
    die = ''.join(random.sample(alphabet, k))
    mask = 0
    for c in die:
        mask |= bit(c)
    dice.append(die)
    masks.append(mask)
    allmask &= mask
    somemask |= mask
    print(die)
goodmask = somemask & ~allmask
#assert goodmask != 0

yeses = random.randrange(m+1)
nos = m - yeses
output = ["Y"] * yeses + ["N"] * nos
random.shuffle(output)
output = ''.join(output)
wl = set()
wl.add('')
for i in range(m):
    w = ''
    while w in wl:
        if output[i] == 'Y':
            w = gen_yes()
        else:
            w = gen_no()
    wl.add(w)
    print(w)

# print(output)
print(yeses, file=sys.stderr)

