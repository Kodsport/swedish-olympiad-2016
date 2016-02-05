#!/usr/bin/python3

# tester for the task "solitaireschack"
# usage: ./tester.py input_file correct_output output_dir < contestants_output

import os
from sys import stdin, exit, argv
import sys
import re
import random

def die(msg):
    f = open(argv[3] + os.sep + "score.txt", "wt+", encoding="utf-8")
    f.write("0")
    f.close()
    exit(43)

def accept(score):
    f = open(argv[3] + os.sep + "score.txt", "wt+", encoding="utf-8")
    f.write(str(score))
    f.close()
    exit(42)


def safe_print(n):
    try:
        print(n)
        sys.stdout.flush()
    except IOError:
        pass

fin, fcor = open(argv[1],'r'), open(argv[2],'r')

best_score = int(fcor.read())

alphabet, case_score, seed = fin.read().split()
case_score = int(case_score)
seed = int(seed)

random.seed(seed)

valid_pieces = {
        '1': '1',
        '2': '2',
        '3': '3',
        '4': '4',
        'd': 'dam',
        'l': 'lopare',
        's': 'springare',
        't': 'torn'
}

def at_edge(r, c):
    return r in [0, 5] or c in [0, 5]

def k_move(r, c, rp, cp, x):
    if abs(r - rp) not in [0, x]: return False
    if abs(c - cp) not in [0, x]: return False
    return True

valid_moves = {
    '1': lambda r, c, rp, cp: k_move(r, c, rp, cp, 1),
    '2': lambda r, c, rp, cp: k_move(r, c, rp, cp, 2),
    '3': lambda r, c, rp, cp: k_move(r, c, rp, cp, 3),
    '4': lambda r, c, rp, cp: k_move(r, c, rp, cp, 4),
    'springare': lambda r, c, rp, cp: list(sorted([abs(r - rp), abs(c - cp)])) == [1, 2],
    'lopare': lambda r, c, rp, cp: ((r + c == rp + cp) or (r - c == rp - cp)) and at_edge(rp, cp),
    'torn': lambda r, c, rp, cp: (rp in [0, 5] and c == cp) or (cp in [0, 5] and r == rp),
    'dam': lambda r, c, rp, cp: valid_moves['lopare'](r, c, rp, cp) or valid_moves['torn'](r, c, rp, cp), 
    'start': lambda r, c, rp, cp: True
}
 

alphabet = [valid_pieces[x] for x in alphabet]

def random_piece():
    return random.choice(alphabet)

cur = [[ [random_piece() for i in range(3)] for c in range(6) ] for r in range(6)]

for x in cur:
    safe_print(' '.join(a[0] for a in x))

hits = []

last_piece = 'start'
lr = -1
lc = -1

while True:
    try:
        r, c = [int(x) for x in stdin.readline().split()]
    except:
        die("Bad input")
    if r == 0 and c == 0:
        break
    if not (1 <= r <= 6 and 1 <= c <= 6):
        die("Move out of bounds")


    r = r - 1
    c = c - 1
    if not cur[r][c]:
        die("Hitting blank square")

    if not valid_moves[last_piece](lr, lc, r, c):
        die("Invalid move")

    if lr == r and lc == c:
        die("Invalid move")

    
    piece = cur[r][c][0]
    last_piece = piece
    lr = r
    lc = c
    hits.append(piece)
    cur[r][c].pop(0)
    safe_print(cur[r][c][0] if cur[r][c] else 'blank')

   
def score(hits):
    base_score = len(hits)
    i = 0
    alternating = (0, None)
    while i < len(hits):
        next_i = i + 4
        seq = hits[i:i+4]
        is_piece = False
        is_num = False
        if seq == ["1", "2", "3", "4"] or seq == ["4", "3", "2", "1"]:
            base_score += 12
            is_num = True
        elif list(sorted(seq)) == ["1","2","3","4"]:
            base_score += 8
            is_num = True
        elif list(sorted(seq)) == list(sorted(['dam', 'lopare', 'springare', 'torn'])):
            base_score += 8
            is_piece = True
        else:
            next_i = i + 1
        i = next_i

        cnt, which = alternating
        if is_piece and which != 'piece':
            alternating = (cnt + 1, 'piece')
        elif is_num and which != 'num':
            alternating = (cnt + 1, 'num')
        elif is_piece:
            alternating = (1, 'piece')
        elif is_num:
            alternating = (1, 'num')
        else:
            alternating = (0, None)
        
        cnt, which = alternating
        if cnt == 2:
            base_score += 16
        elif cnt > 2:
            base_score += 8

    streak = (0, None)
    for x in hits:
        cnt, which = streak
        if x == which:
            streak = (cnt + 1, x)
        else:
            streak = (1, x)
        cnt, which = streak
        if cnt == 2:
            base_score += 4
        elif cnt > 2:
            base_score += 2
    return base_score

accept(case_score * score(hits) / best_score)
