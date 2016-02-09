pos = set()

sc = 0

def init(N, L, P):
    for i in P:
        jump(-100, i)

def jump(A, B):
    global sc
    if A-1 in pos or A+1 in pos: sc -= 1
    if A-1 in pos and A-2 not in pos: sc -= 1
    if A+1 in pos and A+2 not in pos: sc -= 1
    if A in pos: pos.remove(A)

    if B-1 in pos or B+1 in pos: sc += 1
    if B-1 in pos and B-2 not in pos: sc += 1
    if B+1 in pos and B+2 not in pos: sc += 1
    pos.add(B)

def score():
    return sc
