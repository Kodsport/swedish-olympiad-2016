#!/usr/bin/python3
import sys

def videos(K, M, S):
    global goto, steps
    goto = S
    steps = M - 1
    if K > 1000:
        sys.exit(0)

def clip(I):
    global steps
    time = 0
    seen = {}
    i = 0
    while i < steps:
        i += 1
        #print("Video %d is %d" % (i, I))
        I = goto[I]
        time += 1
        if I in seen and steps - i >= 3000:
            delta = time - seen[I]
            #print("cycle %d %d %d" % (delta, i, steps))
            left = steps - i
            i = i + left // delta * delta
            #print("cycle %d %d %d" % (delta, i, steps))
            continue
        seen[I] = time
    #print("Video %d is %d" % (i, I))
    return I
